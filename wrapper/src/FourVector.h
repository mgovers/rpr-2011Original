/*!
 * \file FourVector.h
 * \ingroup wrapper
 *
 * \author Pieter Vancraeyveld <pieter.vancraeyveld@ugent.be>
 * 
 * \copyright
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef FOURVECTOR_H
#define FOURVECTOR_H

#include <iostream>
#include <cmath>
#include "Matrix.h"
#include "GammaStructure.h"
#include <complex>


//-------------------------------------------------------------------------
//---- Certain classes and functions need to be pre-declared
//---- See C++ FAQ lite 35.16 as to why

template<typename T> class FourVector;
template<typename T> 
std::ostream& operator<<(std::ostream&,const FourVector<T>&);


//-------------------------------------------------------------------------
//---- class FourVector<T> declaration

/*! \class FourVector
 * \brief Class representing a general 4-vector in Minkowski space.
 * The components of the 4-vector can be virtually everything.
 */
template< typename T >
class FourVector
{
 public:
  // Constructors
  // ------------
  FourVector(); // default constructor (all components are zero)
  FourVector(const T&,const T&,const T&,const T&);

  // Access individual components
  // ----------------------------
  T& operator[](int);
  T operator[](int) const;

  // Assignment
  // ----------
  FourVector& operator=(const FourVector&);
 
  // Addition
  // --------
  FourVector& operator+=(const FourVector& right);
  FourVector& operator-=(const FourVector& right);

  FourVector operator+(const FourVector&) const;
  FourVector operator-(const FourVector& right) const;

  // Unary minus
  // -----------
  FourVector operator-() const;

  // Vector multiplication
  // ---------------------
  T operator*(const FourVector&) const;
  template< typename X>
    friend std::complex<X> operator* (const FourVector< X>&, const FourVector<std::complex<X> >&);
  
  template< typename X>
    friend std::complex<X> operator* (const FourVector< std::complex<X> >&, const FourVector<X>&);
  
  template< typename X, int K, int L >
    friend Matrix<K,L> operator*(const FourVector<X>&,
				 const FourVector< Matrix<K,L> >&);
  template< typename X >
    friend GammaStructure operator*(const FourVector<GammaStructure>&,
				    const FourVector<X>&);
  template< typename X >
    friend GammaStructure operator*(const FourVector<X>&,
				    const FourVector<GammaStructure>&);
  
  // Scalar multiplication
  // ---------------------
  template< typename X, typename F >
    friend FourVector<X> operator*(const FourVector<X>&, const F&);
  template< typename X, typename F >
    friend FourVector<X> operator*(const F&, const FourVector<X>&);
  template< typename X, typename F >
    friend FourVector<X>& operator*=(FourVector<X>&, const F&);
  template< typename X >
    friend FourVector<GammaStructure> operator*(const GammaStructure&,
						const FourVector<X>&);
  template< typename X >
    friend FourVector<GammaStructure> operator*(const FourVector<X>&,
						const GammaStructure&);

  // General
  // -------
  FourVector lowerIndex() const; /* Lowering the index of the 4vector
				  * is equivalent to multiplication
				  * with the metric */
  double theta() const; // polar angle of the 3vector
  double phi() const; // azimuthal angle of the 3vector

  // Output
  // ------
  void print() const; // print to screen
  friend std::ostream& operator<< <>(std::ostream&,const FourVector&); // overload <<

 private:
  // Data members (components)
  // -------------------------
  T t;
  T x;
  T y;
  T z;  
};

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//---- class FourVector<T> definitions
//---- We do not have a separate source file
//---- See C++ FAQ lite 35.12 for more info

// Constructors
// ------------

template< typename T >
FourVector<T>::FourVector() // default constructor
: t( T() ),
  x( T() ),
  y( T() ),
  z( T() )
{
  // empty body
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
FourVector<T>::FourVector(const T& tTemp,const T& xTemp,
			  const T& yTemp,const T& zTemp)
  : t( tTemp ),
    x( xTemp ),
    y( yTemp ),
    z( zTemp )
{
  // empty body
}

//-----------------------------------------------------------------------

/// access individual components
template< typename T >
T& FourVector<T>::operator[]( int subscript)
{
  switch(subscript)
    {
    case 0:
      return t;
    case 1:
      return x;
    case 2:
      return y;
    case 3:
      return z;
    default:
      std::cerr << "subscript(=" << subscript << ") out of range"
		<< std::endl;
      exit(1); 
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
T FourVector<T>::operator[]( int subscript) const
{
  switch(subscript)
    {
    case 0:
      return t;
    case 1:
      return x;
    case 2:
      return y;
    case 3:
      return z;
    default:
      std::cerr << "subscript(=" << subscript << ") out of range"
		<< std::endl;
      exit(1); 
    }
}

//-----------------------------------------------------------------------

// Assignment
// ----------
template< typename T >
FourVector<T>& FourVector<T>::operator=(const FourVector<T>& toCopy)
{
  if(this != &toCopy) {
    t = toCopy.t;
    x = toCopy.x;
    y = toCopy.y;
    z = toCopy.z;
  }

  return *this;
}

//-----------------------------------------------------------------------

// addition
// --------

template< typename T >
FourVector<T>& FourVector<T>::operator+=(const FourVector<T>& right)
{
  t += right.t;
  x += right.x;
  y += right.y;
  z += right.z;

  return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
FourVector<T>& FourVector<T>::operator-=(const FourVector<T>& right)
{
  t -= right.t;
  x -= right.x;
  y -= right.y;
  z -= right.z;

  return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
FourVector<T> FourVector<T>::operator+(const FourVector<T>& right) const
{
  return FourVector<T>(t+right.t,
		       x+right.x,
		       y+right.y,
		       z+right.z);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
FourVector<T> FourVector<T>::operator-(const FourVector<T>& right) const
{
  return FourVector<T>(t+(-1.0*right.t),
		       x+(-1.0*right.x),
		       y+(-1.0*right.y),
		       z+(-1.0*right.z));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template< typename T >
FourVector<T> FourVector<T>::operator-() const
{
  return FourVector<T>((-1.0*t),
		       (-1.0*x),
		       (-1.0*y),
		       (-1.0*z));
}

//-----------------------------------------------------------------------

/// Minkowski product
template< typename T >
T FourVector<T>::operator*(const FourVector<T>& right) const
{
  return (t*right.t
	  -x*right.x
	  -y*right.y
	  -z*right.z);
}

//! Minkowski product (T * complex<T> )
template <typename X>
std::complex <X> operator*(const FourVector < X >& left, const FourVector < std::complex < X> >& right)
{
    std::complex<X> product = left.t*right.t
                              -left.x*right.x
                              -left.y*right.y
                              -left.z*right.z;
    return product;
}

/// product ( complex<T> * T)
template <typename X>
std::complex <X> operator*(const FourVector < std::complex < X> >& left, const FourVector < X>& right)
{
    std::complex<X> product = left.t*right.t
                              -left.x*right.x
                              -left.y*right.y
                              -left.z*right.z;
    return product;
}
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Special type of vector multiplication
/// in which the right side is a KxL matrix
template< typename X, int K, int L >
Matrix<K,L> operator*(const FourVector<X>& left,
		      const FourVector< Matrix<K,L> >& right)
{
  Matrix<K,L> product = (left.t*right.t
			 + (-1.0*left.x*right.x)
			 + (-1.0*left.y*right.y)
			 + (-1.0*left.z*right.z));
  return product;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Special type of vector multiplication
/// in which the left side is a GammaStructure
template< typename T >
GammaStructure operator*(const FourVector<GammaStructure>& left,
			 const FourVector<T>& right)
{
  GammaStructure product = (left.t*right.t
			    + (-1.0*left.x*right.x)
			    + (-1.0*left.y*right.y)
			    + (-1.0*left.z*right.z));
  return product;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Special type of vector multiplication
/// in which the right side is a GammaStructure
template< typename X >
GammaStructure operator*(const FourVector<X>& left,
			 const FourVector<GammaStructure>& right)
{
  GammaStructure product = (left.t*right.t
			    + (-1.0*left.x*right.x)
			    + (-1.0*left.y*right.y)
			    + (-1.0*left.z*right.z));
  return product;
}

//-----------------------------------------------------------------------

/// Scalar multiplication
/// (FourVector * factor)
template< typename X , typename F>
FourVector<X> operator*(const FourVector<X>& vect, const F& factor)
{
  return FourVector<X>(vect.t*factor,
		       vect.x*factor,
		       vect.y*factor,
		       vect.z*factor);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Scalar multiplication
/// (FourVector * factor)
template< typename X , typename F>
FourVector<X>& operator*=(FourVector<X>& vect, const F& factor)
{
  vect.t *= factor;
  vect.x *= factor;
  vect.y *= factor;
  vect.z *= factor;

  return vect;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Scalar multiplication
/// (factor * FourVector)
template< typename X, typename F>
FourVector<X> operator*(const F& factor, const FourVector<X>& vect)
{
  return FourVector<X>(factor*vect.t,
		       factor*vect.x,
		       factor*vect.y,
		       factor*vect.z);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Scalar multiplication
/// (GammaStructure * T 4vector)
template< typename X >
FourVector<GammaStructure> operator*(const GammaStructure& left,
				     const FourVector<X>& right)
{
  return FourVector<GammaStructure>(left*right.t,
				    left*right.x,
				    left*right.y,
				    left*right.z);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// Scalar multiplication
/// (T 4vector * GammaStructure)
template< typename X >
FourVector<GammaStructure> operator*(const FourVector<X>& left,
				     const GammaStructure& right)
{
  return FourVector<GammaStructure>(left.t*right,
				    left.x*right,
				    left.y*right,
				    left.z*right);
}

//-----------------------------------------------------------------------

/// Lowering the index of the 4vector
template< typename T >
FourVector<T> FourVector<T>::lowerIndex() const
{
  return FourVector<T>(t,-1.0*x,-1.0*y,-1.0*z);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// polar angle of the 3vector
template< typename T >
double FourVector<T>::theta() const 
{ 
  return x == 0.0 && y == 0.0 && z == 0.0 ? 0.0 : std::atan2(std::sqrt(x*x+y*y),z); 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/// azimuthal angle of the 3vector
template< typename T >
double FourVector<T>::phi() const 
{ 
  return x == 0.0 && y == 0.0 ? 0.0 : std::atan2(y,z); 
}

//-----------------------------------------------------------------------

/// print to screen
template< typename T >
void FourVector<T>::print() const
{
  std::cout << "(" << t << "," << x << "," << y << "," << z << ")" << std::endl;
}

//-----------------------------------------------------------------------

/// Write to screen using << operator
template< typename T >
std::ostream& operator<<(std::ostream& output, const FourVector<T>& vector)
{
  output << "(" << vector.t << "," << vector.x
	 << "," << vector.y << "," << vector.z << ")";

  return output;
}

//-----------------------------------------------------------------------

/// 4vector gamma_{mu} containing 4 GammaStructures
const FourVector<GammaStructure> GMU(GammaStructure(0,0,1),
				     GammaStructure(0,0,0,1),
				     GammaStructure(0,0,0,0,1),
				     GammaStructure(0,0,0,0,0,1));

#endif
