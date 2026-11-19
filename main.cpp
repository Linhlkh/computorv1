#include "main.hpp"

// void solveEquation(string equation){

// }

int main(int ac, char **av) {
    // std::cout << "Hello, World!" << std::endl;
    string line;
    if (ac == 1) {
        cout << "Please enter an equation:" << endl;
        if (!getline(cin, line))
            return 1;
        // if (line.empty())
        //     return 0;
    }
    else if( ac == 2) {
        line = av[1];
    }
    else {
        cerr << "Usage: ./computor \"equation\"" << endl;
        return 1;
    }
    vector<Term> terms = parsing(line);
    // for (size_t i = 0; i < terms.size(); i++)
    // {
    //     cout << "hehe" << endl;
    //     cout << terms[i].text << endl;
    //     cout << terms[i].sign << endl;
    // }
    vector<double> coef = define_coef(terms);
    find_degree(coef);
    // solveEquation(line);
    return 0;
}