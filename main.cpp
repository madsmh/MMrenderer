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


#include <iostream>
#include "vector3.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector3 p(1.0, 2.0, 3.0);
    Vector3 q(2.0, 3.0, 4.0);
    std::cout << "p=" << p << " , q=" << q << std::endl;
    std::cout << "dot(p,q)  =" << dot(p,q) << std::endl;
    std::cout << "cross(p,q)=" << cross(p,q) << std::endl;
    return 0;
}

