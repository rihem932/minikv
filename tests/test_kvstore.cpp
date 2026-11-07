#include <catch2/catch_test_macros.hpp>

#include "kvstore.hpp"

TEST_CASE("set and get a value") {
    KVStore store;
    store.set("name", "Rihem");
    auto value = store.get("name");
    REQUIRE(value.has_value());
    REQUIRE(*value == "Rihem");
}

TEST_CASE("get of a missing key returns nothing") {
    KVStore store;
    REQUIRE_FALSE(store.get("missing").has_value());
}

TEST_CASE("set overwrites an existing value") {
    KVStore store;
    store.set("k", "old");
    store.set("k", "new");
    REQUIRE(*store.get("k") == "new");
    REQUIRE(store.size() == 1);
}

TEST_CASE("del removes a key and reports whether it existed") {
    KVStore store;
    store.set("k", "v");
    REQUIRE(store.del("k"));
    REQUIRE_FALSE(store.exists("k"));
    REQUIRE_FALSE(store.del("k"));
}

TEST_CASE("invalid keys are rejected") {
    KVStore store;
    REQUIRE_THROWS(store.set("", "v"));
    REQUIRE_THROWS(store.set("two words", "v"));
}
