#ifdef NICE_USELIB_CPPUNIT
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#endif



/**
 * CppUnit-Testrunner
 */
int main(int argc, char* argv[]) {
// shut up warnings
(void)argc;
(void)argv;
#ifdef NICE_USELIB_CPPUNIT
   CppUnit::TestResult    controller;
   CppUnit::TestResultCollector result;
   controller.addListener(&result);

  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  // Print test in a compiler compatible format.
  CppUnit::CompilerOutputter outputter( &result, std::cerr );
  outputter.write();
    
  // Run the tests
  runner.run( controller );
  std::string sTestName = suite->getName();
  //std::string sTestName = runner.getName();
  sTestName.append( "_testresults.xml");
  std::cout << sTestName <<std::endl;
  std::ofstream xmlFileOut(sTestName.c_str());
  CppUnit::XmlOutputter xmlOut(&result, xmlFileOut);
  xmlOut.write();
  
  // Return error code 1 if one of tests failed.
  return result.wasSuccessful() ? 0 : 1;
#else
#error "Install cppunit (http://cppunit.sourceforge.net/cppunit-wiki)" 
  return 1;
#endif
}
