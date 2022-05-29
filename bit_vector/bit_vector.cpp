/*
 *	UPDATE 3 / 28 / 2022 - Harlow Huber
 *		The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
 *		This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
 *		put my changes below.All functionality will remain the same, or exceedingly similar.
 *		All previous code comments will remain, for now, as a reference.
 *
 *	BUG FIXES
 */

#include "bit_vector.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// implementation of nvboolfunc

//**********************************************************************************************
//	Bitwise OR of two bit_vector_t.
//**********************************************************************************************

bit_vector_t& bit_vector_t::bitOr(bit_vector_t& x, bit_vector_t& y)
{

	if (x.get_size() != y.get_size())
	{
		bit_vector_t bt = *new bit_vector_t();
		return bt;
	}

	bit_vector_t& newBV = *new bit_vector_t(x.get_size());

	//Or x and y and store the results in newBV.

	for (int i = 0; i < x.get_size(); i++)
	{
		newBV.bit_array[i] = x.bit_array[i] | y.bit_array[i];
	}

	return newBV;

}

//***********************************************************************************************
// default contructor
//***********************************************************************************************
bit_vector_t::bit_vector_t(void)
{
	size = 0;
	bit_array = NULL;
}

//***********************************************************************************************
// contructor from a string "01001001000"
//***********************************************************************************************
bit_vector_t::bit_vector_t(const char* const str)
{
	if (str)
	{
		size_t i = 0;

		size = strlen(str);
		bit_array = new bool[size];
		if (!bit_array)
		{
			size = 0;
		}
		else {
			for (i = 0; i < size; i++)	bit_array[i] = (str[i] == '0') ? false : true;
		}

	}
	else {
		bit_array = NULL;
		size = 0;
	}
}

//***********************************************************************************************
// contructor by the size only
//***********************************************************************************************
bit_vector_t::bit_vector_t(size_t _size)
{
	size = _size;
	bit_array = new bool[size];
	if (!bit_array)
	{
		size = 0;
	}
}

//***********************************************************************************************
// contructor by size and value as value only would not be distinguishable
// take bits from the right and forgot the others ...
//***********************************************************************************************
bit_vector_t::bit_vector_t(size_t _size, int val)
{
	size = _size;
	bit_array = new bool[size];
	if (!bit_array)
	{
		size = 0;
	}
	else {
		size_t i;
		for (i = 0; i < size; i++) {
			bit_array[i] = (((val & (0x1 << i)) != 0) ? true : false); // FIX: simplify, all zeroes
		}
		
	}

}

//***********************************************************************************************
// copy contructor
//***********************************************************************************************
bit_vector_t::bit_vector_t(const bit_vector_t& src)
{
	size = src.size;
	bit_array = new bool[size];
	if (!bit_array)
	{
		size = 0;
	}
	else {
		size_t i;
		for (i = 0; i < size; i++) bit_array[i] = src.bit_array[i];
	}

}

//***********************************************************************************************
// copy operator
//***********************************************************************************************
bit_vector_t& bit_vector_t::operator=(const bit_vector_t& src)
{
	if (size != src.size)
	{
		if (bit_array) delete[](bit_array);
		size = src.size;
		bit_array = new bool[size];
		if (!bit_array)
		{
			size = 0;
		}
		else {
			size_t i;
			for (i = 0; i < size; i++) bit_array[i] = src.bit_array[i];
		}
	}
	else {
		size_t i;
		for (i = 0; i < size; i++) bit_array[i] = src.bit_array[i];
	}

	return *this;
}

//***********************************************************************************************
// destructor
//***********************************************************************************************
bit_vector_t::~bit_vector_t(void)
{
	if (bit_array) delete[](bit_array);
	size = 0;
}

//***********************************************************************************************
// return the level of the vector (norm of the vector)
//***********************************************************************************************

int bit_vector_t::getlevel(void)
{
	size_t i;
	int r = 0;

	if (size == 0 || !bit_array) return -1;

	for (i = 0; i < size; i++) 
		r += ((bit_array[i]) ? 1 : 0);

	return r;
}


//***********************************************************************************************
// Order operator in the lattice scope  strict >
//***********************************************************************************************

bool bit_vector_t::operator>(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) 
		return false;

	for (i = 0; i < size; i++)
	{
		if (((char)bit_array[i]) <= ((char)x.bit_array[i]))
			return false;
	}

	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  strict <
//***********************************************************************************************

bool bit_vector_t::operator<(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) return false;
	for (i = 0; i < size; i++) if (((char)bit_array[i]) >= ((char)x.bit_array[i])) return false;
	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  >=
//***********************************************************************************************

bool bit_vector_t::operator>=(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) return false;
	for (i = 0; i < size; i++) if (((char)bit_array[i]) < ((char)x.bit_array[i])) return false;
	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  strict <=
//***********************************************************************************************

bool bit_vector_t::operator<=(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) return false;
	for (i = 0; i < size; i++) if (((char)bit_array[i]) > ((char)x.bit_array[i])) return false;
	return true;
}

//***********************************************************************************************
// This operator return true if the 2 vectors are equal
//***********************************************************************************************

bool bit_vector_t::operator==(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) return false;
	for (i = 0; i < size; i++) if (bit_array[i] != x.bit_array[i]) return false;
	return true;
}

//***********************************************************************************************
// This operator return true if different, or not comparable false if not.
//***********************************************************************************************

bool bit_vector_t::operator!=(bit_vector_t& x)
{
	size_t i = 0;

	if (!x.bit_array || !bit_array || x.size != size) return true;
	for (i = 0; i < size; i++) if (bit_array[i] != x.bit_array[i]) return true;
	return false;
}

//***********************************************************************************************
// return the bit from the vector
//***********************************************************************************************
bool& bit_vector_t::operator[](size_t i)
{
	if (i > size) return bit_array[size];
	else return bit_array[i];
}

//***********************************************************************************************
// return a conversion in the value
//***********************************************************************************************

size_t bit_vector_t::get_value(void)
{
	size_t r = 0, i;

	for (i = 0; i < size; i++)	
		r |= ((bit_array[i]) ? 0x1 : 0x0) << i;

	return r;
}

//***********************************************************************************************
// return a string containing the bit vector
//***********************************************************************************************

char* bit_vector_t::get_string(void)
{
	size_t i;
	char* v = new char[size + 1];
	v[size] = '\0';

	for (i = 0; i < size; i++)
	{
		v[i] = (bit_array[i]) ? '1' : '0';
	}
	return v;
}

//***********************************************************************************************
// Compatibility methods
// construct a bit_vector_t from a Vector of the Hanselchain project
// and operator= from the same type of object
//***********************************************************************************************

bit_vector_t::bit_vector_t(const Vector& src)
{

	size = (size_t)src.getSize();
	bit_array = new bool[size];
	if (!bit_array)
	{
		size = 0;
	}
	else {
		size_t i;
		for (i = 0; i < size; i++)
			bit_array[i] = (src.retrieveBit(i + 1) == 1);
	}
}

bit_vector_t& bit_vector_t::operator=(const Vector& src)
{
	bit_vector_t u(src);
	*this = u;
	return *this;
}
