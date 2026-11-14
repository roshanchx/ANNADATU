#include "AnnadatuApp.hpp"
#include "Common.hpp"
#include <iostream>

int main() {
    try {
        annadatu::AnnadatuApp app;
        app.run();
    } catch (const std::exception& ex) {
        std::cerr << "\nAnnadatu error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
