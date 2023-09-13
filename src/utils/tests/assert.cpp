
// extern
#include <catch2/catch_test_macros.hpp>

// local
#include <assert.hpp>



bool const assert_exception = true;


TEST_CASE("always assert")
{
    REQUIRE_NOTHROW(always_assert(true));
    REQUIRE_THROWS(always_assert(false));
}

TEST_CASE("debug assert")
{
#ifndef NDEBUG

    REQUIRE_THROWS(debug_assert(false));
    REQUIRE_NOTHROW(debug_assert(true));

#else

    REQUIRE_NOTHROW(debug_assert(false));
    REQUIRE_NOTHROW(debug_assert(true));

#endif
}
