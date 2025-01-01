import java.io.*;

class Calc {
    int token; int value; int ch;
    private PushbackInputStream input;
    final int NUMBER=256;

    Calc(PushbackInputStream is) {
        input = is;
    }

    int getToken( )  { /* tokens are characters */
        while(true) {
            try  {
                ch = input.read();
                if (ch == ' ' || ch == '\t' || ch == '\r') ;
                else
                if (Character.isDigit(ch)) {
                    value = number( );
                    input.unread(ch);
                    return NUMBER;
                }
                else return ch;
            } catch (IOException e) {
                System.err.println(e);
            }
        }
    }

    private int number( )  {
        /* number -> digit { digit } */
        int result = ch - '0';
        try  {
            ch = input.read();
            while (Character.isDigit(ch)) {
                result = 10 * result + ch -'0';
                ch = input.read();
            }
        } catch (IOException e) {
            System.err.println(e);
        }
        return result;
    }

    void error( ) {
        System.out.printf("parse error : %d\n", ch);
        //System.exit(1);
    }

    void match(int c) {
        if (token == c)
            token = getToken();
        else error();
    }

    void command( ) {
        /* command -> expr '\n' */
        Object result = expr();
        if (token == '\n') /* end the parse and print the result */
            System.out.println(result);
        else error();
    }

    Object expr() {
        /* <expr> -> <bexp> {& <bexp> | '|'<bexp>} | !<expr> | true | false */
        Object result;
        if (token == '!'){
            // !<expr>
            match('!');
            result = !(boolean) expr();
        }
        else if (token == 't'){
            // true
            match('t');
            result = (boolean)true;
        }
        else if (token == 'f'){
            // false
            match('f');
            result = (boolean)false;
        }
        else {
            /* <bexp> {& <bexp> | '|'<bexp>} */
            result = bexp();
            while (token == '&' || token == '|') {
                if (token == '&'){
                    match('&');
                    result = (boolean)result && (boolean)bexp();
                }
                else if (token == '|'){
                    match('|');
                    result = (boolean)result || (boolean)bexp();
                }
            }
        }
        return result;
    }

    Object bexp( ) {
        /* <bexp> -> <aexp> [<relop> <aexp>] */
        Object result;
        int aexp1 = aexp();
        if (token == '<' || token == '>' || token == '=' || token == '!'){ // <relop>
            /* Check each string using relop(): "<", "<=", ">", ">=", "==", "!=" */
            String Op = relop();
            // relop() 함수로 어떤 Operation을 수행할지 Op변수에 저장
            int aexp2 = aexp();

            if(Op.equals("<")){
                result = aexp1 < aexp2;
            }
            else if(Op.equals("<=")){
                result = aexp1 <= aexp2;
            }
            else if(Op.equals(">")){
                result = aexp1 > aexp2;
            }
            else if(Op.equals(">=")){
                result = aexp1 >= aexp2;
            }
            else if(Op.equals("==")){
                result = aexp1 == aexp2;
            }
            else if(Op.equals("!=")){
                result = aexp1 != aexp2;
            }
            else {
                result = aexp1;
                error();
            }
            // relop()으로 리턴받은 Op의 종류에 따라 다른 결과 계산
        }
        else {
            result = aexp1;
        }
        return result;
    }

    String relop() {
        /* <relop> -> ( < | <= | > | >= | == | != ) */
        String result = "";
        // 연산의 종류를 저장해리턴할 변수

        // 현재 저장된 token의 종류로 result 결정
        if(token =='<'){
            match('<');
            if(token == '=') {
                match('=');
                result = "<=";
            }
            else result = "<";
        }
        else if(token =='>'){
            match('>');
            if(token == '=') {
                match('=');
                result = ">=";
            }
            else result = ">";
        }
        // bexp에서 =, !로 시작하는 경우는 ==, != 만 존재하기 때문에 
        // 다음 토큰으로 반드시 '=' 가 들어옴
        else if(token =='='){
            match('=');
            if(token == '=') {
                match('=');
                result = "==";
            }
        }
        else if(token =='!'){
            match('!');
            if(token == '=') {
                match('=');
                result = "!=";
            }
        }
        return result;
    }

    // TODO: [Modify code of aexp() for <aexp> -> <term> { + <term> | - <term> }]
    int aexp() {
        /* expr -> term { '+' term | '-' term} */
        int result = term();
        while (token == '+' || token == '-') {
            if(token == '+'){
                match('+');
                result += term();
            }
            else { // token이 '+'가 아니라면 while의 조건에 의해 반드시 '-'
                match('-');
                result -= term();
            }
        }
        return result;
    }

    // TODO: [Modify code of term() for <term> -> <factor> { * <factor> | / <factor>}]
    int term( ) {
        /* term -> factor { '*' factor | '/' factor} */
        int result = factor();
        while (token == '*' || token == '/') {
            if (token == '*'){
                match('*');
                result *= factor();
            }
            else { // token이 '*'가 아니라면 while의 조건에 의해 반드시 '/'
                match('/');
                result /= factor();
            }
        }
        return result;
    }

    int factor() {
        /* factor -> '(' expr ')' | number */
        // TODO: Modify this code to factor -> [-] ( '(' expr ')' | number )
        int result = 0;
        int isMinus = 0; // -가 있는지를 저장할 변수, -가 있다면 1로 설정
        if(token == '-') {
            match('-');
            isMinus = 1; // token이 -라면 계산 후 값에 -1을 곱하는 연산 추가
        }
        if (token == '(') {
            match('(');
            result = aexp();
            match(')');
        }
        else if (token == NUMBER) {
            result = value;
            match(NUMBER); //token = getToken();
        }

        if(isMinus == 1) { // isMinus가 1이면 결과값에 -1이 곱하는 연산 추가
            result *= -1;
        }
        return result;
    }

    void parse( ) {
        token = getToken(); // get the first token
        command();          // call the parsing command
    }

    public static void main(String args[]) {
        Calc calc = new Calc(new PushbackInputStream(System.in));
        while(true) {
            System.out.print(">> ");
            calc.parse();
        }
    }
}