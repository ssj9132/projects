package library;
import java.time.Duration;

/**
  *For Invalid Runtime Exception
  *@license.agreement Gnu General Public License 3.0
  */

public class InvalidRuntimeException extends ArithmeticException
{
	  
	/**
	  *Message to indicate invalid runtime exception 
	  *@param msg		message
	  */
	  
	public InvalidRuntimeException(String msg)
	{
		super(msg);
	}

	/**
	  *Indicating invalid runtime exception
	  *@param title		name of book/video
	  *@param time  	duration of video
	  */	
	
	public InvalidRuntimeException(String title, int time)
	{
		super(title + ": invalid runtime " + time);
	}
}
