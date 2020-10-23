//
// Created by ariel on 21/10/2020.
//

#include <cmath>
#include <exception>
#include <iostream>
#include "anomaly_detection_util.h"

using namespace std;

void myCheckWithTwoVariables(int size, float *varToCheck) {
    if (size <= 0) throw exception();
    if (varToCheck == nullptr) throw exception();
}

void myCheckWithThreeVariables(int size, float *varToOneCheck, float *varToTwoCheck) {
    if (size <= 0) throw exception();
    if (varToOneCheck == nullptr) throw exception();
    if (varToTwoCheck == nullptr) throw exception();
}


float expectation(float *x, int size) {
    myCheckWithTwoVariables(size, x);
    float exp = 0;
    for (int i = 0; i < size; i++) {
        if (x == nullptr) throw exception();
        exp += *x;
        ++x;
    }
    exp = exp / size;
    return exp;
}

float var(float *x, int size) {
    myCheckWithTwoVariables(size, x);
    float var = 0;
    // return the expectation.
    float exp = expectation(x, size);
    for (int i = 0; i < size; i++) {
        if (x == nullptr) throw exception();
        // (xi - expectation)^2.
        var += (*x - exp) * (*x - exp);
        ++x;
    }
    var /= size;
    return var;
}

float avg(float *varToAvg, int size) {
    myCheckWithTwoVariables(size, varToAvg);
    float average = 0;
    int i = 0;
    for (; i < size; ++i) {
        if (varToAvg == nullptr) throw exception();
        average += *varToAvg;
        ++varToAvg;
    }
    return average / size;

}

float cov(float *x, float *y, int size) {
    myCheckWithThreeVariables(size, x, y);
    float covariance = 0;
    float avgX = avg(x, size);
    float avgY = avg(y, size);
    for (int i = 0; i < size; ++i) {
        if (x == nullptr) throw exception();
        if (y == nullptr) throw exception();
        int ff = 8;
        covariance += (*x - avgX) * (*y - avgY);
        ++x;
        ++y;
    }
    return covariance / size;
}

float standardDeviation(float *varToDev, int size) {
    myCheckWithTwoVariables(size, varToDev);
    float standDev = var(varToDev, size);
    return sqrt(standDev);
}

float pearson(float *x, float *y, int size) {
    myCheckWithThreeVariables(size, x, y);
    float standardDeviationOfXY = (standardDeviation(x, size) * standardDeviation(y, size));
    return cov(x, y, size) / standardDeviationOfXY;
}

Line linear_reg(Point **points, int size) {
    if (size <= 0) throw exception();
    if (points== nullptr) throw exception();
    float* x = new float[size];
    float* y = new float[size];
    // loop for getting X and Y values.
    for (int i = 0; i < size; ++i) {
        if ((*points) == nullptr) throw exception();
        x[i] = (*points)->x;
        y[i] = (*points)->y;
        ++points;
    }
    float a = cov(x, y, size) / var(x, size);
    float avgX = avg(x, size);
    float avgY = avg(y, size);
    float b = avgY - (a * avgX);
    return Line(a,b);

}

float dev(Point p, Line l) {
    float y = l.f(p.x);
    float distance = 0;
    /*float distance = abs(p.y-y);*/
    (p.y >= y) ? distance = p.y - y : distance = y - p.y;
    return distance;
}
float dev(Point p,Point** points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}