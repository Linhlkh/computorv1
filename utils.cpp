#include "main.hpp"

void exitErr(string msg) {
    cerr << "Error: " << msg << endl;
    exit(1); 
}

string trim(string &equation){
    size_t start = equation.find_first_not_of(' ');
    size_t end = equation.find_last_not_of(' ');
    if (start == string::npos)
        return "";
    return(equation.substr(start, end - start + 1));
}