#include "vec3.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Vec3 Addition Test"){
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, 5.0, 6.0);
    vec3 v3 = v1 + v2;

    REQUIRE(v3.x() == 5.0);
    REQUIRE(v3.y() == 7.0);
    REQUIRE(v3.z() == 9.0);
}

TEST_CASE("Vec3 Multiplication Test"){
    vec3 v1(1.0, 2.0, 0.0);
    vec3 v2(4.0, -5.0, 6.0);
    vec3 v3 = v1 * v2;

    REQUIRE(v3.x() == 4.0);
    REQUIRE(v3.y() == -10.0);
    REQUIRE(v3.z() == 0.0);
}

