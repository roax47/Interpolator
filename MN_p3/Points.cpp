#include "Points.h"
#include <stdio.h>
#include <math.h>
#include <algorithm> 
Points::Points() {
	this->x = 0;
	this->y = 0;
}

Points::Points(int x,int y) {
	this->x = x;
	this->y = y;
}

double Points::Lagrange(Points *p, double x, int N)
{
	double ret = 0;
	double pi = 1;
	for (int i = 0; i < N; i++) {
		pi = 1;
		for (int j = 0; j < N; j++) {
			if ( j != i){
				pi *= (x - p[j].x) / (p[i].x - p[j].x);
			}
		}
		ret += p[i].y*pi;
	}
	return ret;
}

void Points::Splines(Points* t, Matrix &x, int intervals_number) {

	int coefficients = 4 * intervals_number;
	Matrix b = Matrix(coefficients, 1);
	Matrix m = Matrix(coefficients, coefficients);

	int row = 0;
	for (int i = 0; i < intervals_number; i++) {
		m.values[row][4 * i] = 1;
		b.values[row][0] = t[i].y;
		row++;
		for (int k = 0; k < 4; k++) {
			m.values[row][4 * i + k] = pow((double)(t[i + 1].x - t[i].x), k);
		}
		b.values[row][0] = t[i + 1].y;
		row++;
	}

	for (int i = 0; i < intervals_number - 1; i++) {
		m.values[row][4 * i + 1] = 1;
		m.values[row][4 * i + 2] = 2 * pow((double)(t[i + 1].x - t[i].x), 1);
		m.values[row][4 * i + 3] = 3 * pow((double)(t[i + 1].x - t[i].x), 2);
		m.values[row][4 * i + 5] = -1;
		row++;
		m.values[row][4 * i + 2] = 2;
		m.values[row][4 * i + 3] = 6 * pow((double)(t[i + 1].x - t[i].x), 1);
		m.values[row][4 * i + 6] = -2;
		row++;
	}

	m.values[row][2] = 1;
	row++;

	m.values[row][4 * (intervals_number - 1) + 2] = 2;
	m.values[row][4 * (intervals_number - 1) + 3] = 6 * pow((double)(t[intervals_number].x - t[intervals_number - 1].x), 1);
	

	int matrix_size = coefficients;
	

	Matrix U = m;
	Matrix L = Matrix(matrix_size, matrix_size);
	Matrix P = Matrix(matrix_size, matrix_size);
	L.IdentityMatrix();
	P.IdentityMatrix();

	double pivot = 0.0;
	int index = 0;
	for (int i = 0; i < matrix_size - 1; i++) {
		pivot = 0.0;
		for (int j = i; j < matrix_size; j++) {
			pivot = std::max(abs(U.values[j][i]), pivot);
		}
		for (int k = i; k < matrix_size; k++) {
			if (abs(U.values[k][i]) == pivot) {
				index = k;
				break;
			}
		}
		double temp;
		for (int z = i; z < matrix_size; z++) {

			temp = U.values[i][z];
			U.values[i][z] = U.values[index][z];
			U.values[index][z] = temp;
		}

		for (int z = 0; z < i; z++) {

			temp = L.values[i][z];
			L.values[i][z] = L.values[index][z];
			L.values[index][z] = temp;
		}
		
		for (int z = 0; z < matrix_size; z++) {

			temp = P.values[i][z];
			P.values[i][z] = P.values[index][z];
			P.values[index][z] = temp;
		}


		for (int j = i + 1; j < matrix_size; j++) {
			L.values[j][i] = U.values[j][i] / U.values[i][i];
			for (int k = i; k < matrix_size; k++) {
				U.values[j][k] -= L.values[j][i] * U.values[i][k];
			}
		}

	}
	Matrix temp = Matrix(matrix_size, 1);
	temp = P * b;
	Matrix y = Matrix(matrix_size, 1);
	Matrix::FowardSubstitution(L, y, temp);
	Matrix::BackwardSubstitution(U, x, y);	
}

double Points::ThirdDegreePolymonial(Matrix & m,double x, int interval)
{

	return m.values[interval*4][0]+ (m.values[interval * 4 + 1][0] * pow((double)x, 1)) + (m.values[interval * 4 + 2][0] * pow((double)x, 2)) + (m.values[interval * 4 + 3][0] * pow((double)x, 3));
}
