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
    // cout << equa_side << endl;
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

    // cout << "size left_term: " << left_term.size() << endl;
    // cout << "size right_term: " << right_term.size() << endl;
    
    for (size_t i = 0; i < right_term.size(); i++)
        left_term.push_back(right_term[i]);
    
    for (size_t i = 0; i < left_term.size(); i++) {
        // cout << "vector term: " << left_term[i].text << endl;
        check_syntax(left_term[i].text);
    }
    // cout << "size left_term: " << left_term.size() << endl;
    return left_term;
}

vector<double> define_coef(vector<Term> &terms) {
    // if (terms.empty())
    //     cout << "empty term" << endl;

    int max_degree = 0;
    for (size_t i = 0; i < terms.size(); i++) {
        size_t power_pos = terms[i].text.find('^');
        int degree = 0;
        if (power_pos != string::npos) {
            // degree = stoi(terms[i].text.substr(power_pos + 1));
            try {
                degree = stoi(terms[i].text.substr(power_pos + 1));
            } catch (const std::out_of_range&) {
                exitErr("Exponent is too large");
            }
        }
        else if (terms[i].text.find('X') != string::npos)
            degree = 1;
        if (degree > 10000)
            exitErr("Exponent is too large");
        if (degree > max_degree)
            max_degree = degree;
    }
    vector<double> coef(max_degree + 1, 0.0);
    vector<double> largest_term(coef.size(), 0.0);
    for (size_t i = 0; i < terms.size(); i++) {
        // cout <<"jj"<< endl;
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
        // double value = val.empty() ? 1.0 : stod(val);
        double value = 1.0;
        if (!val.empty()) {
            try {
                value = stod(val);
            } catch (const std::out_of_range&) {
                exitErr("Coefficient is out of range");
            }
        }
        if (terms[i].sign == '-')
            value = -value;
        coef[degree] += value;

        double abs_value = (value < 0.0) ? -value : value;
        if (abs_value > largest_term[degree])
            largest_term[degree] = abs_value;
    }

    const double relative_tolerance =
    8.0 * std::numeric_limits<double>::epsilon();

    for (size_t i = 0; i < coef.size(); ++i) {
        double abs_coef = (coef[i] < 0.0) ? -coef[i] : coef[i];
        double tolerance = relative_tolerance * largest_term[i];

        if (abs_coef <= tolerance)
            coef[i] = 0.0;
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
    bool first = true;
    string value_text;
    size_t end = coef.size();

    while (end > 1 && coef[end - 1] == 0.0)
        --end;
    for (size_t i = 0; i < end; i++){
        double val = coef[i];

        if (val == 0.0)
            continue;
        string sign = "+";
        double abs = val;

        if (val < 0) {
            sign = "-";
            abs = -val;
        }
        if (first) {
            if (sign == "-")
                value_text += "-";
            value_text += format_number(abs) + " * X^" + to_string(i);
            first = false;
        }
        else 
            value_text += " " + sign + " " + format_number(abs) + " * X^" + to_string(i);
    }
    if (first)
        value_text = "0";
    value_text += " = 0";
    cout << "Reduced form: " << value_text << endl;
}