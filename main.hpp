#ifndef MAIN_HPP     
#define MAIN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>

using namespace std;

//store seperated parts of equation
struct Term {
    char sign;
    string text;
};

void exitErr(string msg);
string trim(string &equation);
vector<Term> parsing(string &equation);
// vector<double> define_coef(string equation);
// void printReducedForm(vector<double> coef);
// int define_degree(string equation);

#endif
