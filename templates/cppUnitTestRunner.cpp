#ifdef NICE_USELIB_CPPUNIT
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#endif

/**
 * CppUnit-Testrunner
 */
int main(int argc, char* argv[]) {
// shut up warnings
(void)argc;
(void)argv;
#ifdef NICE_USELIB_CPPUNIT
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter(
    new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    
  // Run the tests
  bool wasSucessful = runner.run();

  // Return error code 1 if one of tests failed.
  return wasSucessful ? 0 : 1;
#else
#error "Install cppunit (http://cppunit.sourceforge.net/cppunit-wiki)" 
  return 1;
#endif
}
