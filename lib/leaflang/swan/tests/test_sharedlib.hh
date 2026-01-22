// note: this test will pass on windows only currently,
// because it access a windows dll, but you can use sharedlib_t
// on macos and linux too

#ifndef SWAN_TEST_SHAREDLIB_INCLUDED
#define SWAN_TEST_SHAREDLIB_INCLUDED

#include "../sharedlib.hh"
#include "../testing.hh"

class test_sharedlib_t : public swan::testcase_t
{
public:
  typedef int(__stdcall * msg_box_ptr)(const void*, const char*, const char*, unsigned int);

  void test_openlib()
  {
    assert_equal(true, lib.isopen());
  }

  void test_getfunc()
  {
    if (lib.isopen())
    {
      msg_box = msg_box_ptr(lib.funcptr("MessageBoxA"));
      if (assert_notequal(msg_box_ptr(NULL), msg_box))
      {
        msg_box(NULL, "Hello, world!", "Title", 0);
      }

    }
    else
    {
      skip();
    }
  }

  test_sharedlib_t() : testcase_t("sharedlib"), lib("user32"), msg_box(NULL)
  {
    add_test(test_func(&test_sharedlib_t::test_openlib), "Checking that user32 lib is correctly opened");
    add_test(test_func(&test_sharedlib_t::test_getfunc), "Checking that lib contains MessageBoxA function");
  }
private:
  swan::sharedlib_t lib;
  msg_box_ptr msg_box;
};

#endif // SWAN_TEST_SHAREDLIB_INCLUDED
