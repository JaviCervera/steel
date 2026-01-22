#ifndef SWAN_TESTING_INCLUDED
#define SWAN_TESTING_INCLUDED

#include "strmanip.hh"
#include "time.hh"
#include "vector.hh"

namespace swan
{
  class testcase_t
  {
  public:
    typedef void(testcase_t::*test_func)();

    testcase_t(const char* name) : name(name) {}

    virtual void init() {}
    virtual void setup() {}
    void run();
    void skip() { skip_ = true; }

    template<typename T>
    bool assert_equal(const T& a, const T& b) { return do_assert(a == b); }

    template<typename T>
    bool assert_notequal(const T& a, const T& b) { return do_assert(a != b); }

    template<typename T>
    bool assert_gequal(const T& a, const T& b) { return do_assert(a >= b); }

    template<typename T>
    bool assert_lequal(const T& a, const T& b) { return do_assert(a <= b); }

    template<typename T>
    bool assert_greater(const T& a, const T& b) { return do_assert(a > b); }

    template<typename T>
    bool assert_lesser(const T& a, const T& b) { return do_assert(a < b); }

    static void print_callback(void(*func)(const char*), const char* msg = NULL);
  protected:
    void add_test(test_func f, const char* msg);
  private:
    std::string name;
    std::vector<test_func> test_funcs;
    std::vector<std::string> test_msgs;
    bool assert_ok;
    bool skip_;
    size_t ok_asserts;
    size_t fail_asserts;

    bool do_assert(bool exp);

    static void std_print(const char* s);
  };

  inline void testcase_t::run()
  {
    // init tests
    print_callback(NULL, ("# Testing " + name + "\n").c_str());
    init();
    ok_asserts = 0;
    fail_asserts = 0;

    // run tests
    unsigned int prev_ms = time::millisecs();
    for (size_t i = 0; i < test_funcs.size(); ++i)
    {
      // init environment
      setup();
      assert_ok = true;
      skip_ = false;

      // run test
      unsigned int prev_ms = time::millisecs();
      (this->*test_funcs[i])();
      unsigned int current_ms = time::millisecs();

      // print output
      std::string msg = "* " + test_msgs[i] +
        " -> " +
        (skip_ ? "SKIP" : (assert_ok ? "OK" : "FAIL")) +
        " (" + strmanip::fromdouble((current_ms - prev_ms) / 1000.0) + "s)"
        "\n";
      print_callback(NULL, msg.c_str());
    }
    unsigned int current_ms = time::millisecs();

    // print results
    std::string msg = "> Finished " + strmanip::fromint(test_funcs.size()) + " tests (" +
      strmanip::fromdouble((current_ms - prev_ms) / 1000.0) + "s)\n";
    print_callback(NULL, msg.c_str());
    print_callback(NULL, ("> * " + strmanip::fromint(ok_asserts) + " passed assertions\n").c_str());
    print_callback(NULL, ("> * " + strmanip::fromint(fail_asserts) + " failed assertions\n").c_str());
    print_callback(NULL, "\n");
  }

  inline void testcase_t::add_test(test_func f, const char* msg)
  {
    test_funcs.push_back(f);
    test_msgs.push_back(msg);
  }

  inline void testcase_t::print_callback(void(*func)(const char*), const char* msg)
  {
    static void(*callback)(const char*) = std_print;
    if (func)
    {
      callback = func;
    }
    else
    {
      callback(msg);
    }
  }

  inline bool testcase_t::do_assert(bool exp)
  {
    assert_ok = exp;
    if (exp) ++ok_asserts;
    else ++fail_asserts;
    return exp;
  }

  inline void testcase_t::std_print(const char* s)
  {
    printf("%s", s);
  }
} // namespace swan

#endif // SWAN_TESTING_INCLUDED
