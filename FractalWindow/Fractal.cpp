#include "Fractal.h"
#include <cstdlib>
#include <vector>
using namespace sf;

int Fractal::ricorsioniMandelbrot(double cr, double ci, int max_iterations)
{
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iterations && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }

    return numeroRicorsioni;
}


int Fractal::ricorsioniJuliaSet1(double cr, double ci, int max_iterations)
{
    double parteRealeC = -0.7269, parteImmaginariaC = 0.1889; // costante c di partenza del set
    int numeroRicorsioni = 0;
    while (numeroRicorsioni < max_iterations && cr * cr + ci * ci < 4.0)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;

    }
    return numeroRicorsioni;
}

int Fractal::ricorsioniJuliaSet2(double cr, double ci, int max_iterations)
{
    double parteRealeC = 0.285, parteImmaginariaC = 0.01; // costante c di partenza del set
    int numeroRicorsioni = 0;
    while (numeroRicorsioni < max_iterations && cr * cr + ci * ci < 4.0)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;

    }
    return numeroRicorsioni;
}

int Fractal::ricorsioniBurning_ship(double cr, double ci, int max_iterations)
{
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iterations && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * abs(parteRealeZ * parteImmaginariaZ) + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

sf::Color Fractal::paint_fractal(int n, int max_iter)
{

    static const auto max_color = colors.size() - 1;
    if (n == max_iter)
        n = 0;

    double mu = 1.0 * n / max_iter;
    mu *= max_color;
    auto i_mu = static_cast<size_t>(mu);
    auto color1 = colors[i_mu];
    auto color2 = colors[std::min(i_mu + 1, max_color)];

    auto a = mu - i_mu;
    auto v = color1;
    auto u = color2;

    auto const b = 1 - a;
    return sf::Color(b * v.r + a * u.r, b * v.g + a * u.g, b * v.b + a * u.b);
}

void Fractal::setMaxIter(int n) {

max_iter = n;
}

void Fractal::setMinRe(double x)
{
    min_re = x;
}

void Fractal::setMaxRe(double x)
{
    max_re = x;
}

void Fractal::setMinIm(double x)
{
    min_im = x;
}

void Fractal::setMaxIm(double x)
{
    max_im = x;
}

void Fractal::setXfp(double x_mouse)
{
    x_fp = x_mouse;
}

void Fractal::setYfp(double y_mouse)
{
    y_fp = y_mouse;
}

void Fractal::setXpoint(double x)
{
    xPoint = x;
}

void Fractal::setYpoint(double y)
{
    yPoint = y;
}
