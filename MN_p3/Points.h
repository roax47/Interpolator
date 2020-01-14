#ifndef POINTS
#define POINTS

#include "Matrix.h"

class Points
{

private:

public:
	double x;
	double y;
	Points();
	Points(int x, int y);
	static double Lagrange(Points *p,double x,int N);
	static void  Splines(Points* t, Matrix &x, int intervals_number);
	static double ThirdDegreePolymonial(Matrix &m,double x, int interval);
};

#endif  