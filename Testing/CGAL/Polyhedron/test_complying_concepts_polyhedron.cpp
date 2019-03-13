// Copyright (c) 2012-2019 University of Lyon and CNRS (France).
// All rights reserved.
//
// This file is part of MEPP2; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published 
// by the Free Software Foundation; either version 3 of the License, 
// or (at your option) any later version.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
// Work around the side effects of the indirect (through
// FEVV/Wrappings/properties.h) inclusion of DataStructures.h

#include <CGAL/Cartesian.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <boost/graph/graph_concepts.hpp>
#include "Testing/Concepts/CGALConceptsCheck.h"

typedef CGAL::Cartesian< double > Kernel;
typedef CGAL::Polyhedron_3< Kernel, CGAL::Polyhedron_items_with_id_3 >
    Polyhedron;
// Technical type alias in order for the tests for the different data
// structures to share some code (preparing generic test for the day
// when all data structure are fully compliant).
typedef Polyhedron G;

int
main(int narg, char **argv)
{
  using namespace boost;
  // Assertions are sometimes redundant (IncidenceGraph concept assertion
  // already internally assert the Graph concept). We nevertheless do such
  // redudant checks along the concept "inheritance" hieararchy in order
  // for the test to provide the simplest feedback when failing (fail early).
  BOOST_CONCEPT_ASSERT((GraphConcept< G >));
  BOOST_CONCEPT_ASSERT((IncidenceGraphConcept< G >));
  BOOST_CONCEPT_ASSERT((BidirectionalGraphConcept< G >));

  // Graph already asserted
  BOOST_CONCEPT_ASSERT((EdgeListGraphConcept< G >));
  BOOST_CONCEPT_ASSERT((VertexListGraphConcept< G >));
  BOOST_CONCEPT_ASSERT((VertexAndEdgeListGraphConcept< G >));

  //////////////////////////////////////////////////////////////////////////
  ////////////// BOOST_CONCEPT_ASSERT( (EdgeMutableGraphConcept< G>) );
  // The following is the unfolding of the boost::EdgeMutableGraphConcept
  // concept on debugging (of Polyhedron) purposes
  { // Technical scope to avoid variable/type collisions with other tests
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    G g;
    edge_descriptor e;
    // std::pair<edge_descriptor, bool> p;
    // typename graph_traits<G>::vertex_descriptor u, v;

    // The following assertion fails with message:
    //   error: no matching function for call to 'add_edge'
    // UNCOMMENT ME (FIXME) p = add_edge(u, v, g);

    // The following assertion fails with message
    //  error: no matching function for call to 'remove_edge
    // UNCOMMENT ME (FIXME) remove_edge(u, v, g);

    remove_edge(e, g);

    // The following assertion fails with message:
    //   error: use of undeclared identifier 'clear_vertex(v, g);`
    // UNCOMMENT ME (FIXME) clear_vertex(v, g);
  } // Technical scope

  //////////////////////////////////////////////////////////////////////////
  //////////// BOOST_CONCEPT_ASSERT( (< MutableIncidenceGraphConcept G>) );
  // The following is the unfolding of the boost::MutableIncidenceGraphConcept
  // concept on debugging (of Polyhedron) purposes.
  // The following unfolding is necessary because the MutableIncidenceGraph
  // concept indirectly (through MutableGraph) inherits from the
  // EdgeMutableGraph concept that currently fails (refer above).
  { // Technical scope to avoid variable/type collisions with other tests
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    // G g;
    // boost::concepts::dummy_edge_predicate<edge_descriptor> p;
    // typename boost::graph_traits<G>::vertex_descriptor u;
    // typename boost::graph_traits<G>::out_edge_iterator iter;

    // The following assertion fails with message:
    //   no matching function for call to 'remove_edge'
    // UNCOMMENT ME (FIXME) remove_edge(iter, g);

    // The following assertion fails with message:
    //   error: use of undeclared identifier 'remove_out_edge_if'
    // UNCOMMENT ME (FIXME) remove_out_edge_if(u, p, g);
  } // Technical scope

  //////////////////////////////////////////////////////////////////////////
  //////////// BOOST_CONCEPT_ASSERT( (< MutableEdgeListGraphConcept G>) );
  // The following is the unfolding of the boost::MutableEdgeListGraphConcept
  // concept on debugging (of Polyhedron) purposes.
  // The following unfolding is necessary because the MutableEdgeListGraph
  // concept inherits from the EdgeMutableGraph concept that currently fails
  // (refer above).
  { // Technical scope to avoid variable/type collisions with other tests
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    // G g;
    // boost::concepts::dummy_edge_predicate<edge_descriptor> p;
    // The following assertion fails with message:
    //   error: use of undeclared identifier 'remove_edge_if'
    // UNCOMMENT ME (FIXME) remove_edge_if(p, g);
  } // Technical scope

  //////////////////////////////////////////////////////////////////////////
  ////////// BOOST_CONCEPT_ASSERT( (< MutableBidirectionalGraphConcept G>) );
  // The following is the unfolding of the
  // boost::MutableBidirectionalGraphConcept concept on debugging (of Linear
  // Cell Complex) purposes. The following unfolding is necessary because
  // the MutableBidirectionalGraph concept inherits from the
  // EdgeMutableGraph concept that currently fails (refer above).
  { // Technical scope to avoid variable/type collisions with other tests
    typedef typename graph_traits< G >::edge_descriptor edge_descriptor;
    // G g;
    // boost::concepts::dummy_edge_predicate<edge_descriptor> p;
    // typename boost::graph_traits<G>::vertex_descriptor u;
    // The following assertion fails with message:
    //   error: use of undeclared identifier 'remove_in_edge_if'
    // UNCOMMENT ME (FIXME) remove_in_edge_if(u, p, g);
  } // Technical scope


  BOOST_CONCEPT_ASSERT((VertexMutableGraphConcept< G >));

  //////////////////////////////////////////////////////////////////////////
  //////////// BOOST_CONCEPT_ASSERT( (MutableGraphConcept< G>) );
  // MutableGraph concept doesn't introduce new expressions. It only fails
  // because the EdgeMutableGraph concept from which MutableGraph inherits
  // fails.

  BOOST_CONCEPT_ASSERT(
      (PropertyGraphConcept< G,
                             graph_traits< G >::vertex_descriptor,
                             vertex_point_t >));
  BOOST_CONCEPT_ASSERT((FEVV::CGALHalfedgeGraph< G >));
  BOOST_CONCEPT_ASSERT((FEVV::CGALHalfedgeListGraph< G >));
  BOOST_CONCEPT_ASSERT((FEVV::CGALMutableHalfedgeGraph< G >));

  BOOST_CONCEPT_ASSERT((FEVV::CGALFaceGraph< G >));
  BOOST_CONCEPT_ASSERT((FEVV::CGALFaceListGraph< G >));
  BOOST_CONCEPT_ASSERT((FEVV::CGALMutableFaceGraph< G >));

  // Just to test the implementation of the FEVV::MutableHalfedgeFaceListGraph
  // concept as opposed to the concept itself. Indeed this concept is
  // just a syntactic gathering of above already asserted concepts (and
  // as such should never fails provided the above succeeds).
  BOOST_CONCEPT_ASSERT((FEVV::MutableHalfedgeFaceListGraph< G >));

  //////////////////////////////////////////////////////////////////////////
  // The following are not mandatory within the FEVV layer. It is just to
  // to document some technical perks or failures of OpenMesh.
  // effective.
  // BOOST_CONCEPT_ASSERT( (concepts::AdjacencyGraph<  G >) );
  // Above assertion fails.

  return 0;
}
