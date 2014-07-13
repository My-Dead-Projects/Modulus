//
//  main.cpp
//  Modulus
//

#include "main.h"
#include "compile.h"
#include <fstream>

int main(int argc, const char * argv[]) {
    Main main(argc, argv);
    return main.start();
}

int Main::start() {
    
    for (int i = 1; i < argv().size(); i++) {
        std::ifstream file(arg(i));
        compile(std::move(file));
    }
    
    return 0;
}
