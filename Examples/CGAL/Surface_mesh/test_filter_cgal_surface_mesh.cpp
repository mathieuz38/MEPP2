


#include "Examples/Generic/test/test_main.hpp"

// The following include defines the FEVV::MeshSurface type
#include "FEVV/DataStructures/DataStructures_cgal_surface_mesh.h"

#include "FEVV/Wrappings/Geometry_traits_cgal_surface_mesh.h"
#include "FEVV/Wrappings/properties_surface_mesh.h"


// Main: load a mesh, apply the filter, write the mesh
int
main(int argc, const char **argv)
{
  return test_main< FEVV::MeshSurface >(argc, argv);
}
