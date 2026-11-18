#include "main.hpp"

// void solveEquation(string equation){
//     // cout << "calculate " << equation << endl;
//     // if (equation.empty())
//     //     return;
//     vector<Term> terms = parsing(equation);
//     vector<double> coef = define_coef(equation);
//     printReducedForm(coef);
//     int degree = define_degree(equation);
//     double a = coef[2];
//     double b = coef[1];
//     double c = coef[0];
//     switch (degree)
//     {
//     case 0:
        
//         break;
//     case 1:

//     case 2:

//     default:
//         break;
//     }

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
    parsing(line);
    // solveEquation(line);
    return 0;
}