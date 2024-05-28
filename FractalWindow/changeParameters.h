#include "Fractal.h"
#pragma once
class changeParameters
{
public:
	double getZoom() { return zoom; };
	double get_w() { return w; };
	void set_w(double x);
	void set_h(double x);
	double get_h() { return h; };
	double getStep() { return step; };
	
	double nuovaCoordinataX(int x);
	double nuovaCoordinataY(int y);
	
private:
	 double zoom = 1.0;
	 double step = 20.0;

	 Fractal fractalChange;

	 double w = (fractalChange.getMaxRe() - fractalChange.getMinRe()) * step / fractalChange.getW();
	 double h = (fractalChange.getMaxIm() - fractalChange.getMinIm()) * step / fractalChange.getH();
};

