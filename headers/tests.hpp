#ifndef TESTS_HPP
#define TESTS_HPP

#include <initializer_list>
#include <iostream>

class Test;
using TestResult = struct TestResult;


class TestsRunner
{
public:
  TestsRunner(std::initializer_list<Test*>);
  virtual ~TestsRunner();
  virtual void run();

private:
  std::initializer_list<Test*> _tests;
};


class Test 
{
public:
  void operator() ();
  virtual ~Test();
private:
  virtual const char* get_test_name() = 0;
  virtual void given() = 0;
  virtual void when() = 0;
  virtual TestResult then() = 0;
};


struct TestResult 
{
  TestResult(bool);
  const char* result;
};



#endif
