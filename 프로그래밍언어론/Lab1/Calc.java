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
    	// 표현식은 bexp, aexp, true, false, number 등 다양한 값을 가진다.
    	// 따라서 자료형을 Object로 선언하고 적절한 형변환을 취해 값을 저장한다.
        Object result = expr();
        if (token == '\n') /* end the parse and print the result */
            System.out.println("The result is : "+result);
         else error();
    }

    Object expr() {
        /* <expr> -> <bexp> {& <bexp> | '|'<bexp>} | !<expr> | true | false */
        Object result;
        if (token == '!'){
            // !<expr>
            match('!');
            result = !(boolean)expr();
        }
        else if (token == 't'){
            // true
            match('t');
            result = (boolean)true;
        }
        else if (token == 'f'){
            // false
            match('f');
            // token이 f라면 expr이 하나의 false로 표현된 상태
            result = (boolean)false; // 출력할 값을 false로 설정한다.
        }
        else {
            // token이 !, t, f가 아니라면
            // 결과 값이 논리연산을 통한 true false 값,
            // 산술연산을 통한 숫자의 값을 가진다.
            result = bexp(); // bexp 함수를 실행해 논리연산자가 있는지 확인한다. 
            while (token == '&' || token == '|') {
            	// 논리연산자가 있다면 expr은 boolean자료형으로 표현된다.
                if (token == '&'){
                    match('&'); // token이 &인 것을 확인하고 다음 토큰을 받아온다.
                    Object bResult = bexp();
                    // & 뒤에 계산되는 값을 b_result객체에 저장한다.
                    // && 연산시 java의 특성상 앞의 값이 false라면
                    // 뒤에 오는 값과 상관없이 false값을 반환하기 때문에
                    // result에 false를 입력한다. 이때 버퍼에 남아있는 값이
                    // token에 들어가 parse에러를 발생시킬 수 있기 때문에
                    // 먼저 버퍼 끝까지 연산을 수행한다.
                    result = (boolean)result && (boolean)bResult;
                    // 연산된 객체의 값을 boolean 자료형으로 변환해 값을 저장한다.
                }
                else if (token == '|'){
                    match('|');
                    Object bResult = bexp();
                    // || 연산도 마찬가지로 result가 true면 뒤의 값을
                    // 확인하지 않기 때문에 미리 연산을 수행해둔다.
                    result = (boolean)result || (boolean)bResult;
                }
            }
        }
        return result;
    }

    Object bexp( ) { // 산술연산을 통한 숫자값 혹은 true false 값을 가지는 연산의 표현식
        /* <bexp> -> <aexp> [<relop> <aexp>] */
        Object result;
        int aexp1 = aexp(); // 산술연산의 값 저장
        // 비교연산자가 존재하면 연산자에 따른 true false값을 리턴하고 그렇지 않으면
        // 산술연산결과를 반환한다.
        if (token == '<' || token == '>' || token == '=' || token == '!'){ // <relop>
            /* Check each string using relop(): "<", "<=", ">", ">=", "==", "!=" */
            String Op = relop();
            // relop() 함수로 어떤 Operation을 수행할지 문자열 Op 변수에 저장
            int aexp2 = aexp();
            // 비교연산을 수행할 값을 계산해 2번째 변수에 저장해 연산자에 따른 비교연산을 수행한다.

            // relop()으로 리턴받은 Op의 종류에 따라 다른 결과 계산
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
            else { // <<, >>,... 등 적절한 비교연산자가 아닐 경우 에러를 반환
                result = aexp1; // 선언한 변수에 연산자 이전 계산 결과를 담아둔다.
                error();
            }
        }
        else {
            result = aexp1;
        }
        return result;
    }

    String relop() { // 비교연산자의 종류를 문자열로 반환하는 함수
        /* <relop> -> ( < | <= | > | >= | == | != ) */
        String result = "";
        // 연산의 종류를 저장해리턴할 변수

        // 현재 저장된 token의 종류로 result 결정
        // <, > 연산자의 경우 뒤에 '='가 추가로 들어왔는지 확인
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

    int aexp() { // 단순 숫자값 혹은 산술연산의 표현식
        /* expr -> term { '+' term | '-' term} */
        int result = term();
        // 현재 토큰의 숫자 값 혹은 우선순위가 높은 곱셈, 나눗셈을 연산한 값을
        // result에 저장해둔다.
        
        // 다음 토큰이 '+', 혹은 '-' 라면 뒤에 산술연산의 결과값이 존재  
        while (token == '+' || token == '-') {
            if(token == '+'){ 
                match('+'); // '+' 라면 
                result += term();
                // 뒤값을 계산해 더 한다.
            }
            else { // token이 '+'가 아니라면 while의 조건에 의해 반드시 '-'
                match('-');
                result -= term();
            }
        } // 더 이상 '+', '-'가 없다면 연산이 된 결과 값 반환
        return result;
    }

    int term( ) { // 단순 숫자 값이나, 곱셈, 나눗셈을 계산한 값
    	// aexp 즉 +, - 보다 먼저 계산되기 때문에 연산자 우선순위가 높은 계산이다.
        int result = factor();
        // token에 *이 있다면, aexp와 같은 방식으로 '*', '/'계산
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
        // 더이상 '*','/'가 없다면 계산한 결과 반환
        return result;
    }

    int factor() { // 숫자의 값이나, ()로 묶인 우선 연산해야하는 표현식
        /* <factor> -> [-] ( <number> | (<aexp>) ) */
        // [-] ( '(' expr ')' | number ) 주석으로 설정되어 있었으나
    	// -true, -false, aexp + true, 등의 연산이 정의 되어 있지 않기 때문에
    	// pdf에 제공된 aexp로 작성했습니다.
        int result = 0;
        int isMinus = 0; // -가 있는지를 저장할 변수, -가 있다면 1로 설정
        if(token == '-') {
            match('-');
            isMinus = 1; // token이 -라면 값을 먼저 계산 후, 값에 -1을 곱하는 연산 추가
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
        return result; // 계산한 결과를 반환
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