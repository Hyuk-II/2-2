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
        throw new IllegalArgumentException("no statement");
    }

    State Eval(Empty s, State state) {
        return state;
    }
  
    State Eval(Assignment a, State state) {
    	// replace array element in array represented by array name
        Value v = V(a.expr, state);
        
        if (a.ar == null)
	        return state.set(a.id, v);
        else {	// id[<expr>] = <expr>;
            // TODO: [Fill the code for assignment of an array element]
        	// Assign to the array element id[<expr>] of the array represented by the array name.
        	// Replace array element in array represented by array name (not use state.set(id, value!)
        	// ex) Value[] ar = ....;	// Array can be represented the array of Value
        	//     ar[index] = v;		// Replace array element 
        	
        	
        	// Assignment에 배열(ar)이 존재한다는 것은 이미 state에 id에 해당하는 배열이 push되어 있는 상태
        	// 즉 배열의 <expr> 인덱스에 v를 할당
        	
        	Value[] arr = state.get(a.ar.id).arrValue();
        	// state에서 ar의 id (값을 바꿀 배열)을 탐색, array가 Value형태로 state에 존재
        	// arrValue() 메소드로 Value[] 즉 배열의 형태로 arr 레퍼런스 선언
        	
        	arr[V(a.ar.expr,state).intValue()] = v;
        	// 할당문에 배열이 있다는 것은 배열에 입력할 위치도 있음 (expr)
        	// 배열의 어느 위치에 v를 삽입할지 계산 -> V(a.ar.expr,state)
        	// V()는 Value 객체를 return하기 때문에 intValue() 메소드로 int값으로 반환
        	// 계산한 index로 arr 레퍼런스 값 수정
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
        State s = allocate(l.decls, state);
        s = Eval(l.stmts,s);
	    return free(l.decls, s);
    }

    State allocate (Decls ds, State state) {
    	// add entries for declared variables (ds) on the state
        if (ds != null) {
        	for (Decl decl : ds) 
			    if (decl.arraysize > 0) { // <type> id[n];
	                // TODO: [Fill the code for array allocation]
			    	// Regarding array declaration, 
			    	// create an array (new Value[arraysize])
			    	// and push (id, new Value(array)) to the state.
			    	
			    	Value[] arr = new Value[decl.arraysize]; // decl에 저장된 배열의 크기만큼 Value 배열 레퍼런스를 선언
			    	state.push(decl.id, new Value(arr));     // 선언된 변수 id로 Value 배열 레퍼런스를 Value이 형태로 state에 저장
	            }
	            else if (decl.expr == null)
	                state.push(decl.id, new Value(decl.type));
		        else
			        state.push(decl.id, V(decl.expr, state));
        }
        return state;
    }

    State free (Decls ds, State state) {
    	// free the entries for declared variables (ds) from the state
        if (ds != null) {
	        for (Decl decl : ds) 
	            state.pop();
        }
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
            return new Value(v1.intValue() == v2.intValue());
        case "!=": 
            return new Value(v1.intValue() != v2.intValue());
        case "<": 
            return new Value(v1.intValue() < v2.intValue());
        case "<=": 
            return new Value(v1.intValue() <= v2.intValue());
        case ">": 
            return new Value(v1.intValue() > v2.intValue());
        case ">=": 
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
        if (e instanceof Array) { // id[<expr>]
	        // TODO: [Fill the code for array expr]
        	// For the array represented by the array name,
        	// return the value of the array element id[<expr>]
        	// ex) Value v = (Value) state.get(ar.id);
        	//     Value[] vs = v.arrValue();
        	//     return (vs[index])
        	
        	Array eArr = (Array)e; // e가 Array의 instance이므로, Array로 변환
        	Value[] arr = ((Value)state.get(eArr.id)).arrValue(); // 배열은 Value 형태로 state에 저장, Array의 아이디로 찾은 Value를 배열로 변환     			
        	int index = V(eArr.expr, state).intValue(); // Array객체에 <expr>로 어떤 index의 값에 접근하는지 저장되어 있음
        												// state에 저장된 정보로 expr을 계산후 intValue() 메소드로 index에 저장 
        	return arr[index]; // Value 배열의 index Value 객체를 리턴
        	
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
//					if (command != null) command.display(0);      // display AST
					if (command == null) 
						 throw new Exception();
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