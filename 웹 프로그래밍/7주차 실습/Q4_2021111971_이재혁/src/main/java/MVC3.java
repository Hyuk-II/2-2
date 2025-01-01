

import java.io.IOException;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class MVC3
 */
@WebServlet("/LJH3")
public class MVC3 extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public MVC3() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html;charset=UTF-8");
		String c = request.getParameter("color");
		RequestDispatcher d = request.getRequestDispatcher("output.jsp");
		
		if(c.equals("amber")) {
			request.setAttribute("beer1","Jack Amber");
			request.setAttribute("beer2","Red Moose");
			d.forward(request, response);
			
		}else {
			request.setAttribute("beer1","Jail Pale Ale");
			request.setAttribute("beer2","Sout Stout");
			d.forward(request, response);
		}
	}

}
