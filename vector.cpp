/*
* Author: Gustavo Brito Sampaio
*/
#include "vector.h"

#include <iostream>
#include <math.h>

Vector::Vector(float i, float j, float k, float w)
{
	this->put(0,i);
	this->put(1,j);
	this->put(2,k);
	this->put(3,w);
}

void Vector::put(int i, float v)
{
	this->_vect[i]=v;
}

float Vector::get(int i)
{
	return _vect[i];
}

float Vector::magnitude()
{
	float s = pow(get(0),2) +
      		pow(get(1),2) +
		pow(get(2),2);
	float n = sqrt( s  );
	return n;
}
void Vector::normalize()
{
	float n =magnitude();
	if(!n)
		return;
	put(0, get(0)/n);
	put(1, get(1)/n);
	put(2, get(2)/n);
}

float Vector::scalar(Vector &v)
{
	float n;
	n = get(0)*v.get(0) +
	    get(1)*v.get(1) +
	    get(2)*v.get(2);
	return n;
}

void Vector::print()
{
	for(int i=0;i<VECTOR_MAX;i++)
		std::cout<<this->get(i)<<"\n";	
}

Vector Vector::operator*(Vector &v)
{
	Vector n;
	
	float i, j, k;
	i = get(1)*v.get(2) - v.get(1)*get(2);
	j = v.get(0)*get(2) - get(0)*v.get(2);
	k = get(0)*v.get(1) - v.get(0)*get(1);
	
	n.put(0,i);
	n.put(1,j);
	n.put(2,k);	

	return n;
}

Vector Vector::operator-()
{
	Vector v(-get(0),-get(1),-get(2));
	return v;
}
