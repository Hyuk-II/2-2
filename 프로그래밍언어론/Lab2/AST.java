// AST.java
// AST for S
// 2021111971 이재혁

import java.util.*;

class Indent {
    public static void display(int level, String s) {
        String tab = "";
        System.out.println();
        for (int i=0; i<level; i++)
            tab = tab + "    ";
        System.out.print(tab + s);
   }
} 

abstract class Command {
    // Command = Decl | Function | Stmt
    Type type =Type.UNDEF;
    public void display(int l) {  }
}

class Decls extends ArrayList<Decl> {
    // Decls = Decl*
	
    Decls() { super(); };
    Decls(Decl d) {
	    this.add(d);
    }
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Decls"); // Decls AST 출력 
    	// Decls는 ArrayList에 Decl들이 담겨져있는 구조
    	// Decls의 모든 item (Decl) 대해 display를 실행
        for(Decl item: this) {
        	item.display(level+1);
        }
    }
	
}

class Decl extends Command {
    // Decl = Type type; Identifier id 
    Identifier id;
    Expr expr = null;
    int arraysize = 0;

    Decl (String s, Type t) {
        id = new Identifier(s); type = t;
    } // declaration 

    Decl (String s, Type t, int n) {
        id = new Identifier(s); type = t; arraysize = n;
    } // array declaration 

    Decl (String s, Type t, Expr e) {
        id = new Identifier(s); type = t; expr = e;
    } // declaration
   
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Decl");
    	type.display(level+1); // 선언할 변수의 타입 출력
    	id.display(level+1);   // 선언할 변수의 식별자 출력
    	// 선언과 동시에 할당이 있다면, 할당문 출력
    	if(expr != null) {
    		expr.display(level+1);
    	}
    }
}

class Functions extends ArrayList<Function> {
    // Functions = Function*
}

class Function extends Command  {
    // Function = Type type; Identifier id; Decls params; Stmt stmt
    Identifier id;
    Decls params;
    Stmt stmt;
   
    Function(String s, Type t) { 
        id = new Identifier(s); type = t; params = null; stmt = null;
    }

    public String toString ( ) { 
       return id.toString()+params.toString(); 
    }
}

class Type {
    // Type = int | bool | string | fun | array | except | void
    final static Type INT = new Type("int");
    final static Type BOOL = new Type("bool");
    final static Type STRING = new Type("string");
    final static Type VOID = new Type("void");
    final static Type FUN = new Type("fun");
    final static Type ARRAY = new Type("array");
    final static Type EXC = new Type("exc");
    final static Type RAISEDEXC = new Type("raisedexc");
    final static Type UNDEF = new Type("undef");
    final static Type ERROR = new Type("error");
    
    protected String id;
    protected Type(String s) { id = s; } // 변수에 해당 타입을 문자열로 저장
    public String toString ( ) { return id; }
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Type : "+id);
    	// 타입은 최하위 위치
    	// Type과 해당문자열을 출력
    }
}

class ProtoType extends Type {
   // defines the type of a function and its parameters
   Type result;  
   Decls params;
   ProtoType (Type t, Decls ds) {
      super(t.id);
      result = t;
      params = ds;
   }
}

abstract class Stmt extends Command {
    // Stmt = Empty | Stmts | Assignment | If  | While | Let | Read | Print
}

class Empty extends Stmt {
    public void display (int level) {
        Indent.display(level, "Empty");
     }
}

class Stmts extends Stmt {
    // Stmts = Stmt*
    public ArrayList<Stmt> stmts = new ArrayList<Stmt>();
    // Stmt들을 담는 AraayList 멤버 변수
    
    Stmts() {
	    super(); 
    }

    Stmts(Stmt s) {
	     stmts.add(s);
    }
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Stmts");
    	for (Stmt item: stmts) {          
    		item.display(level+1);
    		// 멤버 변수에 저장된 모든 stmt출력
    	}
    }
}

class Assignment extends Stmt {
    // Assignment = Identifier id; Expr expr
    Identifier id; // 할당할 변수의 식별
    Array ar = null;
    Expr expr; // 변수에 할당할 값

    Assignment (Identifier t, Expr e) {
        id = t;
        expr = e;
    }

    Assignment (Array a, Expr e) {
        ar = a;
        expr = e;
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Assignment");
    	id.display(level+1); // 변수 이름 (식별자) 출력
    	expr.display(level+1); // 변수에 할당할 값 출력
    }
}

class If extends Stmt {
    // If = Expr expr; Stmt stmt1, stmt2;
    Expr expr; // 조건식
    Stmt stmt1, stmt2;
    // stmt1 : if 조건이 참일 때 실행
    // stmt2 : if 조건이 거짓일 때 (else) 시행
    
    If (Expr t, Stmt tp) { // else가 없는 if문
        expr = t; stmt1 = tp; stmt2 = new Empty( );
    }
    
    If (Expr t, Stmt tp, Stmt ep) { // else가 있는 if문
        expr = t; stmt1 = tp; stmt2 = ep; 
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "If");
    	expr.display(level+1); // 조건 출력
    	stmt1.display(level+1); // 조건이 참일 때
    	stmt2.display(level+1); // 조건이 거짓일 때
    	// stmt2가 없을 시 Empty 객체 이기 때문에 따로 예외처리 X 
    }
    
}

class While extends Stmt {
    // While = Expr expr; Stmt stmt;
    Expr expr; // 조건식
    Stmt stmt; // 조건이 참인동안 실행

    While (Expr t, Stmt b) {
        expr = t; stmt = b;
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "While");
    	expr.display(level+1);
    	stmt.display(level+1);
    }
}

class Let extends Stmt {
    Decls decls; // 지역 변수 선언
    Functions funs;
    Stmts stmts; // let문에서 작동하는 stmt

    Let(Decls ds, Stmts ss) {
        decls = ds;
		funs = null;
        stmts = ss;
    }

    Let(Decls ds, Functions fs, Stmts ss) {
        decls = ds;
	    funs = fs;
        stmts = ss;
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "LET");
    	decls.display(level+1);
    	stmts.display(level+1);
    }
}

class Read extends Stmt {
    // Read = Identifier id
    Identifier id; // 입력 받을 변수의 식별자

    Read (Identifier v) {
        id = v;
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Read");
    	id.display(level+1);
    }
}

class Print extends Stmt {
    // Print =  Expr expr
    Expr expr; // 출력할 표현식

    Print (Expr e) {
        expr = e;
    }
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Print");
    	expr.display(level+1);
    }
}

class Return extends Stmt {
    Identifier fid;
    Expr expr;

    Return (String s, Expr e) {
        fid = new Identifier(s);
        expr = e;
    }
}

class Try extends Stmt {
    // Try = Identifier id; Stmt stmt1; Stmt stmt2; 
    Identifier eid;
    Stmt stmt1; 
    Stmt stmt2; 

    Try(Identifier id, Stmt s1, Stmt s2) {
        eid = id; 
        stmt1 = s1;
        stmt2 = s2;
    }
}

class Raise extends Stmt {
    Identifier eid;

    Raise(Identifier id) {
        eid = id;
    }
}

class Exprs extends ArrayList<Expr> {
    // Exprs = Expr*
}

abstract class Expr extends Stmt {
    // Expr = Identifier | Value | Binary | Unary | Call

}

class Call extends Expr { 
    Identifier fid;  
    Exprs args;

    Call(Identifier id, Exprs a) {
       fid = id;
       args = a;
    }
}

class Identifier extends Expr {
    // Identifier = String id
    private String id;

    Identifier(String s) { id = s; }

    public String toString( ) { return id; }
    
    public boolean equals (Object obj) {
        String s = ((Identifier) obj).id;
        return id.equals(s);
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Identifier : "+id);
    }
}

class Array extends Expr {
    // Array = Identifier id; Expr expr
    Identifier id;
    Expr expr = null;

    Array(Identifier s, Expr e) {id = s; expr = e;}

    public String toString( ) { return id.toString(); }
    
    public boolean equals (Object obj) {
        String s = ((Array) obj).id.toString();
        return id.equals(s);
    }
}

class Value extends Expr {
    // Value = int | bool | string | array | function 
    protected boolean undef = true;
    Object value = null; // Type type;
    
    Value(Type t) { // 타입 정보를 가지는 value
        type = t;  
        if (type == Type.INT) value = new Integer(0);
        if (type == Type.BOOL) value = new Boolean(false);
        if (type == Type.STRING) value = "";
        undef = false;
    }

    Value(Object v) { // 특정한 값을 가지는 value
        if (v instanceof Integer) type = Type.INT;
        if (v instanceof Boolean) type = Type.BOOL;
        if (v instanceof String) type = Type.STRING;
        if (v instanceof Function) type = Type.FUN;
        if (v instanceof Value[]) type = Type.ARRAY;
        value = v; undef = false; 
    }

    Object value() { return value; }
    
    // value가 나타내는 값 반환하는 메소드
    int intValue( ) { 
        if (value instanceof Integer) 
            return ((Integer) value).intValue(); 
        else return 0;
    }
    
    boolean boolValue( ) { 
        if (value instanceof Boolean) 
            return ((Boolean) value).booleanValue(); 
        else return false;
    } 

    String stringValue ( ) {
        if (value instanceof String) 
            return (String) value; 
        else return "";
    }

    Function funValue ( ) {
        if (value instanceof Function) 
            return (Function) value; 
        else return null;
    }

    Value[] arrValue ( ) {
        if (value instanceof Value[]) 
            return (Value[]) value; 
        else return null;
    }

    Type type ( ) { return type; }

    public String toString( ) {
    	// value가 특정 값을 나타낼 때 문자열로 반환
        //if (undef) return "undef";
        if (type == Type.INT) return "" + intValue(); 
        if (type == Type.BOOL) return "" + boolValue();
	    if (type == Type.STRING) return "" + stringValue();
        if (type == Type.FUN) return "" + funValue();
        if (type == Type.ARRAY) return "" + arrValue();
        return "undef";
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Value : "+value);
    }
}

class Binary extends Expr {
// Binary = Operator op; Expr expr1; Expr expr2;
    Operator op; // 2개의 표현식을 연결하는 연산자
    Expr expr1, expr2;

    Binary (Operator o, Expr e1, Expr e2) {
        op = o; expr1 = e1; expr2 = e2;
    } // binary
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Binary");
    	op.display(level+1);
    	expr1.display(level+1);
    	expr2.display(level+1);
    }
}

class Unary extends Expr {
    // Unary = Operator op; Expr expr
    Operator op; // 표현식 앞에 붙는 연산자 ex) '-'
    Expr expr;

    Unary (Operator o, Expr e) {
        op = o; //(o.val == "-") ? new Operator("neg"): o; 
        expr = e;
    } // unary
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Unary");
    	op.display(level+1);
    	expr.display(level+1);
    }
}

class Operator {
    String val; // 연산자를 문자열로 저장
    
    Operator (String s) { 
	val = s; 
    }

    public String toString( ) { 
	return val; 
    }

    public boolean equals(Object obj) { 
	return val.equals(obj); 
    }
    
    // TODO: [Insert the code of display()]
    public void display(int level) {
    	Indent.display(level, "Operator : "+val);
    }
}