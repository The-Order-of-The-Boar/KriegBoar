
// extern
#include <catch2/catch_test_macros.hpp>

// local
#include <assert.hpp>



TEST_CASE("always assert")
{
    assert_enable_exception_mode();

    REQUIRE_NOTHROW(always_assert(true));
    REQUIRE_THROWS(always_assert(false));
}

TEST_CASE("debug assert")
{
    assert_enable_exception_mode();

#ifndef NDEBUG

    REQUIRE_THROWS(debug_assert(false));
    REQUIRE_NOTHROW(debug_assert(true));

#else

    REQUIRE_NOTHROW(debug_assert(false));
    REQUIRE_NOTHROW(debug_assert(true));

#endif
}
