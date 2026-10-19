#include "kvstore.hpp"

void KVStore::set(const std::string& key, const std::string& value) {
    data_[key] = value;
}

std::optional<std::string> KVStore::get(const std::string& key) const {
    auto it = data_.find(key);
    if (it == data_.end()) {
        return std::nullopt;  // key does not exist
    }
    return it->second;
}

bool KVStore::del(const std::string& key) {
    return data_.erase(key) > 0;  // true if something was deleted
}

bool KVStore::exists(const std::string& key) const {
    return data_.count(key) > 0;
}

std::size_t KVStore::size() const {
    return data_.size();
}
