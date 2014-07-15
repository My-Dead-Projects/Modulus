//
//  compile.cpp
//  Modulus
//

#include "compile.h"
#include <list>
#include <iostream>

bool tokenize();
void load_file(std::ifstream&&);

class token_t {
public:
    std::string data;
    enum {
        string,
        number,
        command,
        invalid
    } type;
    token_t() : type(invalid) {}
};

namespace code {
    std::list<std::string> line_list;
    std::list<token_t> token_list;
    
    void print_line_list(std::ostream& out) {
        out<<"---------------"<<std::endl
           <<"** line_list **"<<std::endl
           <<"** ------------"<<std::endl;
        for (auto line : code::line_list) {
            out<<"** "<<line<<std::endl;
        }
        out<<"***************"<<std::endl
           <<"---------------"<<std::endl<<std::endl;
    }
    
    void print_token_list(std::ostream& out) {
        out<<"----------------"<<std::endl
           <<"** token_list **"<<std::endl
           <<"** -------------"<<std::endl;
        for (auto token : code::token_list) {
            out<<"** [";
            switch (token.type) {
                case token_t::string:
                    out<<"str";
                    break;
                case token_t::number:
                    out<<"num";
                    break;
                case token_t::command:
                    out<<"com";
                    break;
                case token_t::invalid:
                    out<<"inv";
                    break;
            }
            out<<"] "<<token.data<<std::endl;
        }
        
        out<<"****************"<<std::endl
           <<"----------------"<<std::endl<<std::endl;
    }
}

std::string compile(std::ifstream&& file) {
    load_file(std::move(file));
    code::print_line_list(std::cout);
    
    if (not tokenize()) { throw "Error: Invalid token";}
    code::print_token_list(std::cout);
    
    return "";
}

bool tokenize() {
    token_t token;
    for (auto line : code::line_list) {
        for (int i = 0, token_length = 0; i < line.length(); i++) {
            if (token.type == token_t::string) {
                if (line[i] == '"') {
                    token.data = line.substr(i-token_length, token_length+1);
                    code::token_list.push_back(std::move(token));
                    token = token_t();
                    token_length = 0;
                } else {
                    token_length++;
                }
            } else if (token.type == token_t::command or
                       token.type == token_t::number) {
                if (line[i] == ' ') {
                    token.data = line.substr(i-token_length, token_length);
                    code::token_list.push_back(std::move(token));
                    token = token_t();
                    token_length = 0;
                } else if (i == line.length()-1) {
                    token.data = line.substr(i-token_length, token_length+1);
                    code::token_list.push_back(std::move(token));
                    token = token_t();
                } else {
                    token_length++;
                }
            } else if (token.type == token_t::invalid) {
                if (line[i] == '"') {
                    token.type = token_t::string;
                    token_length++;
                } else if ((line[i] >= 'a' and line[i] <= 'z') or
                           (line[i] >= 'A' and line[i] <= 'Z')) {
                    token.type = token_t::command;
                    token_length++;
                } else if (line[i] >= '0' and line[i] <= '9') {
                    token.type = token_t::number;
                    token_length++;
                } else {
                    if (token.type == token_t::command) {
                        if (not (line[i] >= 'a' and line[i] <= 'z') or
                            (line[i] >= 'A' and line[i] <= 'Z')) {
                            return false;
                        }
                    } else if (token.type == token_t::number) {
                        if (not (line[i] >= '0' and line[i] <= '9')) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void load_file(std::ifstream&& file) {
    while (file.good()) {
        std::string line;
        getline(file, line);
        code::line_list.push_back(move(line));
        line = std::string();
    }
}
