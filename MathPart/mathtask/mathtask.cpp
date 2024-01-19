// mathtask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>

//ofstream ut("test.txt");
//ut << std::fixed << std::setprecision(3);
// 
// 
//x * x * x + 2*x*x + 3;
//3*x*x + 4*x;
//
using namespace std;


double varTheta;
double a = 0.5f;
double b = 0.1f;

double func = a + b * varTheta;
double f(double x) {

    return x * x * x + 2*x*x + 3;
}
double df(double x) {

    return 3*x*x + 4*x;
}
void writeToFile(const char* fileName, double x, double y, double r, double g) {
    ofstream outputFile(fileName, ios::app);  // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << std::fixed << std::setprecision(3);
        outputFile << x << " , " << y << " , " << r << " , " << g << " , ";
        
        
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
        outputFile << " white";  // Use white for y = 0
    }
    outputFile << endl;
    outputFile.close();
}
//std::pair<double, int> newton(double x0, double lower_bound, double upper_bound, const char* fileName) {
//
//    int iter{ 0 };
//    double x = x0;
//    auto fx = f(x0);
//    writeToFile(fileName, x, fx);
//    while (std::abs(fx) > 0.01 && x >= lower_bound && x <= upper_bound) {
//        x = x - fx / df(x);
//        fx = f(x);
//        iter++;
//        writeToFile(fileName, x, fx);
//        cout << " Derivate of x " << df(x) << endl;
//        cout << " X pos: " << x << " Y pos : " << fx << endl;
//    }
//    return std::pair<double, int >(x, iter);
//}

struct Vertex {
    float x, y, z;
    float r, g, b;
    float u, v;


};
void function(int iterations, int start,const char* filename) {
    float n = 0.05f;
    float x0, x1, y0, y1, y2;
    Vertex vertex; // x ,y , z, r, g, b, u, v
    vector<Vertex> mVertices;
    x0 = 0.00f, y0 = 0.0f;
    for (int i = start; i < iterations; i++) {
        //float x = i * n;

        //float y = x * x;

        x1 = i * n;
        y1 = x1 * x1 * x1 + 2 * x1 * x1 + 3;
        y2 = 3 * x1 * x1 + 4 * x1;
        x0 = x1;
        y0 = x1;
        vertex.x = x1;
        vertex.y = y1;

        if (y1 > y0) {
            //rising
            vertex.r = 0.0f;
            vertex.g = 1.0f;
            vertex.b = 0.0f;
        }
        else {
            //decreasing
            vertex.r = 1.0f;
            vertex.g = 0.0;
            vertex.b = 0.0f;
        }
        mVertices.push_back(vertex);
        writeToFile(filename, vertex.x, vertex.y, vertex.r, vertex.g);
        cout << "X = " << vertex.x << " " << "Y = " << vertex.y  << "The derivate: " << y2 << endl;


    }
}
void SprialFunction(const char* filename) {
    int iterations = 20;
    float n = 0.05f;
    float x0, x1, y0, y1, z1, z0;
    Vertex vertex; // x ,y , z, r, g, b, u, v
    vector<Vertex> mVertices;
    float radius = 0.1f;
    float angularFrequency = 0.1f;
    x0 = 0.00f, y0 = 0.0f, z0 = 0.0f, z1 = 0.0f;
    for (int i = 0; i < iterations; i++) {
        float t = i * n;

        //float y = x * x;
        x1 = radius * std::cos(angularFrequency * t);
        y1 = radius * std::sin(angularFrequency * t);
        z1 = radius * std::sin(angularFrequency * t);

        x0 = x1;
        y0 = y1;
        z0 = z1;
        vertex.x = x1;
        vertex.y = y1;
        vertex.z = z1;

        if (y1 > y0) {
            //rising
            vertex.r = 0.0f;
            vertex.g = 1.0f;
            vertex.b = 0.0f;
        }
        else {
            //decreasing
            vertex.r = 1.0f;
            vertex.g = 0.0;
            vertex.b = 0.0f;
        }
        mVertices.push_back(vertex);
        //writeToFile(filename, vertex.x, vertex.y, vertex.r, vertex.g);
        cout << "X = " << vertex.x << " " << "Y = " << vertex.y << " " << "Z = " << vertex.z << endl;


    }


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
    function(100, 1, outputFileName);
    SprialFunction(outputFileName);

    /*auto par = newton(7, lower_bound, upper_bound, outputFileName);

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
    }*/
    
    




    return 0;
}

