#include "parser.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace {

std::string to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}

}  // namespace

std::string handle_command(KVStore& store, const std::string& line) {
    std::istringstream in(line);
    std::string cmd;
    std::string key;

    in >> cmd;
    if (cmd.empty()) {
        return "";
    }
    cmd = to_upper(cmd);
    in >> key;

    if (cmd == "SET") {
        std::string value;
        std::getline(in >> std::ws, value);  // value may contain spaces
        if (key.empty() || value.empty()) {
            return "ERROR: usage: SET <key> <value>";
        }
        store.set(key, value);
        return "OK";
    }
    if (cmd == "GET") {
        if (key.empty()) {
            return "ERROR: usage: GET <key>";
        }
        auto value = store.get(key);
        return value ? *value : "(nil)";
    }
    if (cmd == "DEL") {
        if (key.empty()) {
            return "ERROR: usage: DEL <key>";
        }
        return store.del(key) ? "1" : "0";
    }
    if (cmd == "EXISTS") {
        if (key.empty()) {
            return "ERROR: usage: EXISTS <key>";
        }
        return store.exists(key) ? "1" : "0";
    }
    if (cmd == "SIZE") {
        return std::to_string(store.size());
    }
    return "ERROR: unknown command '" + cmd + "'";
}
