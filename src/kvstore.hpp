#pragma once

#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>

class KVStore {
public:
    KVStore() = default;                              // in-memory only
    explicit KVStore(const std::string& log_path);    // persistent: replays the log

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);
    bool exists(const std::string& key) const;
    std::size_t size() const;

private:
    void replay(const std::string& path);
    void append(const std::string& line);

    std::unordered_map<std::string, std::string> data_;
    std::ofstream log_;  // open only in persistent mode
};
