#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "../src/ray.h"
#include "../src/vec3.h"

TEST_CASE("Ray Construction Test"){
    point3 orig(1.0, 2.0, 3.0);
    vec3 dir(4.0, 5.0, 6.0);
    ray r(orig, dir);

    REQUIRE_THAT(r.getOrigin().x(), Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(r.getOrigin().y(), Catch::Matchers::WithinAbs(2.0, 1e-8));
    REQUIRE_THAT(r.getOrigin().z(), Catch::Matchers::WithinAbs(3.0, 1e-8));

    REQUIRE_THAT(r.getDirection().x(), Catch::Matchers::WithinAbs(4.0, 1e-8));
    REQUIRE_THAT(r.getDirection().y(), Catch::Matchers::WithinAbs(5.0, 1e-8));
    REQUIRE_THAT(r.getDirection().z(), Catch::Matchers::WithinAbs(6.0, 1e-8));
}

TEST_CASE("Ray At Parameter Test"){
    point3 orig(1.0, 2.0, 3.0);
    vec3 dir(4.0, 5.0, 6.0);
    ray r(orig, dir);

    point3 at_point = r.at(2.0);
    REQUIRE_THAT(at_point.x(), Catch::Matchers::WithinAbs(9.0, 1e-8));
    REQUIRE_THAT(at_point.y(), Catch::Matchers::WithinAbs(12.0, 1e-8));
    REQUIRE_THAT(at_point.z(), Catch::Matchers::WithinAbs(15.0, 1e-8));
}

TEST_CASE("Ray Default Constructor Test"){
    ray r;

    REQUIRE_THAT(r.getOrigin().x(), Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(r.getOrigin().y(), Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(r.getOrigin().z(), Catch::Matchers::WithinAbs(0.0, 1e-8));

    REQUIRE_THAT(r.getDirection().x(), Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(r.getDirection().y(), Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(r.getDirection().z(), Catch::Matchers::WithinAbs(0.0, 1e-8));
}

TEST_CASE("Ray At Parameter Negatives And Zero Test"){
    point3 orig(1.0, 1.0, -1.0);
    vec3 dir(0.0, -1.0, 2.0);
    ray r(orig, dir);
    REQUIRE_THAT(r.at(0.0).x(), Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(r.at(0.0).y(), Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(r.at(0.0).z(), Catch::Matchers::WithinAbs(-1.0, 1e-8));
    REQUIRE_THAT(r.at(-1.0).x(), Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(r.at(-1.0).y(), Catch::Matchers::WithinAbs(2.0, 1e-8));
    REQUIRE_THAT(r.at(-1.0).z(), Catch::Matchers::WithinAbs(-3.0, 1e-8));
    REQUIRE_THAT(r.at(3.0).x(), Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(r.at(3.0).y(), Catch::Matchers::WithinAbs(-2.0, 1e-8));
    REQUIRE_THAT(r.at(3.0).z(), Catch::Matchers::WithinAbs(5.0, 1e-8));
}

TEST_CASE("At Parameter With Zero Direction Test"){
    point3 orig(2.0, 3.0, 4.0);
    vec3 dir(0.0, 0.0, 0.0);
    ray r(orig, dir);
    REQUIRE_THAT(r.at(5.0).x(), Catch::Matchers::WithinAbs(2.0, 1e-8));
    REQUIRE_THAT(r.at(5.0).y(), Catch::Matchers::WithinAbs(3.0, 1e-8));
    REQUIRE_THAT(r.at(5.0).z(), Catch::Matchers::WithinAbs(4.0, 1e-8));
}

