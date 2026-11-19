#include "main.hpp"

void push_term(vector<Term> &terms, string textTerm, char signTerm, bool reverse){
    string text = trim(textTerm);
    if (text.empty())
        exitErr("Invalid syntax: Empty term");
    if (reverse) {
        signTerm = (signTerm == '+') ? '-' : '+';
    }
    Term term;
    term.sign = signTerm;
    term.text = text;
    terms.push_back(term);
}

vector<Term> split_term(string &equa_side, bool reverse) {
    vector<Term> terms;
    string textTerm = "";
    char signTerm = '+';
    int errorSign = 0;

    for (size_t i = 0; i < equa_side.size(); i++) {
        char c = equa_side[i];
        if (c == '+' || c == '-') {
            if (errorSign != 0)
                exitErr("Invalid syntax: Double sign");
            if (!trim(textTerm).empty()) {
                push_term(terms, textTerm, signTerm, reverse);
            }
            signTerm = c;
            textTerm = "";
            errorSign = 1;
        }
        else {
            textTerm += c;
            if (!trim(textTerm).empty())
                errorSign = false;
        }
        // cout<<textTerm<<endl;
    }
    push_term(terms, textTerm, signTerm, reverse);
    return terms;
}

void check_syntax(string &terms){
    static const regex pattern(
        R"(^([0-9]+(\.[0-9]+)?|([0-9]+(\.[0-9]+)?\s*(\*\s*)?)?X(\^[0-9]+)?)$)"
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

    vector<Term> left_term = split_term(left_equa, false);
    vector<Term> right_term = split_term(right_equa, true);
    for (size_t i = 0; i < right_term.size(); i++)
        left_term.push_back(right_term[i]);
    
    for (size_t i = 0; i < left_term.size(); i++) {
        // cout << "vector term: " << left_term[i].text << endl;
        check_syntax(left_term[i].text);
    }
    return left_term;
}

vector<double> define_coef(vector<Term> &terms) {
    int max_degree = 0;
    for (size_t i = 0; i < terms.size(); i++) {
        size_t power_pos = terms[i].text.find('^');
        int degree = 0;
        if (power_pos != string::npos) {
            degree = stoi(terms[i].text.substr(power_pos + 1));
        }
        else if (terms[i].text.find('X') != string::npos)
            degree = 1;
        if (degree > max_degree)
            max_degree = degree;
    }
    vector<double> coef(max_degree + 1, 0.0);
    for (size_t i = 0; i < terms.size(); i++) {
        size_t power_pos = terms[i].text.find('^');
        size_t star_pos = terms[i].text.find('*');
        size_t x_pos = terms[i].text.find('X');
        
        int degree = 0;
        if (power_pos != string::npos)
            degree = stoi(terms[i].text.substr(power_pos + 1));
        else if (x_pos != string::npos)
            degree = 1;
        
        string val;
        if (star_pos != string::npos)
            val = terms[i].text.substr(0, star_pos);
        else if (x_pos != string::npos)
            val = terms[i].text.substr(0, x_pos);
        else
            val = terms[i].text;
        
        val = trim(val);
        // cout << val << endl;
        double value = val.empty() ? 1.0 : stod(val);
        if (terms[i].sign == '-')
            value = -value;
        coef[degree] += value;
    }
    // for (size_t i = 0; i < coef.size(); i++) {
    //     cout<< "coef: " << coef[i] << endl;
    // }
    return coef;
}

int find_degree(vector<double> &coef) {
    for (int i = (int)coef.size() - 1; i >= 0; i--) {
        if (coef[i] != 0){
            cout << "Polynomial degree: " << i << endl;
            return i;
        }
    }
    cout << "Polynomial degree: 0" << endl;
    return 0;
}

void reduced_form(vector<double> &coef) {
    
}