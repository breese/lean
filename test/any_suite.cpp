#include "test_assert.hpp"
#include <lean/any.hpp>

//-----------------------------------------------------------------------------

namespace unique_any_suite
{

static_assert(std::is_nothrow_default_constructible<lean::unique_any>::value, "default constructible");
static_assert(!std::is_copy_constructible<lean::unique_any>::value, "not copy constructible");
static_assert(std::is_nothrow_move_constructible<lean::unique_any>::value, "move constructible");
static_assert(std::is_constructible<lean::unique_any, int>::value, "value constructible");
#if defined(LEAN_HAS_IN_PLACE_TYPE)
static_assert(std::is_constructible<lean::unique_any, lean::in_place_type_t<int>, int>::value, "inplace constructible");
#endif

static_assert(!std::is_copy_assignable<lean::unique_any>::value, "not copy assignable");
static_assert(std::is_nothrow_move_assignable<lean::unique_any>::value, "move assignable");
static_assert(std::is_assignable<lean::unique_any, int>::value, "value assignable");

void api_ctor_default()
{
    lean::unique_any any;
    assert(!any.has_value());
}

void api_ctor_move()
{
    lean::unique_any any{42};
    assert(any.has_value());

    lean::unique_any copy{std::move(any)};
    assert(!any.has_value());
    assert(copy.has_value());
}

void api_ctor_value()
{
    lean::unique_any any{42};
    assert(any.has_value());
}

void api_ctor_inplace()
{
#if defined(LEAN_HAS_IN_PLACE_TYPE)
    lean::unique_any any{lean::in_place_type<int>, 42};
    assert(any.has_value());
    assert(any.holds<int>());
#endif
}

void api_assign_move()
{
    lean::unique_any any{42};
    assert(any.has_value());

    lean::unique_any copy;
    assert(!copy.has_value());
    copy = std::move(any);
    assert(!any.has_value());
    assert(copy.has_value());
}

void api_assign_value()
{
    lean::unique_any any;
    any = 42;
    assert(any.has_value());
}

void api_has_value()
{
    lean::unique_any any;
    assert(!any.has_value());
    any = 42;
    assert(any.has_value());
}

void api_holds()
{
    struct unknown {};

    {
        lean::unique_any any;
        assert(any.holds<void>());
        assert(!any.holds<int>());
        assert(!any.holds<unknown>());
    }
    {
        lean::unique_any any{42};
        assert(!any.holds<void>());
        assert(any.holds<int>());
        assert(!any.holds<unknown>());
    }
}

void api_holds_decay()
{
    {
        lean::unique_any any;
        assert(!any.holds<int>());
        assert(!any.holds<int&>());
        assert(!any.holds<const int&>());
        assert(!any.holds<volatile int&>());
        assert(!any.holds<const volatile int&>());
    }
    {
        lean::unique_any any{42};
        assert(any.holds<int>());
        assert(any.holds<int&>());
        assert(any.holds<const int&>());
        assert(any.holds<volatile int&>());
        assert(any.holds<const volatile int&>());
    }
}

void api_emplace()
{
    lean::unique_any any;
    assert(any.holds<void>());

    auto& v = any.emplace<int>(42);
    assert(any.holds<int>());
    assert(v == 42);
}

void api_reset()
{
    lean::unique_any any{42};
    assert(any.has_value());
    assert(any.holds<int>());

    any.reset();
    assert(!any.has_value());
    assert(!any.holds<int>());
}

void api_swap()
{
    lean::unique_any alpha;
    lean::unique_any bravo{42};
    assert(alpha.holds<void>());
    assert(bravo.holds<int>());

    alpha.swap(bravo);
    assert(alpha.holds<int>());
    assert(bravo.holds<void>());
}

void run()
{
    api_ctor_default();
    api_ctor_move();
    api_ctor_value();
    api_ctor_inplace();
    api_assign_move();
    api_assign_value();
    api_has_value();
    api_holds();
    api_holds_decay();
    api_emplace();
    api_reset();
    api_swap();
}

} // namespace unique_any_suite

//-----------------------------------------------------------------------------

int main()
{
    unique_any_suite::run();
    return 0;
}
