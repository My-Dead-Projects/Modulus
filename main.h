//
//  main.h
//  Modulus
//

#ifndef main_h
#define main_h

#include <vector>
#include <string>

class Main {
    std::vector<std::string> p_argv;
public:
    std::vector<std::string> argv() {
        return p_argv;
    }
    std::string arg(size_t n) {
        return p_argv[n];
    }
    int start();
    Main(int argc, const char * argv[]) : p_argv(argc) {
        for (int i = 0; i < argc; i++) {
            p_argv.push_back(std::string(argv[i]));
        }
    }
};

#endif
