

public class TestStruct {

//called from jvmstarter.exe program
  public static void entrypoint(String msg[])
  {

     System.out.println( "EntryPoint was called with " + msg.length + " parameters" ) ;
     
     for( int i = 0 ; i < msg.length ; i++ )
     {
        System.out.println("Parameters " + i + " = " + msg[i] ) ;

     }

     System.out.flush() ;
     //System.exit(0) ;
  }
  
  public static void main(String args[])
  {
    System.out.println("Whats up from Main entrypoint must have been called by java.exe" ) ;
    System.exit(0) ;

  }

}