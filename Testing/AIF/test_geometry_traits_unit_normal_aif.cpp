// Copyright (c) 2012-2019 University of Lyon and CNRS (France).
// All rights reserved.
//
// This file is part of MEPP2; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; either version 3 of
// the License, or (at your option) any later version.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#include "FEVV/DataStructures/AIF/AIFMesh.hpp"
#include "FEVV/Wrappings/Geometry_traits_aif.h"

#include <iostream>

using namespace FEVV;

int
main(int narg, char **argv)
{
  if(narg > 1)
  {
    std::cout << "Usage: " << argv[0] << " (no arguments)." << std::endl;
    exit(EXIT_FAILURE);
  }

  typedef DataStructures::AIF::AIFMesh Mesh;
  typedef Geometry_traits< Mesh > Geometry;
  typedef Geometry::Point Point;
  typedef Geometry::Vector Vector;

  Mesh m;
  Geometry g(m);
  Point p1(0.0f, 0.0f, 0.0f);
  Point p2(1.0f, 0.0f, 0.0f);
  Point p3(0.0f, 0.1f, 0.0f);
  Vector n = g.unit_normal(p1, p2, p3);

  if(n == Vector(0.0, 0.0, 1.0))
  {
    std::cout << "OK." << std::endl;
    return 0;
  }
  else
  {
    std::cout << "Bad result!" << std::endl;
    return 1;
  }
}
