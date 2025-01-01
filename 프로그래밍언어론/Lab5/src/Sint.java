 // Sint.java
// Interpreter for S
import java.util.Scanner;

public class Sint {
    static Scanner sc = new Scanner(System.in);
    static State state = new State();

    State Eval(Command c, State state) { 
	    if (c instanceof Decl) {
	        Decls decls = new Decls();
	        decls.add((Decl) c);
	        return allocate(decls, state);
	    }

	    if (c instanceof Function) { 
	        Function f = (Function) c; 
	        state.push(f.id, new Value(f)); 
	        return state;
	    }

	    if (c instanceof Stmt)
	        return Eval((Stmt) c, state); 
		
	    throw new IllegalArgumentException("no command");
    }

    State Eval(Stmt s, State state) {
        if (s instanceof Empty) 
	        return Eval((Empty)s, state);
        if (s instanceof Assignment)  
	        return Eval((Assignment)s, state);
        if (s instanceof If)  
	        return Eval((If)s, state);
        if (s instanceof While)  
	        return Eval((While)s, state);
        if (s instanceof Stmts)  
	        return Eval((Stmts)s, state);
	    if (s instanceof Let)  
	        return Eval((Let)s, state);
	    if (s instanceof Read)  
	        return Eval((Read)s, state);
	    if (s instanceof Print)  
	        return Eval((Print)s, state);
        if (s instanceof Call) 
	        return Eval((Call)s, state);
	    if (s instanceof Return) 
	        return Eval((Return)s, state);
        throw new IllegalArgumentException("no statement");
    }

    // [Function]
    // call without return value
    State Eval(Call c, State state) { // 함수 호출을 평가
    	// TODO: [Fill the code of call stmt]
	     Value v = state.get(c.fid); // 힘수 호출에 해당하는 아이디로 state를 탐색해함수를 v에 저장
         Function f = v.funValue();  // v는 함수 호출로 저장된 값이므로 함수 인스턴스, 함수 AST를 f에 저장
         state = newFrame(state, c, f); // 함수호출시 내부연산을 위한 프레임 생성
         state = Eval(f.stmt, state);   // newFrame으로 추가된 state로 함수의 stmt를 평가
         state = deleteFrame(state, c, f); // 함수 호출 후 인자 정보들을 제거
        
	    return state;
    }
    
    // [Function]
    // value-returning call 
    Value V (Call c, State state) { 
	    Value v = state.get(c.fid);  	 	// find function
        Function f = v.funValue();
        state = newFrame(state, c, f); 		// create the frame on the stack
        state = Eval(f.stmt, state); 	   	// interpret the call
	    v = state.peek().val;				// get the return value
        state = deleteFrame(state, c, f); 	// delete the frame from the stack
        return v;
    }
    
    // [Function]
    State Eval(Return r, State state) {
        Value v = V(r.expr, state);
        return state.set(new Identifier("return"), v); 
    }

    // [Function]
    State newFrame (State state, Call c, Function f) {
        if (c.args.size() == 0) 
            return state;
        
        // TODO: [Fill the code of newFrame]
    	// evaluate arguments
        Value val[] = new Value[c.args.size()]; // 함수 호출에 사용된 인자들을 저장할 배열
        int i=0;
        for (Expr e : c.args)
           val[i++] = V(e,state); // 함수 호출에 사용된 인자들의 값을 계산해 (단순 값 전달이 아닐 수 있음) 배열에 저장
        
	    // activate a new stack frame in the stack 
        i=0; 
        for (Decl d : f.params) { // pass by value
           Identifier v = (Identifier)d .id; // 함수 정의에 존재하는 id -> 함수 내부에서 사용할 변수
           state.push(v, val[i++]); // 함수 내부에서 사용할 변수에 인자 값들을 저장해 state에 반영
        }
        
        state.push(new Identifier("return"), null); // allocate for return value
        return state; // 함수 내부 연산을 위한 state 반환
    }

    // [Function]
    State deleteFrame (State state, Call c, Function f) { // 함수 연산 이후 관련 정보 제거
    // free a stack frame from the stack
        state.pop();  // pop the return value	
        
        // TODO: [Fill the code of deleteFrame]
        if (f.params != null) 
           state  = free(f.params, state); // 함수 정의에 존재하는 매개변수 정보들을 state에서 제거
       
        return state; // 수정된 state 반환
    }

    State Eval(Empty s, State state) {
        return state;
    }
  
    State Eval(Assignment a, State state) {
        Value v = V(a.expr, state);

        if (a.ar == null)
	        return state.set(a.id, v);
        else {
            Value i = V(a.ar.expr, state);
            Value val = state.get(a.ar.id);
            Value[] ar = (Value[]) val.arrValue();
            ar[i.intValue()] = v;
            return state;
        }
    }

    State Eval(Read r, State state) {
        if (r.id.type == Type.INT) {
	        int i = sc.nextInt();
	        state.set(r.id, new Value(i));
	    } 
 
	    if (r.id.type == Type.BOOL) {
	        boolean b = sc.nextBoolean();	
            state.set(r.id, new Value(b));
	    }

	    if (r.id.type == Type.STRING) {
	        String s = (String) sc.next();
	        state.set(r.id, new Value(s));
	    } 
	    return state;
    }

    State Eval(Print p, State state) {
	    System.out.println(V(p.expr, state));
        return state; 
    }
  
    State Eval(Stmts ss, State state) {
        for (Stmt s : ss.stmts) {
            state = Eval(s, state);
            if (s instanceof Return)  
                return state;
        }
        return state;
    }
  
    State Eval(If c, State state) {
        if (V(c.expr, state).boolValue( ))
            return Eval(c.stmt1, state);
        else
            return Eval(c.stmt2, state);
    }
 
    State Eval(While l, State state) {
        if (V(l.expr, state).boolValue( ))
            return Eval(l, Eval(l.stmt, state));
        else 
	        return state;
    }

    State Eval(Let l, State state) {
        State s = allocate(l.decls, state); // 지역변수로 사용할 변수들을 state에 할당
        
        // [Function]
        if (l.funs != null) { // let문에 지역함수 선언이 존재한다면
            // TODO: [Fill the code here]
            // Case with Function declaration inside Let
        	for (Function fun : l.funs)
        		s.push(fun.id, new Value(fun)); // 지역 state에 아이디와 해당함수를 pair로 저장
        }
        
        s = Eval(l.stmts, s); // 추가된 let지역 변수 함수로 stmt를 평가합니다.
 
	    return free(l.decls, s); // let함수 종료 후 선언부를 state에서 제거합니다.
    }

    State allocate (Decls ds, State state) {
        if (ds != null)
        for (Decl decl : ds) 
		    if (decl.arraysize > 0) { 
                Value[] ar = new Value[decl.arraysize];
                state.push(decl.id, new Value(ar)); 
            }
            else if (decl.expr == null)
                state.push(decl.id, new Value(decl.type));
	        else
		        state.push(decl.id, V(decl.expr, state));

        return state;
    }

    State free (Decls ds, State state) {
        if (ds != null)
        for (Decl decl : ds) 
            state.pop();

        return state;
    }

    Value binaryOperation(Operator op, Value v1, Value v2) {
        check(!v1.undef && !v2.undef,"reference to undef value");
	    switch (op.val) {
	    case "+":
            return new Value(v1.intValue() + v2.intValue());
        case "-": 
            return new Value(v1.intValue() - v2.intValue());
        case "*": 
            return new Value(v1.intValue() * v2.intValue());
        case "/": 
            return new Value(v1.intValue() / v2.intValue());
        case "==":
        	if (v1.type == Type.STRING)
        		return new Value(v1.value == v2.value);
        	else if (v1.type == Type.BOOL)
        		return new Value(v1.boolValue() == v2.boolValue());
        	else
        		return new Value(v1.intValue() == v2.intValue());
        case "!=":
        	if (v1.type == Type.STRING)
        		return new Value(v1.value != v2.value);
        	else if (v1.type == Type.BOOL)
        		return new Value(v1.boolValue() != v2.boolValue());
        	else
        		return new Value(v1.intValue() != v2.intValue());
        case "<":
        	if (v1.type == Type.STRING) {
            	String v1_str = (String)v1.value;
            	String v2_str = (String)v2.value;
            	int res = v1_str.compareTo(v2_str);
            	boolean res_value;
            	if (res < 0) res_value = true;
            	else res_value = false;
            	return new Value(res_value);
        	}
        	else
        		return new Value(v1.intValue() < v2.intValue());
        case "<=":
        	if (v1.type == Type.STRING) {
            	String v1_str = (String)v1.value;
            	String v2_str = (String)v2.value;
            	int res = v1_str.compareTo(v2_str);
            	boolean res_value;
            	if (res <= 0) res_value = true;
            	else res_value = false;
            	return new Value(res_value);
        	}
        	else
        		return new Value(v1.intValue() <= v2.intValue());
        case ">":
        	if (v1.type == Type.STRING) {
            	String v1_str = (String)v1.value;
            	String v2_str = (String)v2.value;
            	int res = v1_str.compareTo(v2_str);
            	boolean res_value;
            	if (res > 0) res_value = true;
            	else res_value = false;
            	return new Value(res_value);
        	}
        	else
        		return new Value(v1.intValue() > v2.intValue());
        case ">=":
        	if (v1.type == Type.STRING) {
            	String v1_str = (String)v1.value;
            	String v2_str = (String)v2.value;
            	int res = v1_str.compareTo(v2_str);
            	boolean res_value;
            	if (res >= 0) res_value = true;
            	else res_value = false;
            	return new Value(res_value);
        	}
        	else
        		return new Value(v1.intValue() >= v2.intValue());
        case "&": 
            return new Value(v1.boolValue() && v2.boolValue());
        case "|": 
            return new Value(v1.boolValue() || v2.boolValue());            

	    default:
	        throw new IllegalArgumentException("no operation");
	    }
    } 
    
    Value unaryOperation(Operator op, Value v) {
        check( !v.undef, "reference to undef value");
	    switch (op.val) {
        case "!": 
            return new Value(!v.boolValue( ));
	    case "-": 
            return new Value(-v.intValue( ));
        default:
            throw new IllegalArgumentException("no operation: " + op.val); 
        }
    } 

    static void check(boolean test, String msg) {
        if (test) return;
        System.err.println(msg);
    }

    Value V(Expr e, State state) {
        if (e instanceof Value) 
            return (Value) e;
        if (e instanceof Identifier) {
	        Identifier v = (Identifier) e;
            return (Value)(state.get(v));
	    }
        if (e instanceof Array) {
	        Array ar = (Array) e;
            Value i = V(ar.expr, state);
            Value v = (Value) state.get(ar.id);
            Value[] vs = v.arrValue(); 
            return (vs[i.intValue()]); 
	    }
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            Value v1 = V(b.expr1, state);
            Value v2 = V(b.expr2, state);
            return binaryOperation (b.op, v1, v2); 
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            Value v = V(u.expr, state);
            return unaryOperation(u.op, v); 
        }
        if (e instanceof Call) 
    	    return V((Call)e, state);  
        throw new IllegalArgumentException("no operation");
    }

    public static void main(String args[]) {
	    if (args.length == 0) {
	        Sint sint = new Sint(); 
			Lexer.interactive = true;
            System.out.println("Language S Interpreter 1.0");
            System.out.print(">> ");
	        Parser parser  = new Parser(new Lexer());

	        do { // Program = Command*
	            if (parser.token == Token.EOF)
		            parser.token = parser.lexer.getToken();
	       
	            Command command=null;
                try {
	                command = parser.command();
	                 //    if (command != null) command.display(0);    // display AST    
					 if (command == null) 
						 throw new Exception();
					 else  { 
						 command.type = TypeChecker.Check(command); 
//						  System.out.println("\nType: "+ command.type); 
				     }
                } catch (Exception e) {
                    System.out.println("Error: " + e);
		            System.out.print(">> ");
                    continue;
                }

	            if (command.type != Type.ERROR) {
                    System.out.println("\nInterpreting..." );
                    try {
                        state = sint.Eval(command, state);
                    } catch (Exception e) {
                         System.err.println("Error: " + e);  
                    }
                }
		        System.out.print(">> ");
	        } while (true);
	    }
        else {
	        System.out.println("Begin parsing... " + args[0]);
	        Command command = null;
	        Parser parser  = new Parser(new Lexer(args[0]));
	        Sint sint = new Sint();

	        do {	// Program = Command*
	            if (parser.token == Token.EOF)
                    break;
	         
                try {
		            command = parser.command();
					//  if (command != null) command.display(0);      // display AST
					if (command == null) 
						 throw new Exception();
					else  {
						 command.type = TypeChecker.Check(command); 
//                         System.out.println("\nType: "+ command.type);  
				    }
                } catch (Exception e) {
                    System.out.println("Error: " + e);
                    continue;
                }

	            if (command.type!=Type.ERROR) {
                    System.out.println("\nInterpreting..." + args[0]);
                    try {
                        state = sint.Eval(command, state);
                    } catch (Exception e) {
                        System.err.println("Error: " + e);  
                    }
                }
	        } while (command != null);
        }        
    }
}