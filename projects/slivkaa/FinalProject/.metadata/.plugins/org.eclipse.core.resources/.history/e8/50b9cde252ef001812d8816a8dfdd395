

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
 //You can use this function to implement your manual testing	
   public void testManualTest()
   {
   
	   
   }
    
   /*
    * Used to test scheme(1st part) of url string
    */
   public void testYourSchemePartition()
   {
	 //Url composition: scheme + authority + port + path + query
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
	   String[] testCases = {	"http://www.google.com", 
								"www.google.com"  , 	//bug, should be true
			   					"3ht://www.google.com",	// true
			   					"http:/www.google.com", //bug, should be false
			   					"http:www.google.com",	//false
			   					"://www.google.com",	//false
//			   					"ftp://www.google.com"	//bug, exception: regular expressions are missing 
	   						};
	   
	   printTestResults(urlVal, testCases, "Partition 1: scheme tests");
   }
   
   /*
    * Used to test authority(2nd part) of url string
    */
   public void testYourAuthorityPartition(){
		 //Url composition: scheme + authority + port + path + query
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
		   String[] testCases = {	"http://www.google",		//false
				   					"http://",					//false
				   					"http://0.0.0.0", 			//true
				   					"http://255.255.255.255",	//true
				   					"http://256.256.255.255",	//false
				   					"http://192.168",			//false
				   					"http://192.168.3.4.5",
		   						};
		   printTestResults(urlVal, testCases, "Partition 2: authority tests");
   }
   
   /*
    * Used to test port(3rd part) of url string
    */
   public void testYourPortPartition(){
		 //Url composition: scheme + authority + port + path + query
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
		   String[] testCases = {	"http://www.google.com:80", 
				   					"http://www.google.com:0", 
				   					"http://www.google.com:65535",
				   					"http://www.google.com:65536",
				   					"http://www.google.com:66000", 
				   					"http://www.google.com:port", 
		   						};
		   printTestResults(urlVal, testCases, "Partition 3: port tests");
   }
 
   /*
    * Used to test path(4th part) of url string
    */
   public void testYourPathPartition(){
		 //Url composition: scheme + authority + port + path + query
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
		   String[] testCases = {	"http://www.google.com/path", 
				   					"http://www.google.com/path1/path2", 
				   					"http://www.google.com/path1//path2", 
				   					"http://www.google.com/..",
		   						};
		   printTestResults(urlVal, testCases, "Partition 4: path tests");
   }
   
   /*
    * Used to test query(5th part) of url string
    */
   public void testYourQueryPartition(){
		 //Url composition: scheme + authority + port + path + query
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
		   String[] testCases = {	"http://www.google.com/path?action=view", 
				   					"http://www.google.com/path?action=view&submit=yes",
				   					"http://www.google.com/path?action$view",
				   					"http://www.google.com/path?",
		   						};
		   printTestResults(urlVal, testCases, "Partition 5: query tests");
   }
   
   //You need to create more test cases for your Partitions if you need to 
   public void printTestResults(UrlValidator urlVal, String[] testCases, String title) {
	   System.out.print("\n" + title + "\n");
	   System.out.print("Valid?\tURL\n");
	   for(int i = 0; i < testCases.length; i++) {	
			boolean validUrl = urlVal.isValid(testCases[i]);
			System.out.print(validUrl + "\t");   
		    System.out.print(testCases[i] + "\n");	
	   }
   }
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
