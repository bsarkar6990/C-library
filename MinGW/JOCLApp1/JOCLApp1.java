public class JOCLApp1 {
   static {
	  System.loadLibrary("JOCLApp1");
   }
 
   // Declare an instance native method sayHello() which receives no parameter and returns void
   private native String callGPU();
 
   // Test Driver
   public static void main(String[] args) {
      System.out.println(new JOCLApp1().callGPU());  // Create an instance and invoke the native method
   }
}