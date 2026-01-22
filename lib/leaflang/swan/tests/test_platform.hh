#ifndef SWAN_TEST_PLATFORM_INCLUDED
#define SWAN_TEST_PLATFORM_INCLUDED

#include "../console.hh"
#include "../platform.hh"
#include "../testing.hh"

class test_platform_t : public swan::testcase_t
{
public:
  void test_platformknown()
  {
    std::string platform_name[] = {"unknown", "windows", "macos", "linux"};
    platform_id_t id = swan::platform::id();
    console::println("* Platform name: " + platform_name[id]);
    assert_notequal<size_t>(punknown, id);
  }

  void test_path()
  {
    std::string path = swan::platform::getenv("PATH");
    console::println("* PATH: " + path);
    assert_notequal<std::string>("", path);
  }

  test_platform_t() : testcase_t("platform")
  {
    add_test(test_func(&test_platform_t::test_platformknown), "Checking that platform is known");
    add_test(test_func(&test_platform_t::test_path), "Checking that PATH env var exist");
  }
};

#endif // SWAN_TEST_PLATFORM_INCLUDED
