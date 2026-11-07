#include <catch2/catch_test_macros.hpp>

#include "kvstore.hpp"
#include "parser.hpp"

TEST_CASE("SET stores a value that contains spaces") {
    KVStore store;
    REQUIRE(handle_command(store, "SET name Rihem Zorgui") == "OK");
    REQUIRE(handle_command(store, "GET name") == "Rihem Zorgui");
}

TEST_CASE("commands are case-insensitive") {
    KVStore store;
    handle_command(store, "set a 1");
    REQUIRE(handle_command(store, "get a") == "1");
}

TEST_CASE("GET of a missing key prints (nil)") {
    KVStore store;
    REQUIRE(handle_command(store, "GET nothing") == "(nil)");
}

TEST_CASE("DEL, EXISTS and SIZE") {
    KVStore store;
    handle_command(store, "SET a 1");
    REQUIRE(handle_command(store, "EXISTS a") == "1");
    REQUIRE(handle_command(store, "SIZE") == "1");
    REQUIRE(handle_command(store, "DEL a") == "1");
    REQUIRE(handle_command(store, "DEL a") == "0");
    REQUIRE(handle_command(store, "SIZE") == "0");
}

TEST_CASE("unknown commands and empty lines") {
    KVStore store;
    REQUIRE(handle_command(store, "FOO bar").rfind("ERROR", 0) == 0);
    REQUIRE(handle_command(store, "").empty());
}
