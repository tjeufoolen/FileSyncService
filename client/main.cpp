#include <iostream>
#include "src/Client.h"
#include "src/utils/Logger.h"

/*
 * File management with
 * ,------.                       ,--.
 * |  .-.  \ ,--.--. ,---.  ,---. |  |-.  ,---.,--.  ,--.
 * |  |  \  :|  .--'| .-. || .-. || .-. '| .-. |\  `'  /
 * |  '--'  /|  |   ' '-' '| '-' '| `-' |' '-' '/  /.  \
 * `-------' `--'    `---' |  |-'  `---'  `---''--'  '--'
 *                         `--'
 *
 * Made by Tjeu Foolen
 * Commissioned by Bob Polis (Teacher Avans Hogeschool at Den Bosch)
 * 2 January 2021)
 */

int main() {
    try {
        std::unique_ptr<Client> c = std::make_unique<Client>("localhost", "12345");
        c->run();
    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << Utils::Logger::CRLF;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
