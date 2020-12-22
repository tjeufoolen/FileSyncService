#include <iostream>
#include "src/Server.h"

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
        std::unique_ptr<Server> s = std::make_unique<Server>(12345);
        s->Run();
    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
