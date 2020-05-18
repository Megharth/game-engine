// Support Code written by Michael D. Shah
// Updated by Seth Cooper
// Last Updated: Spring 2020
// Please do not redistribute without asking permission.

#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include<iostream>

// Forward references of each of the structs
struct Vector3D;
struct Matrix3D;

//! \brief Vector3D performs vector operations with 3-dimensions
//! The purpose of this class is primarily for 3D graphics
//! applications.
struct Vector3D{
    // Note: x,y,z are a convention
    // x,y,z could be position, but also any 3-component value.
    float x,y,z;

    // Default constructor
    // 'why default?' https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
    Vector3D() = default;

    // The "Real" constructor we want to use.
    // This initializes the values x,y,z
    Vector3D(float a, float b, float c){
    	x = a;
    	y = b;
    	z = c;
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    float& operator[](int i){
      return ((&x)[i]);
    }

    // Index operator, allowing us to access the individual
    // x,y,z components of our vector.
    const float& operator[](int i) const{
        return ((&x)[i]);
    }

    // Multiplication Operator
    // Multiply vector by a uniform-scalar.
    Vector3D& operator *=(float s){
    	x = x*s;
    	y = y*s;
    	z = z*s;
        return (*this);
    }

    // Division Operator
    Vector3D& operator /=(float s){
        // TODO:
    	if(s != 0) {
    		x = x/s;
    		y = y/s;
    		z = z/s;
    	}
        return (*this);
    }

    // Addition operator
    Vector3D& operator +=(const Vector3D& v){
        x += v[0];
        y += v[1];
        z += v[1];

      return (*this);
    }

    // Subtraction operator
    Vector3D& operator -=(const Vector3D& v){
        x -= v[0];
        y -= v[1];
        z -= v[2];

      return (*this);
    }

};

// Add two vectors together
inline Vector3D operator +(const Vector3D& a, const Vector3D& b){
  Vector3D vec;
  vec[0] = a[0] + b[0];
  vec[1] = a[1] + b[1];
  vec[2] = a[2] + b[2];
  return vec;
}

// Subtract two vectors
inline Vector3D operator -(const Vector3D& a, const Vector3D& b){
  Vector3D vec;
  vec[0] = a[0] - b[0];
  vec[1] = a[1] - b[1];
  vec[2] = a[2] - b[2];
  return vec;
}

// Multiplication of a vector by a scalar values
inline Vector3D operator *(const Vector3D& v, float s){
  Vector3D vec;
  vec[0] = v[0] * s;
  vec[1] = v[1] * s;
  vec[2] = v[2] * s;
  return vec;
}

// Division of a vector by a scalar value.
inline Vector3D operator /(const Vector3D& v, float s){
  Vector3D vec;
  if (s != 0) {
	  vec[0] = v[0] / s;
	  vec[1] = v[1] / s;
	  vec[2] = v[2] / s;
  } else {
	  vec[0] = 0;
	  vec[1] = 1;
	  vec[2] = 2;
  }
  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector3D operator -(const Vector3D& v){
  Vector3D vec;

  vec[0] = -v[0];
  vec[1] = -v[1];
  vec[2] = -v[2];

  return vec;
}

// Compute the dot product of a Vector3D
inline float Dot(const Vector3D& a, const Vector3D& b){
  int xSum = a[0] * b[0];
  int ySum = a[1] * b[1];
  int zSum = a[2] * b[2];

  return (xSum + ySum + zSum);
}

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
inline Vector3D CrossProduct(const Vector3D& a, const Vector3D& b){
  Vector3D vec;
  vec[0] = (a[1] * b[2]) - (b[1] * a[2]);
  vec[1] = - ((a[0] * b[2]) - (b[0] * a[2]));
  vec[2] = (a[0] * b[1]) - (b[0] * a[1]);

  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector3D& v){
  float magSq = Dot(v, v);
  return sqrt(magSq);
}

// Vector Projection
inline Vector3D Project(const Vector3D& a, const Vector3D& b){
  Vector3D vec;
  float dp = Dot(a, b);
  float mag = Magnitude(b);
  mag *= mag;
  vec = b * (float)((float)dp/(float)mag);
  return vec;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector3D Normalize(const Vector3D& v){
  Vector3D vec;
  float mag = Magnitude(v);
  if (mag > 0) {
	  vec = v / mag;
  } else {
	  vec = v;
  }
  return vec;
}


// Matrix 3D represents 3x3 matrices in Math
struct Matrix3D{
private:
    float n[3][3];  // Store each value of the matrix

public:
    Matrix3D() = default;

    // Row major order.
    // Matrix constructor with 9 scalar values.
    Matrix3D( float n00, float n01, float n02,
              float n10, float n11, float n12,
              float n20, float n21, float n22){

        n[0][0] = n00; n[0][1] = n01; n[0][2] = n02;
        n[1][0] = n10; n[1][1] = n11; n[1][2] = n12;
        n[2][0] = n20; n[2][1] = n21; n[2][2] = n22;
    }

    // Matrix constructor from three vectors.
    Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c){
      n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
      n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
      n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[i][j]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[i][j]);
    }

    // Return a row from a matrix as a vector.
    Vector3D& operator [](int j){
      return (*reinterpret_cast<Vector3D *>(n[j]));
    }

    // Return a row from a matrix as a vector.
    const Vector3D& operator [](int j) const{
      return (*reinterpret_cast<const Vector3D *>(n[j]));
    }

};

// Transpose a matrix :: Additional function
Matrix3D Transpose(const Matrix3D& A) {
	Matrix3D mat3D;
	mat3D[0][0] = A(0,0); mat3D[0][1] = A(1,0); mat3D[0][2] = A(2,0);
	mat3D[1][0] = A(0,1); mat3D[1][1] = A(1,1); mat3D[1][2] = A(2,1);
	mat3D[2][0] = A(0,2); mat3D[2][1] = A(1,2); mat3D[2][2] = A(2,2);
	return mat3D;
}

// Scalar multiplication
Matrix3D Mul(const Matrix3D& M, float s) {
	Matrix3D mat;
	mat[0][0] = s * M(0,0); mat[0][1] = s * M(0,1); mat[0][2] = s * M(0,2);
	mat[1][0] = s * M(1,0); mat[1][1] = s * M(1,1); mat[1][2] = s * M(1,2);
	mat[2][0] = s * M(2,0); mat[2][1] = s * M(2,1); mat[2][2] = s * M(2,2);
	return mat;
}

// to find the minor of a co-factor
float Minor(const Matrix3D &M, int i, int j) {
	return ((M((i+1) % 3, (j+1) % 3) * M((i+2) % 3, (j+2) % 3)) -
				(M((i+1) % 3, (j+2) % 3) * M((i+2) % 3, (j+1) % 3)));
}

// Determinant
float Determinant(const Matrix3D& M) {
	return (M(0,0) * Minor(M, 0, 0)) + (M(0,1) * Minor(M, 0, 1)) + (M(0,2) * Minor(M, 0, 2));
}

// Inverse
Matrix3D Inverse(const Matrix3D& M) {
	float det = Determinant(M);
	Matrix3D c;
	c(0,0) = Minor(M, 0, 0); c(0,1) = Minor(M, 0, 1); c(0,2) = Minor(M, 0, 2);
	c(1,0) = Minor(M, 1, 0); c(1,1) = Minor(M, 1, 1); c(1,2) = Minor(M, 1, 2);
	c(2,0) = Minor(M, 2, 0); c(2,1) = Minor(M, 2, 1); c(2,2) = Minor(M, 2, 2);
	Matrix3D i = Mul(c, (float) ((float)1/(float)det));
	return Transpose(i);
}


// Matrix Multiplication
Matrix3D operator *(const Matrix3D& A, const Matrix3D& B){
  Matrix3D mat3D;
  Matrix3D bT = Transpose(B);
  mat3D[0][0] = Dot(A[0], bT[0]); mat3D[0][1] = Dot(A[0], bT[1]); mat3D[0][2] = Dot(A[0], bT[2]);
  mat3D[1][0] = Dot(A[1], bT[0]); mat3D[1][1] = Dot(A[1], bT[1]); mat3D[1][2] = Dot(A[1], bT[2]);
  mat3D[2][0] = Dot(A[2], bT[0]); mat3D[2][1] = Dot(A[2], bT[1]); mat3D[2][2] = Dot(A[2], bT[2]);
  return mat3D;
}

Vector3D operator *(const Matrix3D& M, const Vector3D& v){
  Vector3D vec;
  vec[0] = Dot(M[0], v);
  vec[1] = Dot(M[1], v);
  vec[2] = Dot(M[2], v);
  return vec;
}


#endif
