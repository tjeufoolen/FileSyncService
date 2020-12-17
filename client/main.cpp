#include <iostream>
#include "src/Client.h"
#include "src/utils/Logger.h"

int main() {
    try {
        std::unique_ptr<Client> c = std::make_unique<Client>("localhost", "12345", "/dropbox/");
        c->run();
    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << Utils::Logger::CRLF;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
