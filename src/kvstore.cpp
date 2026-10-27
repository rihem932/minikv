#include "kvstore.hpp"

#include <filesystem>
#include <sstream>
#include <stdexcept>

KVStore::KVStore(const std::string& log_path) {
    replay(log_path);                          // 1. rebuild data from the old log
    log_.open(log_path, std::ios::app);        // 2. then keep appending to it
    if (!log_) {
        throw std::runtime_error("cannot open log file: " + log_path);
    }
}

void KVStore::replay(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        return;  // no log yet: start empty
    }
    std::string line;
    std::streamoff good_end = 0;  // end of the last complete line
    while (std::getline(in, line)) {
        if (in.eof()) {
            break;  // last line has no '\n': the program crashed while writing it, ignore it
        }
        good_end = in.tellg();
        std::istringstream fields(line);
        std::string cmd;
        std::string key;
        fields >> cmd >> key;
        if (cmd == "SET" && !key.empty()) {
            std::string value;
            std::getline(fields >> std::ws, value);
            data_[key] = value;
        } else if (cmd == "DEL" && !key.empty()) {
            data_.erase(key);
        }
    }
    in.close();
    // Cut off a half-written last line so new writes start on a clean line.
    std::error_code ec;
    auto size = std::filesystem::file_size(path, ec);
    if (!ec && size > static_cast<std::uintmax_t>(good_end)) {
        std::filesystem::resize_file(path, static_cast<std::uintmax_t>(good_end), ec);
    }
}

void KVStore::append(const std::string& line) {
    if (log_.is_open()) {
        log_ << line << '\n';
        log_.flush();  // hand the data to the operating system right away
    }
}

void KVStore::set(const std::string& key, const std::string& value) {
    if (key.empty() || key.find_first_of(" \t\r\n") != std::string::npos ||
        value.find('\n') != std::string::npos) {
        throw std::invalid_argument("invalid key or value");
    }
    data_[key] = value;
    append("SET " + key + " " + value);
}

std::optional<std::string> KVStore::get(const std::string& key) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        return std::nullopt;  // key does not exist
    }
    return it->second;
}

bool KVStore::del(const std::string& key) {
    bool removed = data_.erase(key) > 0;
    if (removed) {
        append("DEL " + key);
    }
    return removed;
}

bool KVStore::exists(const std::string& key) const {
    return data_.count(key) > 0;
}

std::size_t KVStore::size() const {
    return data_.size();
}
