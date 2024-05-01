/**
 * @author Roberto Vicario
 */

#pragma onnce

#include <cmath>

/**
 * @brief Computes the mean of an array of numbers.
 */
double computeMEAN(const double results[], int size) {
    double sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += results[i];
    }
    return sum / size;
}

/**
 * @brief Computes the variance of an array of numbers.
 */
double computeVAR(const double results[], int size) {
    double mean = computeMEAN(results, size);
    double sumSquaredDiff = 0;

    for (int i = 0; i < size; ++i) {
        sumSquaredDiff += pow(results[i] - mean, 2);
    }

    return sumSquaredDiff / size;
}

/**
 * @brief Computes the standard deviation of an array of numbers.
 */
double computeSTDDEV(const double results[], int size) {
    return sqrt(computeVAR(results, size));
}
