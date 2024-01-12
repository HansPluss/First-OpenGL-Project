// mathtask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

//ofstream ut("test.txt");
//ut << std::fixed << std::setprecision(3);

using namespace std;
double f(double x) {

    return x * x * x + 2*x*x + 3;
}
double df(double x) {

    return 3*x*x + 4*x;
}
void writeToFile(const char* fileName, double x, double y) {
    ofstream outputFile(fileName, ios::app);  // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << " " << y;
        
        
    }
    else {
        cerr << "Unable to open the output file for writing." << endl;
    }
    if (y > 0) {
        outputFile << " green";  // Use green for positive y
    }
    else if (y < 0) {
        outputFile << " red";    // Use red for negative y
    }
    else {
        outputFile << " black";  // Use black for y = 0
    }
    outputFile << endl;
    outputFile.close();
}
std::pair<double, int> newton(double x0, double lower_bound, double upper_bound, const char* fileName) {

    int iter{ 0 };
    double x = x0;
    auto fx = f(x0);
    writeToFile(fileName, x, fx);
    while (std::abs(fx) > 0.01 && x >= lower_bound && x <= upper_bound) {
        x = x - fx / df(x);
        fx = f(x);
        iter++;
        writeToFile(fileName, x, fx);
        cout << " Derivate of x " << df(x) << endl;
        cout << " X pos: " << x << " Y pos : " << fx << endl;
    }
    return std::pair<double, int >(x, iter);
}
int main()
{
    //def mengde
    double lower_bound = -100.0;
    double upper_bound = 100.0;
    const char* outputFileName = "output.txt";

    // Open the file for writing

    
    ofstream clearFile(outputFileName);
    clearFile.close();

    auto par = newton(5, lower_bound, upper_bound, outputFileName);

    if (par.first >= lower_bound && par.first <= upper_bound) {
        std::cout << "Root: " << par.first << " Iterations: " << par.second << std::endl;
    }
    else {
        std::cout << "No root found within the specified interval." << std::endl;
    }
    ofstream updateFile(outputFileName, ios::in | ios::out);
    if (updateFile.is_open()) {
        updateFile.seekp(0);
        updateFile << "Number of Points: " << par.second << endl;
        updateFile.close();
    }
    else {
        cerr << "Error unable to update file" << endl;
    }
    return 0;
}

