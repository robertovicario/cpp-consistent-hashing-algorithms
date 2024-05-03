/**
 * @author Roberto Vicario
 */

#pragma onnce

#include <cmath>

double computeMean(const double results[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += results[i];
    }
    return sum / size;
}

double computeVar(const double results[], int size) {
    double mean = computeMean(results, size);
    double sumSquaredDiff = 0;

    for (int i = 0; i < size; i++) {
        sumSquaredDiff += pow(results[i] - mean, 2);
    }

    return sumSquaredDiff / size;
}

double computeStdDev(const double results[], int size) {
    return sqrt(computeVar(results, size));
}
