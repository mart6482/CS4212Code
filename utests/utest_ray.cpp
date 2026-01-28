#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../src/ray.h"
#include "../src/vec3.h"

TEST_CASE("Ray Construction Test"){
    point3 orig(1.0, 2.0, 3.0);
    vec3 dir(4.0, 5.0, 6.0);
    ray r(orig, dir);

    REQUIRE(r.getOrigin().x() == 1.0);
    REQUIRE(r.getOrigin().y() == 2.0);
    REQUIRE(r.getOrigin().z() == 3.0);

    REQUIRE(r.getDirection().x() == 4.0);
    REQUIRE(r.getDirection().y() == 5.0);
    REQUIRE(r.getDirection().z() == 6.0);
}

TEST_CASE("Ray At Parameter Test"){
    point3 orig(1.0, 2.0, 3.0);
    vec3 dir(4.0, 5.0, 6.0);
    ray r(orig, dir);

    point3 at_point = r.at(2.0);
    REQUIRE(at_point.x() == 9.0);
    REQUIRE(at_point.y() == 12.0);
    REQUIRE(at_point.z() == 15.0);
}

TEST_CASE("Ray Default Constructor Test"){
    ray r;

    REQUIRE(r.getOrigin().x() == 0.0);
    REQUIRE(r.getOrigin().y() == 0.0);
    REQUIRE(r.getOrigin().z() == 0.0);

    REQUIRE(r.getDirection().x() == 0.0);
    REQUIRE(r.getDirection().y() == 0.0);
    REQUIRE(r.getDirection().z() == 0.0);
}

TEST_CASE("Ray At Parameter Negatives And Zero Test"){
    point3 orig(1.0, 1.0, -1.0);
    vec3 dir(0.0, -1.0, 2.0);
    ray r(orig, dir);
    REQUIRE(r.at(0.0).x() == 1.0);
    REQUIRE(r.at(0.0).y() == 1.0);
    REQUIRE(r.at(0.0).z() == -1.0);
    REQUIRE(r.at(-1.0).x() == 1.0);
    REQUIRE(r.at(-1.0).y() == 2.0);
    REQUIRE(r.at(-1.0).z() == -3.0);
    REQUIRE(r.at(3.0).x() == 1.0);
    REQUIRE(r.at(3.0).y() == -2.0);
    REQUIRE(r.at(3.0).z() == 5.0);
}

TEST_CASE("At Parameter With Zero Direction Test"){
    point3 orig(2.0, 3.0, 4.0);
    vec3 dir(0.0, 0.0, 0.0);
    ray r(orig, dir);
    REQUIRE(r.at(5.0).x() == 2.0);
    REQUIRE(r.at(5.0).y() == 3.0);
    REQUIRE(r.at(5.0).z() == 4.0);
}

