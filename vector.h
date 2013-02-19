/*
* Author: Gustavo Brito Sampaio
*/

#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_MAX 4

class Vector
{

public:
	Vector(float i=0.0, float j=0.0, float k=0.0, float w=1.0);
	void put(int i, float v);
	float get(int i);
	//
	float magnitude();
	void normalize();
	float scalar(Vector &v);
	//
	void print();
	//operators
	Vector operator*(Vector &v); // mult vetorial
	Vector operator-(); // inverse
private:
	float _vect[VECTOR_MAX];
	/*
	*	a00
	*	a01	
	*	a02
	*	a03
	*
	*/

};

#endif
