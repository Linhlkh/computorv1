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

string format_number( double value){
    string text_val = to_string(value);
    size_t last_not_zero = text_val.find_last_not_of('0');
    if (last_not_zero != string::npos && text_val[last_not_zero] == '.')
        last_not_zero--;
    return text_val.substr(0, last_not_zero + 1);
}

double ft_sqrt(double num) {
    if (num == 0)
        return 0;
    double guess = num;
    for (int i = 0; i < 100; i++)
        guess = (guess + num/guess)/2.0;
    return guess;
}

long long ft_round(double x) {
    if (x >= 0)
        return (long long)(x + 0.5);
    else
        return (long long)(x - 0.5);
}

bool is_perfect_square(double num) {
    if (num < 0)
        return false;
    double get_sqrt = ft_sqrt(num);
    long long rounded = ft_round(get_sqrt);
    double diff = (double(rounded* rounded) - num);
    if (diff < 0)
        diff = -diff;
    return (diff < 0.0001);
}

long long ft_gdc(long long x, long long y) {
    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;
    while (y != 0) {
        long long temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

string fraction_to_string(double numerator, double denominator) {
    long long scale = 1000;

    long long num = ft_round(numerator * scale);
    long long den = ft_round(denominator * scale);

    long long g = ft_gdc(num, den);

    if (g != 0)
    {
        num /= g;
        den /= g;
    }

    if (den < 0)
    {
        num = -num;
        den = -den;
    }

    if (den == 1)
        return to_string(num);

    return to_string(num) + "/" + to_string(den);
}


