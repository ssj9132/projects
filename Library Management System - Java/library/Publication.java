package library;
import java.time.LocalDate;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;

/**
  *Publications found in Library
  *@license.agreement Gnu General Public License 3.0
  */

public class Publication
{
	private String title;
	private String author;
	private int copyright;
	private String loanedTo;
	private LocalDate dueDate;
		
	/**
	  *Forming Publication section 
	  *@param title			title of book/video
	  *@param author		name of author
	  *@param copyright		year of copyright
	  */
	
	public Publication(String title, String author, int copyright)
	{
		this.title = title;
		this.author = author;
		this.copyright = copyright;
		
		if((copyright < 1900) || (copyright > LocalDate.now().getYear()))
		{
			throw new IllegalArgumentException("ERROR: Invalid Copyright");
		}
	}
	/**
	  *Open file
	  *@param br 		Buffered Reader variable
	  *@throws IOException   exception for error in reading
	  */
	public Publication(BufferedReader br) throws IOException
	{
		
		this.title     = br.readLine();
		this.author    = br.readLine();
		this.copyright = Integer.parseInt(br.readLine());
		
		String m = br.readLine(); 
		
		if(m.equals("checked in"))
		{
			loanedTo = null;
			dueDate = null;
		}
		else
		{
			loanedTo = br.readLine();
			String duedate = br.readLine();
			dueDate = LocalDate.parse(duedate);
		}
	}
	
	/**
	  *Save file
	  *@param bw 		Buffered Writer variable
	  *@throws IOException   exception for error in reading
	  */
	public void save(BufferedWriter bw) throws IOException
	{
		bw.write("" + title     + '\n');
		bw.write("" + author    + '\n');
		bw.write("" + copyright + '\n');
		
		if(loanedTo == null)
		{
			bw.write("checked in\n");
		}
		else
		{
			bw.write("checked out\n");
			bw.write(loanedTo + '\n');
			bw.write(dueDate.toString()+ '\n');
		}
	}
	/**
	  *Checking out section
	  *@param patron			name of customer/patron
	  */	
	
	public void checkout(String patron)
	{
		this.loanedTo = patron;
		this.dueDate = LocalDate.now().plusDays(14);
	}
	/**
	  *Checking in section
	  */	
	  
	public void checkin()
	{
        loanedTo = null;
        dueDate = null;
    }
	
	/**
	  *Forming the Resultant Strings
	  *@param bk			if it is a book
	  *@param time		    the duration of video
	  *@return				returning the string
	  */
	
	protected String toStringBldr(String bk, String time)
	{
		if(bk == "Book")
		{
			if(loanedTo != null)
			{
				return "Book: "+ title + "\n" + "   Author: " + author + "\n" + "   Copyright Year: " + copyright + "\n" + "   Loaned To: " + loanedTo + "\n" + "   Due by: " + dueDate + "\n";
			}
			else
			{
				return "Book: "+ title + "\n" + "   Author: " + author + "\n" + "   Copyright Year: " + copyright + "\n" ;
			}
		}
		
		else
		{
			if(loanedTo != null)
			{
				return "Video: "+ title + "\n" + "   Author: " + author + "\n" + "   Copyright Year: " + copyright + "\n" + "   Runtime: " + time + " minutes" + "\n" + "   Loaned To: " + loanedTo + "\n" + "   Due by: " + dueDate + "\n";
			}
			else
			{
				return "Video: "+ title + "\n" + "   Author: " + author + "\n" + "   Copyright Year: " + copyright + "\n" + "   Runtime: " + time + " minutes" + "\n" ;
			}
		}
	}
	
	@Override
	public String toString()
	{
		return toStringBldr("Book", "");
	}

}




