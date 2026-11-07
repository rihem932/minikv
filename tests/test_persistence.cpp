#include <catch2/catch_test_macros.hpp>

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <string>

#include "kvstore.hpp"

namespace {
// A log file in the temp folder that is removed again when the test ends.
struct TempLog {
    std::string path;
    explicit TempLog(const std::string& name)
        : path((std::filesystem::temp_directory_path() / name).string()) {
        std::remove(path.c_str());
    }
    ~TempLog() { std::remove(path.c_str()); }
};
}  // namespace

TEST_CASE("data survives a restart") {
    TempLog log("minikv_test_restart.log");
    {
        KVStore store(log.path);
        store.set("name", "Rihem Zorgui");
        store.set("city", "Essen");
    }  // store is destroyed here: like quitting the program
    KVStore again(log.path);
    REQUIRE(*again.get("name") == "Rihem Zorgui");
    REQUIRE(again.size() == 2);
}

TEST_CASE("deleted keys stay deleted after a restart") {
    TempLog log("minikv_test_delete.log");
    {
        KVStore store(log.path);
        store.set("a", "1");
        store.set("b", "2");
        store.del("a");
    }
    KVStore again(log.path);
    REQUIRE_FALSE(again.exists("a"));
    REQUIRE(again.exists("b"));
}

TEST_CASE("a half-written last line is ignored and repaired") {
    TempLog log("minikv_test_crash.log");
    {
        KVStore store(log.path);
        store.set("ok", "yes");
    }
    {
        std::ofstream broken(log.path, std::ios::app);
        broken << "SET broken Va";  // simulated crash: no newline at the end
    }
    {
        KVStore store(log.path);
        REQUIRE_FALSE(store.exists("broken"));
        store.set("after", "crash");
    }
    KVStore again(log.path);
    REQUIRE(*again.get("after") == "crash");
    REQUIRE(*again.get("ok") == "yes");
    REQUIRE_FALSE(again.exists("broken"));
}
