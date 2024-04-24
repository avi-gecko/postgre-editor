#include "tests.hpp"


TestsRunner::TestsRunner(std::initializer_list<Test*> tests): _tests(tests) {}

TestsRunner::~TestsRunner() {}

void TestsRunner::run()
{
  for (auto test: _tests)
  {
    (*test)();
    delete test;
  }
}


void Test::operator() () {
	std::cout << get_test_name() << ' ' << then().result << std::endl;
}

Test::~Test() {}

TestResult::TestResult(bool result) {TestResult::result = result ? "PASSED" : "FAILED";}

