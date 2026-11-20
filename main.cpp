#include "main.hpp"

int main(int ac, char **av) {
    string line;
    if (ac == 1) {
        cout << "Please enter an equation:" << endl;
        if (!getline(cin, line))
            return 1;
    }
    else if( ac == 2)
        line = av[1];
    else {
        cerr << "Usage: ./computorv1 \"equation\"" << endl;
        return 1;
    }
    vector<Term> terms = parsing(line);
    vector<double> coef = define_coef(terms);
    reduced_form(coef);
    int degree = find_degree(coef);
    switch (degree)
    {
    case 0:
        solve_degree_0(coef);
        break;
    case 1:
        solve_degree_1(coef);
        break;
    case 2:
        solve_degree_2(coef);
        break;
    default:
        cout << "The polynomial degree is strictly greater than 2, I can't solve." << endl;
    }
    return 0;
}