#pragma once
#include "threeValuesArray.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>

using namespace sf;
class Fractal
{
	

public:
	//Fractal();

	//methods for the rgb
	int ricorsioniMandelbrot(double cr, double ci, int max_iterations);
	int ricorsioniJuliaSet1(double cr, double ci, int max_iterations);
	int ricorsioniJuliaSet2(double cr, double ci, int max_iterations);
	int ricorsioniBurning_ship(double cr, double ci, int max_iterations);
	sf::Color paint_fractal(int n, int max_iter);
	//get methods
	int getMaxIter() { return max_iter; };
	void setMaxIter(int n);
	int getMinRe() { return min_re; };
	void setMinRe(double x);
	int getMaxRe() { return max_re; };
	void setMaxRe(double x);
	int getMinIm() { return min_im; };
	void setMinIm(double x);
	int getMaxIm() { return max_im; };
	void setMaxIm(double x);
	int getW() { return W; };
	int getH() { return H; };
	int getXfp() { return x_fp; };
	void setXfp(double x_mouse);
	void setYfp(double y_mouse);
	int getYfp() { return y_fp; };
	int getXpoint() { return xPoint; };
	void setXpoint(double x);
	int getYpoint() { return yPoint; };
	void setYpoint(double y);

private:
	 int max_iter { 128 };     //number of iterations
	double min_re { -2 };     //minimum value real axis
	double max_re { 2 };      //maximum value real axis
	double min_im { -2 };    //minimum value immaginary axis
	double max_im { 2 };  
	const double W{ 600 };
	const double H{ 600 };
	int x_fp {0};
	int y_fp {0};
	double xPoint;
	double yPoint;

	const std::vector<sf::Color> colors {
   {0,0,0},
   {213,67,31},
   {251,255,121},
   {62,223,89},
   {43,30,218},
   {0,255,247}
	};

	threeValuesArray arrayToFill;

};

