

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;

/**
 * Servlet implementation class LoginServlet
 */
@WebServlet("/login")
public class LoginServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public LoginServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		request.setCharacterEncoding("UTF-8");
	    response.setContentType("text/html; charset=UTF-8");
	    response.setCharacterEncoding("UTF-8");
		
		String name = request.getParameter("name");
		String phone = request.getParameter("phone");
		String address = request.getParameter("address");
		
		PrintWriter out = response.getWriter();
		
		
		out.println("<HTML>");
		out.println("<HEAD></HEAD>");
		out.println("<BODY>");
		out.println("NAME = " + name + "<br/>");
		out.println("PHONE = " + phone + "<br/>");
		out.println("ADDRESS = " + address + "<br/>");
		out.println("</BODY>");
		out.println("<HTML>");
	}

}
