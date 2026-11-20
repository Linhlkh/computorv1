#ifndef MAIN_HPP     
#define MAIN_HPP

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <stdexcept>
#include <limits>

using namespace std;

//store seperated parts of equation
struct Term {
    char sign;
    string text;
};

//parsing.cpp
vector<Term> parsing(string &equation);
vector<double> define_coef(vector<Term> &terms);
int find_degree(vector<double> &coef);
void reduced_form(vector<double> &coef);

//utils.cpp
void exitErr(string msg);
string trim(string &equation);
string format_number( double value);
double ft_sqrt(double num);
bool is_perfect_square(double num);
long long ft_round(double x);
string fraction_to_string(double numerator, double denominator);

//calculate
void solve_degree_0(vector<double> &coef);
void solve_degree_1(vector<double> &coef);
void solve_degree_2(vector<double> &coef);

#endif
