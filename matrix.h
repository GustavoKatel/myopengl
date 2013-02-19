/*
* Author: Gustavo Brito Sampaio
*/

#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_MAX 4

class Matrix
{

public:
	Matrix();
	void put(int i, int j, float value);
	float get(int i, int j);
	//
	void print();
	//
	void load_zero();
	void load_identity();
	bool is_null();
	//operators
	Matrix operator+(Matrix &m);
	Matrix operator-(Matrix &m);
	Matrix operator*(Matrix &m);
	int operator==(Matrix &m);
	int operator!=(Matrix &m);
	//operators vector
	Vector operator*(Vector &v);
	/*
	* V' = M*V
	*/

private:
	float _matrix[MATRIX_MAX][MATRIX_MAX];
	/*
	*	a00 a01 a02 a03
	*	a10 a11 a12 a13
	*	a20 a21 a22 a23
	*	a30 a31 a32 a33
	*/

};

#endif
