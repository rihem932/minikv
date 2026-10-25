#include <iostream>
#include <string>

#include "kvstore.hpp"
#include "parser.hpp"

int main() {
    KVStore store;
    std::cout << "MiniKV ready. Commands: SET, GET, DEL, EXISTS, SIZE, QUIT\n";

    std::string line;
    while (true) {
        std::cout << "> " << std::flush;
        if (!std::getline(std::cin, line)) {
            break;  // end of input (Ctrl+D)
        }
        if (line == "QUIT" || line == "quit") {
            break;
        }
        std::string reply = handle_command(store, line);
        if (!reply.empty()) {
            std::cout << reply << "\n";
        }
    }

    std::cout << "Bye.\n";
    return 0;
}
