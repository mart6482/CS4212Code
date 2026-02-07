#include "../src/sphere.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Sphere Intersection Test") {
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    REQUIRE(s.intersect(r) == true);
}

TEST_CASE("Sphere No Intersection Test") {
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
    REQUIRE(s.intersect(r) == false);
}

TEST_CASE("Sphere Tangent Intersection Test") {
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);

    ray r(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    REQUIRE(s.intersect(r) == true);
}

TEST_CASE("Sphere Intersection With Ray Origin Inside Sphere Test") {
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);

    ray r(vec3(0.0f, 0.0f, -5.0f), vec3(0.0f, 1.0f, 0.0f));
    REQUIRE(s.intersect(r) == true);
}

TEST_CASE("Sphere Intersection With Ray Pointing Away Test") {
    vec3 center(0.0f, 0.0f, -5.0f);
    float radius = 1.0f;
    sphere s(center, radius);

    ray r(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
    REQUIRE(s.intersect(r) == false);
}    