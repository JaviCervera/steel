#ifndef SWAN_TEST_DIR_INCLUDED
#define SWAN_TEST_DIR_INCLUDED

#include "../console.hh"
#include "../dir.hh"
#include "../file.hh"
#include "../strmanip.hh"
#include "../testing.hh"

using namespace swan;

class test_dir_t : public testcase_t
{
public:
  void init()
  {
    console::println("* Current dir is '" + dir::current() + "'");
  }

  void test_notempfolder()
  {
    assert_equal(funknown, filetype("_test_tmp"));
  }

  void test_create()
  {
    dir::create("_test_tmp");
    assert_equal(fdir, filetype("_test_tmp"));
  }

  void test_remove()
  {
    dir::remove("_test_tmp");
    assert_equal(funknown, filetype("_test_tmp"));
  }

  void test_contents()
  {
    std::vector<std::string> current_dir = dir::contents(dir::current());
    console::println("* Printing ' " + dir::current() + "' dir contents: ");
    for (
      std::vector<std::string>::const_iterator it = current_dir.begin();
      it != current_dir.end();
      ++it)
    {
      console::println("  * " + *it);
    }

    assert_gequal<size_t>(current_dir.size(), 2);
  }

  void test_change()
  {
    std::string expected_current = strmanip::extractdir(dir::current());
    dir::change("..");
    std::string actual_current = dir::current();
    dir::change("tests");
    assert_equal(expected_current, actual_current);
  }

  test_dir_t() : testcase_t("dir")
  {
    add_test(test_func(&test_dir_t::test_notempfolder), "Checking that temp folder does not exist");
    add_test(test_func(&test_dir_t::test_create), "Checking dir::create");
    add_test(test_func(&test_dir_t::test_remove), "Checking dir::remove");
    add_test(test_func(&test_dir_t::test_contents), "Checking dir::contents");
    add_test(test_func(&test_dir_t::test_change), "Checking dir::change");
  }
};

#endif // SWAN_TEST_DIR_INCLUDED
