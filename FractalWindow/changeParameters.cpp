#include "changeParameters.h"



void changeParameters::set_w(double x)
{
    w = x;
}

void changeParameters::set_h(double x)
{
    h = x;
}

double changeParameters::nuovaCoordinataX(int x)
{
    double new_x = fractalChange.getMinRe() + (static_cast<double>(fractalChange.getMaxRe()) - fractalChange.getMinRe()) * x / fractalChange.getW();
    return new_x;
}

double changeParameters::nuovaCoordinataY(int y)
{
    double new_y = -(fractalChange.getMinIm() + (static_cast<double>(fractalChange.getMaxIm()) - fractalChange.getMinIm()) * y / fractalChange.getH());
    return  new_y;
}
