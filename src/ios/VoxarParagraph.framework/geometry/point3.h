#ifndef __GUARD_POINT3_H__
#define __GUARD_POINT3_H__

#include <algorithm>
#include <vector> 

class Vector3;

class Point3 {
public:
    typedef double* iterator;
    typedef const double* const_iterator;

    double& x;
    double& y;
    double& z;

    Point3(double x, double y, double z);

    // Conversion constructor from Vector3
    explicit Point3(const Vector3& vector);

    // Copy constructor
    Point3(const Point3& other);

    // Coordinate indexing
    double& operator[](int i) { return coordinates[i]; }
    const double& operator[](int i) const { return coordinates[i]; }

    // Iterator functions
    iterator begin() { return coordinates; }
    iterator end() { return coordinates + 3; }
    const_iterator begin() const { return coordinates; }
    const_iterator end() const { return coordinates + 3; }

    Point3& operator=(const Point3& other);

    bool operator==(const Point3& other) const;
    bool operator!=(const Point3& other) const { return !operator==(other); }

    void operator+=(const Vector3& vec);
    void operator-=(const Vector3& vec);

private:
    double coordinates[3];
};

double distance(const Point3& a, const Point3& b);
double distance2(const Point3& a, const Point3& b);

Vector3 operator-(const Point3& a, const Point3& b);
Point3 operator+(const Point3& p, const Vector3& v);
Point3 operator+(const Vector3& v, const Point3& p);

// At the end of the header in order to avoid cyclic dependency
#include "vector3.h"

#endif