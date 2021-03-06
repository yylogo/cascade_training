//
// Created by yylogo on 2/14/16.
//

#include <string>
#include <sstream>
#include "sub_str.h"

/*
 * Copy from:
 * http://stackoverflow.com/questions/236129/split-a-string-in-c
 * */

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}