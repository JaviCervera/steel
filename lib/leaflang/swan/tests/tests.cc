#include "test_dir.hh"
#include "test_file.hh"
#include "test_platform.hh"
#include "test_sharedlib.hh"
#include "test_strmanip.hh"
#include "test_time.hh"
#include "test_vector.hh"

using namespace swan;

int main(int argc, const char* argv[])
{
  test_dir_t d;
  test_file_t f;
  test_platform_t p;
  test_sharedlib_t sl;
  test_strmanip_t st;
  test_time_t t;
  test_vector_t v;

  d.run();
  f.run();
  p.run();
  sl.run();
  st.run();
  t.run();
  v.run();
}
