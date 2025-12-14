#include "math_funcs.h"

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
void normalizeVector(double* x, double* y)
{
    double length = distanceBetweenPoints(0, 0, *x, *y);

    if(length == 0) return;
    
    (*x) /= length;
    (*y) /= length;
}