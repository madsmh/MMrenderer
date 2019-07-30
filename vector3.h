/* Copyright (c) 2019 By the Authors
 *
 * This file is part of MMRender.

    Orbit Simulator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Orbit Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MMRender.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */


#ifndef ORBIT3D_VECTOR3_H
#define ORBIT3D_VECTOR3_H

#include <vector>
#include <iostream>
#include <cmath>

class Vector3 {
    double coords[3];
public:
    inline explicit Vector3( double x = 0.0, double y = 0.0, double z = 0.0){
     coords[0] = x, coords[1] = y, coords[2] = z;
    }
    inline explicit Vector3(std::vector<double> v) {
        coords[0]= v[0], coords[1] = v[1], coords[2]= v[2];
    }

    inline double norm2() const { return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2]; }
    inline double norm()  const { return std::sqrt(norm2()); }

    inline void normalize() {
        double k = norm();
        coords[0]/=k;
        coords[1]/=k;
        coords[2]/=k;
    }

    inline double x()     const { return coords[0]; }
    inline double y()     const { return coords[1]; }
    inline double z()     const { return coords[2]; }

    inline explicit operator std::vector<double>() const  {
        return std::vector<double> {coords[0], coords[1], coords[2]};
    }

    inline double operator[](int i) const { return coords[i];}

    inline  Vector3& operator += (const Vector3& rhs) {
        coords[0] += rhs[0];
        coords[1] += rhs[1];
        coords[2] += rhs[2];
        return *this;
    }

    inline Vector3& operator -= (const Vector3& rhs) {
        coords[0] -= rhs[0];
        coords[1] -= rhs[1];
        coords[2] -= rhs[2];
        return *this;
    }

    inline Vector3& operator *= (const double rhs) {
        coords[0] *= rhs;
        coords[1] *= rhs;
        coords[2] *= rhs;
        return *this;
    }

    inline Vector3& operator /= (const double rhs) {
        coords[0] /= rhs;
        coords[1] /= rhs;
        coords[2] /= rhs;
        return *this;
    }

    inline friend bool operator == (const Vector3& lhs, const Vector3& rhs) {
        return (lhs[0] == rhs[0]) && (lhs[1] == rhs[1]) && (lhs[2] == rhs[2]);
    }

    inline friend Vector3 operator * (Vector3 lhs, const double rhs ) {
        return lhs *= rhs;
    }

    inline friend Vector3 operator * (const double lhs, Vector3 rhs ) {
        return rhs *= lhs;
    }

    inline friend Vector3 operator * (const Vector3& factor1, const Vector3& factor2){
        double x = factor1[0]*factor2[0];
        double y = factor1[1]*factor2[1];
        double z = factor1[2]*factor2[2];

        return Vector3(x, y, z);
    }

    inline friend Vector3 operator + (Vector3 lhs, const Vector3& rhs) {
        return lhs += rhs;
    }

    inline friend Vector3 operator - (Vector3 lhs, const Vector3& rhs) {
        return lhs -= rhs;
    }

    inline friend Vector3 operator / (Vector3 lhs, const double rhs){
        return lhs /= rhs;
    }

    inline friend std::ostream& operator << (std::ostream &os, const Vector3& rhs) {
        return os << rhs[0] << " " << rhs[1] << " " << rhs[2];
    }
};

#endif //ORBIT3D_VECTOR3_H

inline Vector3 cross (const Vector3 factor1, const Vector3 factor2){
    double x = factor1[1]*factor2[2] - factor1[2]*factor2[1];
    double y = factor1[2]*factor2[0] - factor1[0]*factor2[2];
    double z = factor1[0]*factor2[1] - factor1[1]*factor2[0];

    return Vector3(x, y, z);
}

inline double dot (const Vector3 v1, const Vector3 v2){
    return v1[0]*v2[0]+v1[1]*v2[1]+v2[2]*v2[2];
}