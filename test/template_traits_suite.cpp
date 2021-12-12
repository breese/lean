#include <lean/detail/template_traits.hpp>

//-----------------------------------------------------------------------------

namespace suite_template_rebind
{

template <typename...> struct test_tuple;

static_assert(std::is_same<lean::template_rebind_t<lean::proto<>, test_tuple>, test_tuple<>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::proto<bool>, test_tuple>, test_tuple<bool>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::proto<bool, int>, test_tuple>, test_tuple<bool, int>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::proto<bool, int, float>, test_tuple>, test_tuple<bool, int, float>>{}, "");

} // namespace suite_template_rebind

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
