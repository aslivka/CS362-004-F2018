/* Authors: Riley Kraft (kraftme), Artem Slivka (slivkaa), Andrew Tjossem (tjossema)
 * CS-362-400-F2018
 * Date: 11/30/2018
 * Sources:
 * 	ResultPairs from UrlValidatorTest.java from UrlValidatorCorrect
 */


import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
 /* Function that implements Manual Testing */
   public void testManualTest()
   {
   	UrlValidator urlVal = new UrlValidator(null,null,UrlValidator.ALLOW_ALL_SCHEMES);
	String[] validURLS = {	"http://www.ed.gov",			//standard web address
			   	"http://www.gov.uk",			//different top level domain
			   	"http://www.oregonstate.edu",		//different top level domain
			   	"http://www.amazon.com",		//different top level domain
			   	"http://www.mail.google.com",		//standard web address
			   	"http://mail.google.com",		//removed www.
			   	"www.mail.google.com",			//removed protocol
			   	"http://www.mail.google.com/mail",	//added path
			   	"http://www.mail.google.com/mail/u",	//additional directory
			   	"https://mail.google.com",		//protocol change
			   	"http://www.mail.google.com:55443"	//added port number
	   };
	  
	 String[] invalidURLS = {"ioce;\\mmm.sometjh,cas/\"",		//clearly incorrect address
			   	"mail.google.com",			//removed scheme
			   	"http://www.wikipedia",			//removed top level domain
			   	"http://.com",				//removed site name
			   	"http://www.mail google.com",		//added space in address
			   	"http;//www.mail.google.com",		//semi-colon after scheme
			   	"http://www.",				//removed end of url
			   	".com/path"				//removed first half of url
	   };
	   printTestResults(urlVal,validURLS,"Manual 1: Valid URLS");
	   printTestResults(urlVal,invalidURLS, "Manual 2: Invalid URLS");  
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
	   boolean validUrl = true;
	   System.out.print("\n" + title + "\n");
	   System.out.print("Valid?\tURL\n");
	   for(int i = 0; i < testCases.length; i++) {	
		try {
	           validUrl = urlVal.isValid(testCases[i]);
		}
		catch(Exception | Error e) {
		   System.out.println("FAIL: "+testCases[i]+" caused "+e);
		}
		System.out.print(validUrl + "\t");   
		System.out.print(testCases[i] + "\n");	
	   }
   }
   
   
public void testIsValid(){
	   PrintWriter file = null;
	   try{
		   file = new PrintWriter("testIsValidresults.out", "UTF-8");
	   }
	   catch(Exception | Error e) {
		   System.out.println(e);
	   }
	   
	   UrlValidator urlVal = null;
	   
	   file.println("--------------- Begin Programming Based Testing ---------------");
	   file.println();
	   file.println("--------------------- Test Default Params ---------------------");
	   
	   urlVal = new UrlValidator();
	   testUrlScheme[3].valid = false;
	   tests(urlVal, false, file);
	   testUrlScheme[3].valid = true;
	   
	   file.println();
	   file.println("--------------------- Test Defined Schemes --------------------");
	   
	   String schemes[] = {"http", "ftp"};
	   
	   testUrlScheme[2].valid = false;
	   testUrlScheme[3].valid = false;
	   urlVal = new UrlValidator(schemes);
	   tests(urlVal, false, file);
	   testUrlScheme[2].valid = true;
	   testUrlScheme[3].valid = true;
	   
	   file.println();
	   file.println("------------------------ Test Options -------------------------");
	   
	   long options = UrlValidator.ALLOW_ALL_SCHEMES + 
			   UrlValidator.ALLOW_2_SLASHES + 
			   UrlValidator.NO_FRAGMENTS + 
			   UrlValidator.ALLOW_LOCAL_URLS;
	   
	   urlVal = new UrlValidator(options);
	   testUrlAuthority[2].valid = true;
	   tests(urlVal, true, file);
	   testUrlAuthority[2].valid = false;
	   
	   file.println();
	   file.println("--------------- Test Defined Schemes & Options ----------------");
	   
	   testUrlScheme[2].valid = false;
	   testUrlScheme[3].valid = false;
	   testUrlAuthority[2].valid = true;
	   urlVal = new UrlValidator(schemes, options - UrlValidator.ALLOW_ALL_SCHEMES);
	   tests(urlVal, true, file);
	   testUrlScheme[2].valid = true;
	   testUrlScheme[3].valid = true;
	   testUrlAuthority[2].valid = false;
	   
	   file.println();
	   file.println("---------------- End Programming Based Testing ----------------");
	   
	   file.close();
   }   
   
   public void tests(UrlValidator urlVal, boolean options, PrintWriter file) {
	   String testUrl;
	   boolean validity;
	   boolean result = true;
	   boolean exception = false;
	   ResultPair[] path;
	   
	   if(options == true) {
		   path = testUrlPathOptions;
		   try {
			   result = urlVal.isValid("http://localhost:8080/");
		   }
		   catch(Exception | Error e) {
			   file.println("BASELINE FAIL: http://localhost:8080/ caused "+e);
			   exception = true;
		   }
		   if(result == false && exception == false) {
			   file.println("BASELINE FAIL: http://localhost:8080/ should be valid");
		   }
		   exception = false;
	   }
	   else {
		   path = testUrlPath;
	   }
	   
	   try {
		   result = urlVal.isValid("http://www.google.com/");
	   }
	   catch(Exception | Error e) {
		   file.println("BASELINE FAIL: http://www.google.com/ caused "+e);
		   exception = true;
	   }
	   if(result == false && exception == false) {
		   file.println("BASELINE FAIL: http://www.google.com/ should be valid");
	   }
	   exception = false;
	   
	   try {
		   result = urlVal.isValid(null);
	   }
	   catch(Exception | Error e) {
		   file.println("BASELINE FAIL: null caused "+e);
		   exception = true;
	   }
	   if(result == true && exception == false) {
		   file.println("BASELINE FAIL: null should be invalid");
	   }
	   exception = false;
	   
	   for(int i = 0; i < testUrlScheme.length; i++) {
		   for(int j = 0; j < testUrlAuthority.length; j++) {
			   for(int k = 0; k < testUrlPort.length; k++) {
				   for(int m = 0; m < path.length; m++) {
					   for(int n = 0; n < testUrlQuery.length; n++) {
						   testUrl = testUrlScheme[i].item + testUrlAuthority[j].item + testUrlPort[k].item + path[m].item + testUrlQuery[n].item;
						   validity = (testUrlScheme[i].valid && testUrlAuthority[j].valid && testUrlPort[k].valid && path[m].valid && testUrlQuery[n].valid);
					   
						   try {
							   result = urlVal.isValid(testUrl);
						   }
						   catch(Exception | Error e) {
							   file.println("FAIL: "+testUrl+" caused "+e);
							   exception = true;
						   }
						   
						   if(result == false && validity == true && exception == false) {
							   file.println("FAIL: "+testUrlScheme[i].item+"("+testUrlScheme[i].valid+") "+testUrlAuthority[j].item+"("+testUrlAuthority[j].valid+") "+testUrlPort[k].item+"("+testUrlPort[k].valid+") "+path[m].item+"("+path[m].valid+") "+testUrlQuery[n].item+"("+testUrlQuery[n].valid+") "+" in "+testUrl+" should be valid");
						   }
						   else if(result == true && validity == false && exception == false) {
							   file.println("FAIL: "+testUrlScheme[i].item+"("+testUrlScheme[i].valid+") "+testUrlAuthority[j].item+"("+testUrlAuthority[j].valid+") "+testUrlPort[k].item+"("+testUrlPort[k].valid+") "+path[m].item+"("+path[m].valid+") "+testUrlQuery[n].item+"("+testUrlQuery[n].valid+") "+" in "+testUrl+" should be invalid");
						   }
						   
						   exception = false;
					   } 
				   } 
			   } 
		   }  
	   }	   
   }
 //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("https://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("google.com", true),
                                  new ResultPair("aaa", false),
                                  new ResultPair("go.au", true),
                                  new ResultPair("www..com", false),
                                  new ResultPair("www.amazon", false),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("google.ala", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair(":-1", false),
                            new ResultPair(":65636",false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testUrlPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair(null, false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };
   
   ResultPair[] testUrlQuery = {new ResultPair("", true),
		   new ResultPair("?action*view", false),
           new ResultPair("?action=edit&mode=up", true)
   };

}
