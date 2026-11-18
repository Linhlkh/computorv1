#include "main.hpp"

void pushTerm(vector<Term> terms, string textTerm, char signTerm, bool reverse){

}

vector<Term> split_term(string &equa_side, bool reverse) {
    vector<Term> terms;
    string textTerm = "";
    char signTerm = '+';
    int errorSign = 0;

    for (size_t i = 0; i < equa_side.size(); i++) {
        char c = equa_side[i];
        if (c == '+' || c == '-') {
            errorSign = 1;
            if (!trim(textTerm).empty()) {
                pushTerm(terms, textTerm, signTerm, reverse);
            }
        }
    }

}

void check_syntax(string &terms){
    static const regex pattern(
        R"(^(([0-9]+(\.[0-9]+)?)\s*(\*\s*)?)?(X(\^[0-9]+)?)?$)"
    );
    if (!regex_match(terms, pattern) || terms.empty())
        exitErr("Invalid term \"" + terms + "\" (expected format: a, X, a*X, X^p, or a*X^p)");
}

vector<Term> parsing(string &equation) {
    size_t find_equals = equation.find('=');
    if (find_equals == string::npos)
        exitErr("Equation must contain '='");
    if (equation.find('=',find_equals + 1) != string::npos)
        exitErr("Equation must contain only one '='");

    string left_equa = equation.substr(0, find_equals);
    string right_equa = equation.substr(find_equals + 1);

    vector<Term> left_term = split_term(left_equa, true);
    vector<Term> right_term = split_term(right_equa, false);
    for (size_t i = 0; i < right_term.size(); i++)
        left_term.push_back(right_term[i]);
    
    for (size_t i = 0; i < left_term.size(); i++) {
        // cout << "vector term: " << left_term[i].text << endl;
        check_syntax(left_term[i].text);
    }

    return left_term;
}
