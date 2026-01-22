#ifndef SWAN_TEST_VECTOR_INCLUDED
#define SWAN_TEST_VECTOR_INCLUDED

#include "../console.hh"
#include "../vector.hh"
#include "../testing.hh"

class foo_t
{
public:
  foo_t() { _handle_statics(1, 0, 0, 0); }
  ~foo_t() { _handle_statics(0, 0, 1, 0); }
  foo_t(const foo_t& other) { _handle_statics(0, 1, 0, 0); }
  static size_t constructor_calls() { return _handle_statics(0, 0, 0, 0); }
  static size_t copy_calls() { return _handle_statics(0, 0, 0, 1); }
  static size_t destructor_calls() { return _handle_statics(0, 0, 0, 2); }
private:
  static size_t _handle_statics(int inc_def, int inc_copy, int inc_dest, size_t get_what)
  {
    static size_t count_def = 0;
    static size_t count_copy = 0;
    static size_t count_dest = 0;
    count_def += inc_def;
    count_copy += inc_copy;
    count_dest += inc_dest;
    switch (get_what)
    {
      case 0: return count_def;
      case 1: return count_copy;
      case 2: return count_dest;
      default: return 0;
    }
  }
};

using namespace swan;

class test_vector_t : public swan::testcase_t
{
public:
  void test_constructor()
  {
    std::vector<foo_t> vec;
    assert_equal<size_t>(0, foo_t::constructor_calls());
    assert_equal<size_t>(0, foo_t::copy_calls());
    assert_equal<size_t>(0, foo_t::destructor_calls());
  }

  void test_constructor2()
  {
    std::vector<foo_t> vec(5);
    assert_equal<size_t>(1, foo_t::constructor_calls());
    assert_equal<size_t>(5, foo_t::copy_calls());
    assert_equal<size_t>(1, foo_t::destructor_calls());
  }

  void test_constructor3()
  {
    std::vector<foo_t> vec(5);
    std::vector<foo_t> vec2(vec);
    assert_equal<size_t>(2, foo_t::constructor_calls());
    assert_equal<size_t>(15, foo_t::copy_calls());
    assert_equal<size_t>(7, foo_t::destructor_calls());
  }

  test_vector_t() : testcase_t("vector")
  {
    add_test(test_func(&test_vector_t::test_constructor), "Checking that empty constructor does not call any instances");
    add_test(test_func(&test_vector_t::test_constructor2), "Checking that constructor calls contained objects constructors");
    add_test(test_func(&test_vector_t::test_constructor3), "Checking that copy constructor calls contained objects constructors");
  }
};

#endif // SWAN_TEST_VECTOR_INCLUDED
