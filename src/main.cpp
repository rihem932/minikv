#include <iostream>

#include "kvstore.hpp"

int main() {
    KVStore store;

    store.set("name", "Rihem");
    auto v = store.get("name");
    std::cout << "name = " << (v ? *v : "(not found)") << "\n";

    store.del("name");
    auto v2 = store.get("name");
    std::cout << "after delete: " << (v2 ? *v2 : "(not found)") << "\n";

    return 0;
}
