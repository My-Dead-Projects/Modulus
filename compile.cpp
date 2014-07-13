//
//  compile.cpp
//  Modulus
//

#include "compile.h"
#include <list>
#include <iostream>

void tokenize();
void load_file(std::ifstream&&);


namespace code {
    std::list<std::string> line_list;
    std::list<std::string> token_list;
}



std::string compile(std::ifstream&& file) {
    load_file(std::move(file));
    
    for (auto line : code::line_list) {
        std::cout<<line<<std::endl;
    }
    
    tokenize();
    
    for (auto token : code::token_list) {
        std::cout<<token<<" | ";
    }
    std::cout<<std::endl;
    
    return "";
}

void tokenize() {
    for (auto line : code::line_list) {
        for (int i = 0, token_length = 0; i < line.length(); i++) {
            if (line[i] == ' ') {
                code::token_list.push_back(std::move(line.substr(i-token_length,
                                                                 token_length)));
                token_length = 0;
            } else if (i == line.length()-1) {
                code::token_list.push_back(std::move(line.substr(i-token_length,
                                                                 token_length+1)));
            } else {
                token_length++;
            }
        }
    }
}

void load_file(std::ifstream&& file) {
    while (file.good()) {
        std::string line;
        getline(file, line);
        code::line_list.push_back(move(line));
        line = std::string();
    }
}
