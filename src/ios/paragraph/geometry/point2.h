#ifndef __GUARD_POINT2_H__
#define __GUARD_POINT2_H__

#include <algorithm>
#include <vector> 

#include "opencv2/core/core.hpp"

class Vector2;

class Point2 {
public:
    typedef double* iterator;
    typedef const double* const_iterator;

    double& x;
    double& y;
    
    Point2(double x, double y);

    // Conversion constructor from Vector2
    explicit Point2(const Vector2& vector);
    // Conversion constructor from cv::Point2f
    Point2(const cv::Point2f& point);

    // Copy constructor
    Point2(const Point2& other);

    // Coordinate indexing
    double& operator[](int i) { return coordinates[i]; }
    const double& operator[](int i) const { return coordinates[i]; }

    // Iterator functions
    iterator begin() { return coordinates; }
    iterator end() { return coordinates + 2; }
    const_iterator begin() const { return coordinates; }
    const_iterator end() const { return coordinates + 2; }

    Point2& operator=(const Point2& other);

    bool operator==(const Point2& other) const;
    bool operator!=(const Point2& other) const { return !operator==(other); }

    void operator+=(const Vector2& vec);
    void operator-=(const Vector2& vec);

private:
    double coordinates[2];
};

double distance(const Point2& a, const Point2& b);
double distance2(const Point2& a, const Point2& b);

Vector2 operator-(const Point2& a, const Point2& b);
Point2 operator+(const Point2& p, const Vector2& v);
Point2 operator+(const Vector2& v, const Point2& p);

// At the end of the header in order to avoid cyclic dependency
#include "vector2.h"

#endif
