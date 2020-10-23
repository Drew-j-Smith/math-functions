
#include "polynomial.h"

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

void saveToFile(double low, double high, string x, string y, long double (*function)(double)){
    ofstream outx, outy;
    outx.open(x, ios::out);
    outy.open(y, ios::out);
    if(outx && outy){
        for(long int i = 0; i < math::abs(high - low - math::SMALL_EPSILON) * 100.0; i++){
            outx << low + i / 100.0 << endl;
            outy << function(low + i / 100.0) << endl;
        }
    }

    outx.close();
    outy.close();
}


int main(){
    
    long double arr[] = {1, 2, 3, 4, 5};
    math::Polynomial polynomial(arr, 5);
    cout << math::derivitive(0, polynomial) << endl;
    // cout << math::integral(0, 1, polynomial) << endl;
    

    cout << setprecision(12);
    cout << math::cos(.5) << endl;
    cout << math::sin(.5) << endl;
    cout << math::exp(-1) << endl;

    cout << math::asin(1) << endl;
    cout << math::asin(.5) << endl;
    cout << math::asin(0) << endl;
    cout << math::asin(-.5) << endl;
    cout << math::asin(-1) << endl;
    
    for(int i = 1; i <= 10; i++){
        cout << math::ln(i/2.0) << endl;
    }

    cout << math::pow(11, .5) << endl;

    cout << math::derivitive(.5, math::exp) << endl;
    cout << math::derivitive(.5, math::sin) << endl;
    cout << math::derivitive(.5, math::cos) << endl;
    cout << math::derivitive(0, math::sin) << endl;
    cout << math::derivitive(0, math::cos) << endl;

    // cout << math::integral(0, 1, math::exp) << endl;
    // cout << math::integral(0, 1, math::sin) << endl;
    // cout << math::integral(0, 1, math::cos) << endl;

    saveToFile(0.01, 5.0, "x.txt", "y.txt", math::ln);

    return 0;
}