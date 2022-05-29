#pragma once

/* **********************************************************************
   *  UPDATE 3/28/2022 - Harlow Huber
   *	The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
   *	This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will 
   *	put my changes below. All functionality will remain the same, or exceedingly similar.
   *	All previous code comments will remain, for now, as a reference.
   * 
   *  BUG FIXES 3/28/2022 - Harlow Huber
   *	operator "=" returns "Boolean" (this item was blank)
   *	in display(), "ofstream" changed to "std::ofstream"
   *	"Boolean" data type does not work in modern C++. Redefined above the old declaration, which is left in a commented out block as a reference
   *		moreover, the "BOOLEAN_DEF" macro doesn't seem to do anything, but it is also left as-is...
   * 
   *  FILE        : vector.h
   *  NAME        : Vector Object specification
   *  OWNER       : Chad Burdyshaw (only owner can make changes)
   *  VERSION     : 1.2            (major change.minor change)
   **
   ** Version modified by Florian DELIZY
   ** ... see other headers for informations ..
   **
   *
   *  CHANGE LOG  :
   *     VERSION #  DATE      WHO COMMENT
   *     ---------------------------------------------------------------
   *     0.1.0      11.17.98  CB  Created file and imported Vector
   *                                 class info from old restore.h
   *     0.2.0      11.18.98  SAF Updated array indexing to range from 0...k-1
   *                                 rather than 1...k
   *                                 Methods affected: setBit, retrieveBit, compareAndSet
   *                              Updated constructor to set all vector elements to 0
   *     0.3.0      11.18.98  SAF Added >= operator for use in MonotoneBooleanFunction
   *     0.4.0      11.18.98  SAF Added retrieveNumberElements for use in MonotoneBooleanFunction
   *     0.5.0      11.18.98  SAF Added =, ==, & operators for use in MonotoneBooleanFunction
   *     0.6.0      11.20.98  JWS Added display
   *                              Added getSize
   *                              added retrieveKnown
   *     1.0.0      11.23.98  ALL Initial Client Release
   *     1.1.0      11.28.98  SAF Added output to a file
   *     1.2.0      11.28.98  SAF Added clearBit
   *
   *  SYSTEM      : ANSI C++ - should build on everything.
   *
   *  DESCRIPTION : Vector representing a bit string of "symptoms" and the
   *                                    operations on these vectors
   *
   *  INCLUDES    : File Stream (fstream.h)
   *
   *  TODO        : N/A
   *
   *************************************************************************/

#ifndef _VECTOR_H
#define _VECTOR_H

#include <fstream>

const int MAX_ELEMENTS = 15;

// boolean data type declaration 
#define BOOLEAN_DEF 
typedef int Boolean;

/*
// boolean data type declaration
#ifndef BOOLEAN_DEF
typedef int Boolean;
const int FALSE = 0;
const int TRUE = 1;
#define BOOLEAN_DEF
#endif
*/

#define VECTOR_NAME "sequence"

// Purpose:     Represents vector and the functional value
class __declspec(dllexport) Vector {
public:
	// Purpose: Creates a new vector with n elements
	// Input:       number of elements
	// Output:      N/A
	// Returns:     N/A
	// Notes:       sets wasInquired and valueKnown to false.
	Vector(/* IN */ int n);

	// Purpose: Sets bit at index to TRUE
	// Input:       index of bit to set
	// Output:      N/A
	// Returns:     N/A
	// Notes:       N/A
	void setBit(/* IN */ int index);

	// Purpose: Sets bit at index to FALSE
	// Input:       index of bit to set
	// Output:      N/A
	// Returns:     N/A
	// Notes:       N/A
	void clearBit(/* IN */ int index);

	// Purpose: Sets vector to given value
	// Input:       Boolean value
	// Output:      N/A
	// Returns:     N/A
	// Notes:       N/A
	void setValue(/* IN */ Boolean answer);

	// Purpose: Retrieve bit value at index
	// Input:       index of bit
	// Output:      N/A
	// Returns:     value of bit
	// Notes:       N/A
	Boolean retrieveBit(/* IN */ int index) const;  // damn, I thought that no one would have dared
													// to do that kind of slow things but ...
													// there are things that have no limit :(
													// did you ever heard about the operator[] ?!?!
													// FD

	// Purpose: Tells the vector is has been presented to the oracle
	// Input:       N/A
	// Output:      N/A
	// Returns:     N/A
	// Notes:       Sets the wasInquired flag
	void setInquired(void);

	// Purpose: Tells the vector is has been presented to the oracle
	// Input:       vector from which to expand if possible
	// Output:      N/A
	// Returns:     N/A
	// Notes:       If the value of the expandFrom vector is true, we check if self
	//              is larger than the expandFrom vector. If self is larger, then
	//              self sets its value to true and valueKnown to true.
	//          If the value of the expandFrom vector is false, we check if self
	//              is smaller than the expandFrom vector. If self is smaller, then
	//              self sets its value to false and valueKnown to true.
	void compareAndSet(/* IN */ Vector expandFrom);

	// Purpose: Retrieves the functional value of the vector as presented by the Oracle.
	// Input:       N/A
	// Output:      N/A
	// Returns:     Returns value
	// Notes:       N/A
	Boolean retrieveValue(void) const;

	// Purpose: Checks if the value of the vector is known
	// Input:       N/A
	// Output:      N/A
	// Returns:     Returns valueKnown
	// Notes:       N/A
	Boolean retrieveKnown(void) const;

	// Purpose: Retrieves the value of wasInquired. That is, whether or not the vector
	//				has been presented by the Oracle.
	// Input:	N/A
	// Output:	N/A
	// Returns:	Returns value of wasInquired
	// Notes:	N/A
	Boolean retrieveInquiredStatus(void) const;

	// Purpose: Element-wise AND of two vectors
	// Input:       comparer vector
	// Output:      N/A
	// Returns:     Result of operation
	// Notes:       N/A
	Vector operator &(/* IN */ Vector& secondVector) const;

	// Purpose: Checks if selfVector is greater than or equal to secondVector
	// Input:       comparer vector
	// Output:      N/A
	// Returns:     TRUE if selfVector greater than or equal to secondVector
	// Notes:       self Vector is not greater/equal if
	//                 selfVector[element k] = FALSE && secondVector[element k] = TRUE
	Boolean operator >=(/* IN */ Vector& secondVector) const;

	// Purpose: Overloads == (equal) operator for two Vectors
	// Input:       comparer vector
	// Output:      N/A
	// Returns:     Result of operation
	// Notes:       N/A
	Boolean operator ==(/* IN */ Vector& secondVector) const;

	// Purpose: Overloads != (not equal) operator for two Vectors
	// Input:       comparer vector
	// Output:      N/A
	// Returns:     Result of operation
	// Notes:       N/A
	Boolean operator !=(/* IN */ const Vector& secondVector) const;

	// Purpose: Assignment of secondVector to selfVector
	// Input:       original vector vector
	// Output:      N/A
	// Returns:     Result of operation
	// Notes:       N/A
	Boolean operator =(/* IN */ const Vector& secondVector);

	// Purpose: Finds the number of TRUE elements in the vector
	// Input:       N/A
	// Output:      N/A
	// Returns:     integer number of TRUE elements
	// Notes:       N/A
	int retrieveNumberTrueElements(void) const;

	// Purpose: Displays vector elements and value to a file
	// Input:       pointer to a file stream
	// Output:      N/A
	// Returns:     N/A
	// Notes:       N/A
	void display(std::ofstream& outputFile) const;

	// Purpose: Gets size of vector
	// Input:       N/A
	// Output:      N/A
	// Returns:     size
	// Notes:       N/A
	int getSize(void) const;

	// Purpose: Sets all vector bits to 0
	// Input:       N/A
	// Output:      N/A
	// Returns:     N/A
	// Notes:       N/A
	void clearVector(void);

	// Purpose: Returns true if all vector bits are 0.
	// Input:       N/A
	// Output:      N/A
	// Returns:     Truth value of all bits being zero.
	// Notes:       N/A
	Boolean allZeros(void);

private:
	int size;                                       // number of elements in vector
	int array[MAX_ELEMENTS];    // array of length size to hold values
								// arglllll whyyyyyyyyyyyyyyyyy ! 
								// FD died here ... enought is enought
								// this is one of the stupidiest things I ever seen
								// .FD

	Boolean value;                  // functional value of vector
	Boolean wasInquired;    // Oracle presented with this vector
	Boolean valueKnown;             // value is known
};      // Vector


/*
** Note : I like comments but were you *really* in that need, of write /*IN* / every where
** despite it is not standard, it is useless, and confusing, try to avoid such stupidity
** next time you approach a keyboard
*/
#endif

