#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// #include <iostream>
// #include <sstream>




namespace math{

const long double EPSILON = 1e-14L;
const long double SMALL_EPSILON = 1e-6L;
const long double PI = 3.1415926535897932L;
const long double E =  2.7182818284590452L;
const int NUM_COEFFICENTS = 30;

long double factorial(int n){
    long double product = 1;
    for(int i = 2; i <= n; i++){
        product *= i;
    }
    return product;
}

long double pow(double a, int b){
    long double product = 1;
    for(int i = 0; i < b; i++){
        product *= a;
    }
    return product;
}

long double abs(double a){
    if(a > 0)
        return a;
    else
        return -a;
}

class Polynomial{
private:
    long double coefficients[NUM_COEFFICENTS];
public:
    Polynomial();
    Polynomial(long double [], int);
    Polynomial(void (*)(int, long double []));

    long double evaluate(double x);

    // string toString();
};

Polynomial::Polynomial(){
    for(int i = 0; i < NUM_COEFFICENTS; i++){
        coefficients[i] = 0;
    }
}

Polynomial::Polynomial(long double coefficients[], int length){
    for(int i = 0; i < NUM_COEFFICENTS; i++){
        if(i < length)
            this->coefficients[i] = coefficients[i];
        else
            this->coefficients[i] = 0;
    }
}

Polynomial::Polynomial(void (*generatorFunction)(int power, long double coeffiecents[])){
    for(int i = 0; i < NUM_COEFFICENTS; i++){
        generatorFunction(i, coefficients);
    }
}

long double Polynomial::evaluate(double x){
    long double sum = 0;
    for (int i = NUM_COEFFICENTS - 1; i >= 0; i--){
        sum += coefficients[i] * pow(x, i);
    }
    return sum;
}

// string Polynomial::toString(){
//     stringstream ss("");
//     for(unsigned int i = 0; i < NUM_COEFFICENTS; i++){
//         ss << coefficients[i] << " x^" << i  << "\n";
//     }
//     return ss.str();
// }

Polynomial sin_taylor_series = Polynomial([](int power, long double* coefficents){
    if(power % 4 == 1)
        coefficents[power] = 1 / factorial(power);
    else if(power % 4 == 3)
        coefficents[power] = -1 / factorial(power);
    else
        coefficents[power] = 0.0L;
});

Polynomial exp_taylor_series = Polynomial([](int power, long double* coefficents){
    coefficents[power] = 1.0L / factorial(power);
});

long double cos(double x){
    return sin_taylor_series.evaluate((PI/2 - x) - 2 * PI * (int)((PI/2 - x) / (2 * PI)));
}

long double sin(double x){
    return sin_taylor_series.evaluate(x - 2 * PI * (int)(x / (2 * PI)));
}

long double exp(double x){
    return exp_taylor_series.evaluate(x - (int)(x + 0.5)) * pow(E, (int)(x + .5));
}

long double binSearch(double val, long double low, long double high, long double (*function)(double)){
    long double mid = (low + high) / 2;
    while (high - low > EPSILON){
        if(function(mid) > val){
            high = mid; 
        }
        else{
            low = mid;
        }
        mid = (low + high) / 2;
    }
    if(abs(mid) < EPSILON)
        return 0.0L;
    else
        return mid;
}

long double asin(double x){
    return binSearch(x, -PI/2, PI/2, sin);
}

long double ln(double x){
    if(x > E)
        return binSearch(x, 1, x, exp);
    else
        return binSearch(x, -1/x, 1, exp);
}

long double pow(double a, double b){
    return exp(b * ln(a));
}

long double derivitive(double x, long double (*function)(double)){
    return function(x + SMALL_EPSILON / 2) / SMALL_EPSILON - function(x - SMALL_EPSILON / 2) / SMALL_EPSILON;
}

long double derivitive(double x, Polynomial p){
    return p.evaluate(x + SMALL_EPSILON / 2) / SMALL_EPSILON - p.evaluate(x - SMALL_EPSILON / 2) / SMALL_EPSILON;
}

long double integral(double lowerBound, double upperBound, long double (*function)(double)){
    long double sum = 0;
    for(long double x = lowerBound; x < upperBound - EPSILON; x += SMALL_EPSILON){
        sum += SMALL_EPSILON * function(x);
    }
    return sum;
}

long double integral(double lowerBound, double upperBound, Polynomial p){
    long double sum = 0;
    for(long double x = lowerBound; x < upperBound - EPSILON; x += SMALL_EPSILON){
        sum += SMALL_EPSILON * p.evaluate(x);
    }
    return sum;
}


}

#endif