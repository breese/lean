#include <lean/detail/template_traits.hpp>

//-----------------------------------------------------------------------------

namespace suite_template_size
{

static_assert(lean::template_size<lean::prototype<>>{} == 0, "");
static_assert(lean::template_size<lean::prototype<bool>>{} == 1, "");
static_assert(lean::template_size<lean::prototype<bool, int>>{} == 2, "");
static_assert(lean::template_size<lean::prototype<bool, int, float>>{} == 3, "");

static_assert(lean::template_size<const lean::prototype<>>{} == 0, "");
static_assert(lean::template_size<const lean::prototype<bool>>{} == 1, "");
static_assert(lean::template_size<const lean::prototype<bool, int>>{} == 2, "");
static_assert(lean::template_size<const lean::prototype<bool, int, float>>{} == 3, "");

} // namespace suite_template_size

//-----------------------------------------------------------------------------

namespace suite_template_element
{

static_assert(std::is_same<lean::template_element_t<0, lean::prototype<bool>>, bool>(), "");
static_assert(std::is_same<lean::template_element_t<0, lean::prototype<bool, int>>, bool>(), "");
static_assert(std::is_same<lean::template_element_t<1, lean::prototype<bool, int>>, int>(), "");
static_assert(std::is_same<lean::template_element_t<0, lean::prototype<bool, int, float>>, bool>(), "");
static_assert(std::is_same<lean::template_element_t<1, lean::prototype<bool, int, float>>, int>(), "");
static_assert(std::is_same<lean::template_element_t<2, lean::prototype<bool, int, float>>, float>(), "");

static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<bool>>, const bool>(), "");
static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<bool, int>>, const bool>(), "");
static_assert(std::is_same<lean::template_element_t<1, const lean::prototype<bool, int>>, const int>(), "");
static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<bool, int, float>>, const bool>(), "");
static_assert(std::is_same<lean::template_element_t<1, const lean::prototype<bool, int, float>>, const int>(), "");
static_assert(std::is_same<lean::template_element_t<2, const lean::prototype<bool, int, float>>, const float>(), "");

static_assert(std::is_same<lean::template_element_t<0, lean::prototype<bool&>>, bool&>(), "");
static_assert(std::is_same<lean::template_element_t<0, lean::prototype<bool&&>>, bool&&>(), "");
static_assert(std::is_same<lean::template_element_t<0, lean::prototype<const bool&>>, const bool&>(), "");
static_assert(std::is_same<lean::template_element_t<0, lean::prototype<const bool&&>>, const bool&&>(), "");

static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<bool&>>, const bool&>(), "");
static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<bool&&>>, const bool&&>(), "");
static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<const bool&>>, const bool&>(), "");
static_assert(std::is_same<lean::template_element_t<0, const lean::prototype<const bool&&>>, const bool&&>(), "");

} // namespace suite_template_element

//-----------------------------------------------------------------------------

namespace suite_template_rebind
{

template <typename...> struct test_tuple;

static_assert(std::is_same<lean::template_rebind_t<lean::prototype<>, test_tuple>, test_tuple<>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::prototype<bool>, test_tuple>, test_tuple<bool>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::prototype<bool, int>, test_tuple>, test_tuple<bool, int>>{}, "");
static_assert(std::is_same<lean::template_rebind_t<lean::prototype<bool, int, float>, test_tuple>, test_tuple<bool, int, float>>{}, "");

} // namespace suite_template_rebind

//-----------------------------------------------------------------------------

int main()
{
    return 0;
}
