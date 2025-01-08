package library;
import java.time.Duration;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.IOException;
/**
  *Video from library for checking out
  *@license.agreement Gnu General Public License 3.0
  */

public class Video extends Publication
{
	private Duration time;
	
	/**
	  *Make a video with it's title, author, copyright year and runtime
	  *@param title 		title of video
	  *@param author		writer of video
	  *@param copyright		year of copyright for video
	  *@param time			runtime of video in minutes
	  */
	 
	 public Video(String title, String author, int copyright, int time)
	 {
	 	super(title, author, copyright);
	 	
	 	if(time <= 0)
	 	{
	 		throw new InvalidRuntimeException(title,time);
	 	}
	 	else
	 	{
	 		this.time = Duration.ofMinutes(time);
	 	}
	 }
	/**
	  *Save file
	  *@param bw 		Buffered Writer variable
	  */
	public void save(BufferedWriter bw) throws IOException
	{
		super.save(bw);
		bw.write(""  + (int)(time.getSeconds()/60) + '\n');
	}
	
	/**
	  *Open file
	  *@param br 		Buffered Reader variable
	  *@throws IOException   exception for error in reading
	  */
	public Video(BufferedReader br) throws IOException
	{
		super(br);
		String rt = br.readLine();
		this.time = Duration.ofMinutes(Integer.parseInt(rt));
	}
 
	 @Override
	 public String toString()
	 {
	 	int rtime = (int)(time.getSeconds()/60);
	 	return toStringBldr("Video", Integer.toString(rtime));
	 }
	 
}
