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

TEST_CASE("Vec3 Length/Squaring Test"){
    vec3 v(3.0, 4.0, 0.0);

    REQUIRE(v.length_squared() == 25.0);
    REQUIRE_THAT(v.length(), Catch::Matchers::WithinAbs(5.0, 1.0e-3));
    
}

TEST_CASE("Vec3 Negation Test"){
    vec3 v1(1.0, -2.0, 3.0);
    vec3 v2 = -v1;

    REQUIRE(v2.x() == -1.0);
    REQUIRE(v2.y() == 2.0);
    REQUIRE(v2.z() == -3.0);
}

TEST_CASE("Vec3 Division Test"){
    vec3 v1(2.0, 4.0, 6.0);
    double t = 2.0;
    double s = 0.0;
    v1 /= t;

    REQUIRE(v1.x() == 1.0);
    REQUIRE(v1.y() == 2.0);
    REQUIRE(v1.z() == 3.0);
    REQUIRE_THROWS_AS((v1 /= s), std::runtime_error);
    
}


TEST_CASE("Vec3 Dot Product Test"){
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, -5.0, 6.0);
    double dot_product = dot(v1, v2);

    REQUIRE(dot_product == 12.0);
}

