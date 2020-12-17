#include <iostream>
#include "src/client.h"

int main() {
    try {
        std::unique_ptr<client> c = std::make_unique<client>("localhost", "12345", "/dropbox/");
        c->run();
    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
