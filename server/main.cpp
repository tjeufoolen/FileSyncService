#include <iostream>
#include "src/Server.h"

int main() {
    try {
        std::unique_ptr<Server> s = std::make_unique<Server>(12345, "/dropbox/");
        s->run();
    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
