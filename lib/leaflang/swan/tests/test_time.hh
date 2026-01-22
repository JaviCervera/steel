#ifndef SWAN_TEST_TIME_INCLUDED
#define SWAN_TEST_TIME_INCLUDED

#include "../console.hh"
#include "../time.hh"
#include "../testing.hh"

class test_time_t : public swan::testcase_t
{
public:
  void test_timeinfo()
  {
    swan::timeinfo_t ti = swan::time::timeinfo();
    assert_equal(false, ti.month == 0);
  }

  void test_parse()
  {
    std::string date = swan::time::parsetimeinfo(swan::time::timeinfo());
    console::println("* Current date: " + date);
    assert_notequal<std::string>("", date);
  }

  void test_millisecs()
  {
    assert_notequal(0u, swan::time::millisecs());
  }

  void test_delay()
  {
    swan::timeinfo_t time_before = swan::time::timeinfo();
    swan::time::delay(1000);
    swan::timeinfo_t time_after = swan::time::timeinfo();
    assert_equal(time_after.sec, (time_before.sec + 1) % 60);
  }

  test_time_t() : testcase_t("time")
  {
    add_test(test_func(&test_time_t::test_timeinfo), "Checking that current month is not zero");
    add_test(test_func(&test_time_t::test_parse), "Checking that parsetimeinfo does not return an empty string");
    add_test(test_func(&test_time_t::test_millisecs), "Checking that millisecs does not return zero");
    add_test(test_func(&test_time_t::test_delay), "Checking that delay waits for the correct time");
  }
};

#endif // SWAN_TEST_TIME_INCLUDED
