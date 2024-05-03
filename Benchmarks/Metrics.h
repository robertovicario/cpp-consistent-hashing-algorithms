/**
 * @author Roberto Vicario
 */

#pragma onnce

#include <cmath>

/**
 * @brief Computes the mean of an array of numbers.
 */
double computeMean(const double results[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += results[i];
    }
    return sum / size;
}

/**
 * @brief Computes the variance of an array of numbers.
 */
double computeVar(const double results[], int size) {
    double mean = computeMean(results, size);
    double sumSquaredDiff = 0;

    for (int i = 0; i < size; i++) {
        sumSquaredDiff += pow(results[i] - mean, 2);
    }

    return sumSquaredDiff / size;
}

/**
 * @brief Computes the standard deviation of an array of numbers.
 */
double computeStdDev(const double results[], int size) {
    return sqrt(computeVar(results, size));
}
