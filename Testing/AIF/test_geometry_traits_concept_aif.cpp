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

#include "Testing/Concepts/GeometryConceptCheck.h"

int
main(int narg, char **argv)
{
  typedef FEVV::DataStructures::AIF::AIFMesh Mesh;
  BOOST_CONCEPT_ASSERT((FEVV::Point_3Concept< Mesh >));

  typedef FEVV::Geometry_traits< Mesh > Geometry;
  Mesh mesh;
  Geometry g(mesh);
  FEVV::GeometryTraits::verify_assumption(g);
  // FEVV::GeometryTraits::verify_operator_results( g );

  return 0;
}
