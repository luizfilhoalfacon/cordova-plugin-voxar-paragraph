#ifndef __GUARD_VECTOR2_H__
#define __GUARD_VECTOR2_H__

#include <algorithm>
#include <vector>

#include "point2.h"

class Vector2 {
public:
    typedef double* iterator;
    typedef const double* const_iterator;

    double& x;
    double& y;

    // Constructor based on coordinates
    Vector2(double x, double y);

    // Constructor based on initial and end points
    Vector2(const Point2& origin, const Point2& destination);

    // Conversion constructor from Point2
    explicit Vector2(const Point2& point);

    // Copy constructor
    Vector2(const Vector2& other);

    // Coordinate indexing
    double& operator[](int i) { return coordinates[i]; }
    const double& operator[](int i) const { return coordinates[i]; }

    // Iterator functions
    iterator begin() { return coordinates; }
    iterator end() { return coordinates + 2; }
    const_iterator begin() const { return coordinates; }
    const_iterator end() const { return coordinates + 2; }

    Vector2& operator=(const Vector2& other);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const { return !operator==(other); }

    void operator+=(const Vector2& other);
    void operator-=(const Vector2& other);

    // Returns a new Vector2 object corresponding to the normalized vector
    Vector2 normalize() const;

    double magnitude() const;

private:
    double coordinates[2];

};


// Cross and dot products
Vector2 cross_prod(const Vector2& a);
double dot_prod(const Vector2& a, const Vector2& b);

// Vector multiplication by a scalar
Vector2 operator*(const Vector2& vec, double scalar);
Vector2 operator*(double& scalar, const Vector2& vec);

// Vector division
Vector2 operator/(const Vector2& vec, double scalar);

// Vector sum
Vector2 operator+(const Vector2& vec1, const Vector2& vec2);

// Vector subtraction
Vector2 operator-(const Vector2& vec1, const Vector2& vec2);

#endif