#include "matrix.h"

#include <iostream>

Matrix::Matrix()
{
	this->load_zero();
}

void Matrix::put(int i, int j, float value)
{
	this->_matrix[i][j]=value;
}

float Matrix::get(int i, int j)
{
	return this->_matrix[i][j];
}

void Matrix::print()
{
	for(int i=0;i<MATRIX_MAX;i++)
	{
		for(int j=0;j<MATRIX_MAX;j++)
		{
			std::cout<<this->get(i,j)<<"\t";
		}
		std::cout<<"\n";
	}
}

void Matrix::load_zero()
{
	for(int i=0;i<MATRIX_MAX;i++)
		for(int j=0;j<MATRIX_MAX;j++)
			this->put(i,j,0.0);
}

void Matrix::load_identity()
{
	this->load_zero();
	for(int i=0;i<MATRIX_MAX;i++)
		this->put(i,i,1);
}

bool Matrix::is_null()
{
	for(int i=0;i<MATRIX_MAX;i++)
		for(int j=0;j<MATRIX_MAX;j++)
			if(get(i,j))
				return false;
	return true;
}

Matrix Matrix::operator+(Matrix &m)
{
	Matrix n;
	int i, j;
	for(i=0;i<MATRIX_MAX;i++)
	{
		for(j=0;j<MATRIX_MAX;j++)
			n.put(i,j, get(i,j)+m.get(i,j));
	}
	return n;
}

Matrix Matrix::operator-(Matrix &m)
{
	Matrix n;
	int i, j;
	for(i=0;i<MATRIX_MAX;i++)
	{
		for(j=0;j<MATRIX_MAX;j++)
			n.put(i,j, get(i,j)-m.get(i,j));
	}
	return n;
}

Matrix Matrix::operator*(Matrix &m)
{
	Matrix n;
	int i, j, k;
	for(i=0;i<MATRIX_MAX;i++)
	{
		for(k=0;k<MATRIX_MAX;k++)
		{
			float v=0.0f;
			for(j=0;j<MATRIX_MAX;j++)
			{
				v+=this->get(i,j)*m.get(j,k);
			}
			n.put(i,k,v);
		}
	}
	return n;
}

int Matrix::operator==(Matrix &m)
{
	for(int i=0;i<MATRIX_MAX;i++)
		for(int j=0;j<MATRIX_MAX;j++)
			if(get(i,j)!=m.get(i,j))
				return 0;
	return 1;
}

int Matrix::operator!=(Matrix &m)
{
	return !(*this==m);
}

Vector Matrix::operator*(Vector &v)
{
	Vector n;
	int i,j;
	float value=0.0;
	for(i=0;i<MATRIX_MAX;i++)
	{
		for(j=0;j<MATRIX_MAX;j++)
		{
			value += this->get(i,j)*v.get(j);
		}
		n.put(i,value);
		value=0.0;
	}
	return n;
}
