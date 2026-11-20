
#include "main.hpp"
#include <iostream>

void solve_degree_0(vector<double> &coef){
    if (coef[0] == 0)
        cout << "Any real number is a solution." << endl;
    else
        cout << "No solution." << endl;
}

void solve_degree_1(vector<double> &coef){
    double b = coef[0];
    double a = coef[1];

    if (a == 0)
        solve_degree_0(coef);
    else {
        double solution = -b/a;
        cout << "The solution is:" << endl << format_number(solution) << endl;
        cout << "As an irreducible fraction: " << fraction_to_string(-b, a) << endl;
    }
}

void solve_degree_2(vector<double> &coef) {
    double a = coef[2];
    double b = coef[1];
    double c = coef[0];
    
    double delta = b * b - 4 * a * c;
    if (delta == 0) {
        double solution = -b / (2 * a);
        cout << "Discriminant is 0, the solution is:" << endl << format_number(solution) << endl;
        cout << "As an irreducible fraction: " << fraction_to_string(-b, (2 * a)) << endl;
    }
    else if (delta > 0) {
        double solution1 = (-b + ft_sqrt(delta)) / (2 * a);
        double solution2 = (-b - ft_sqrt(delta)) / (2 * a);
        cout << "Discriminant is strictly positive, the two solutions are:" << endl;
        cout << format_number(solution1) << endl << format_number(solution2) << endl;

        if (is_perfect_square(delta)) {
            cout << "Solution as an irreducible fraction: " << endl;
            cout << fraction_to_string((-b + ft_sqrt(delta)),(2 * a)) << endl;
            cout << fraction_to_string((-b - ft_sqrt(delta)),(2 * a)) << endl;
        }
    }
    else {
        double sqrt_delta = ft_sqrt(-delta);
        double real = -b / (2 * a);
        double imagine = sqrt_delta / (2 * a);

        cout << "Discriminant is strictly negative, the two complex solutions are:" << endl;
        cout << format_number(real) << " + " << format_number(imagine) << "i" << endl;
        cout << format_number(real) << " - " << format_number(imagine) << "i" << endl;

        if (is_perfect_square(-delta)) {
            cout << "Solution as an irreducible fraction: " << endl;
            cout << fraction_to_string((-b), (2 * a)) << " + " << fraction_to_string(sqrt_delta, (2 * a)) << "i" << endl;
            cout << fraction_to_string((-b), (2 * a)) << " - " << fraction_to_string(sqrt_delta, (2 * a)) << "i" << endl;
        }
    }

}

