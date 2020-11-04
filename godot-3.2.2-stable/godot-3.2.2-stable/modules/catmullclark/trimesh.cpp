#include "trimesh.h"

// needed for implementation
#include <cassert>
#include <set>
#include <iostream>
#include <algorithm>


typedef std::map< std::pair< trimesh_t::index_t, trimesh_t::index_t >, trimesh_t::index_t > directed_edge2index_map_t;
trimesh_t::index_t directed_edge2face_index( const directed_edge2index_map_t& de2fi, trimesh_t::index_t vertex_i, trimesh_t::index_t vertex_j )
{
    assert( !de2fi.empty() );
    
    directed_edge2index_map_t::const_iterator it = de2fi.find( std::make_pair( vertex_i, vertex_j ) );
    
    // If no such directed edge exists, then there's no such face in the mesh.
    // The edge must be a boundary edge.
    // In this case, the reverse orientation edge must have a face.
    if( it == de2fi.end() )
    {
        assert( de2fi.find( std::make_pair( vertex_j, vertex_i ) ) != de2fi.end() );
        return -1;
    }
    
    return it->second;
}

void trimesh_t::build(const unsigned long num_vertices, const unsigned long num_triangles, const std::vector<triangle_t> *triangles, const unsigned long num_edges, const edge_t *edges, const std::vector<vertex> *_verteces) {
    /*
    Generates all half edge data structures for the mesh given by its vertices 'self.vs'
    and faces 'self.faces'.
    
    Python version used heavily
    */
    
    assert( triangles );
    assert( edges );

	m_face_positions.clear();

	m_faces = *triangles;

    directed_edge2index_map_t de2fi;
    for( int fi = 0; fi < num_triangles; ++fi )
    {
        const triangle_t& tri = triangles[0][fi];
        de2fi[ std::make_pair( tri.v[0], tri.v[1] ) ] = fi;
        de2fi[ std::make_pair( tri.v[1], tri.v[2] ) ] = fi;
        de2fi[ std::make_pair( tri.v[2], tri.v[0] ) ] = fi;
		m_face_positions.push_back(getAverage({tri.positions[0],tri.positions[1],tri.positions[2]}));
    }

	clear();

    m_vertex_halfedges.resize( num_vertices, -1 );
    m_face_halfedges.resize( num_triangles, -1 );
    m_edge_halfedges.resize( num_edges, -1 );
    m_halfedges.reserve( num_edges*2 );
	m_vertex_positions = *_verteces;
    
    for( int ei = 0; ei < num_edges; ++ei )
    {
        const edge_t& edge = edges[ei];
        
        // Add the halfedge_t structures to the end of the list.
        const index_t he0index = m_halfedges.size();
        m_halfedges.push_back( halfedge_t() );
        halfedge_t& he0 = m_halfedges.back();
        
        const index_t he1index = m_halfedges.size();
        m_halfedges.push_back( halfedge_t() );
        halfedge_t& he1 = m_halfedges.back();
        
        // The face will be -1 if it is a boundary half-edge.
        he0.face = directed_edge2face_index( de2fi, edge.v[0], edge.v[1] );
        he0.to_vertex = edge.v[1];
        he0.edge = ei;
        
        // The face will be -1 if it is a boundary half-edge.
        he1.face = directed_edge2face_index( de2fi, edge.v[1], edge.v[0] );
        he1.to_vertex = edge.v[0];
        he1.edge = ei;
        
        // Store the opposite half-edge index.
        he0.opposite_he = he1index;
        he1.opposite_he = he0index;
        
        // Also store the index in our m_directed_edge2he_index map.
        assert( m_directed_edge2he_index.find( std::make_pair( edge.v[0], edge.v[1] ) ) == m_directed_edge2he_index.end() );
        assert( m_directed_edge2he_index.find( std::make_pair( edge.v[1], edge.v[0] ) ) == m_directed_edge2he_index.end() );
        m_directed_edge2he_index[ std::make_pair( edge.v[0], edge.v[1] ) ] = he0index;
        m_directed_edge2he_index[ std::make_pair( edge.v[1], edge.v[0] ) ] = he1index;
        
        // If the vertex pointed to by a half-edge doesn't yet have an out-going
        // halfedge, store the opposite halfedge.
        // Also, if the vertex is a boundary vertex, make sure its
        // out-going halfedge is a boundary halfedge.
        // NOTE: Halfedge data structure can't properly handle butterfly vertices.
        //       If the mesh has butterfly vertices, there will be multiple outgoing
        //       boundary halfedges.  Because we have to pick one as the vertex's outgoing
        //       halfedge, we can't iterate over all neighbors, only a single wing of the
        //       butterfly.
        if( m_vertex_halfedges[ he0.to_vertex ] == -1 || -1 == he1.face )
        {
            m_vertex_halfedges[ he0.to_vertex ] = he0.opposite_he;
        }
        if( m_vertex_halfedges[ he1.to_vertex ] == -1 || -1 == he0.face )
        {
            m_vertex_halfedges[ he1.to_vertex ] = he1.opposite_he;
        }
        
        // If the face pointed to by a half-edge doesn't yet have a
        // halfedge pointing to it, store the halfedge.
        if( -1 != he0.face && m_face_halfedges[ he0.face ] == -1 )
        {
            m_face_halfedges[ he0.face ] = he0index;
        }
        if( -1 != he1.face && m_face_halfedges[ he1.face ] == -1 )
        {
            m_face_halfedges[ he1.face ] = he1index;
        }
        
        // Store one of the half-edges for the edge.
        assert( m_edge_halfedges[ ei ] == -1 );
        m_edge_halfedges[ ei ] = he0index;
    }
    
    // Now that all the half-edges are created, set the remaining next_he field.
    // We can't yet handle boundary halfedges, so store them for later.
    std::vector< index_t > boundary_heis;
    for( int hei = 0; hei < m_halfedges.size(); ++hei )
    {
        halfedge_t& he = m_halfedges.at( hei );
        // Store boundary halfedges for later.
        if( -1 == he.face )
        {
            boundary_heis.push_back( hei );
            continue;
        }
        
        const triangle_t& face = triangles[0][ he.face ];
        const index_t i = he.to_vertex;
        
        index_t j = -1;
        if( face.v[0] == i ) j = face.v[1];
        else if( face.v[1] == i ) j = face.v[2];
        else if( face.v[2] == i ) j = face.v[0];
        assert( -1 != j );
        
        he.next_he = m_directed_edge2he_index[ std::make_pair(i,j) ];
    }
    
    // Make a map from vertices to boundary halfedges (indices) originating from them.
    // NOTE: There will only be multiple originating boundary halfedges at butterfly vertices.
    std::map< index_t, std::set< index_t > > vertex2outgoing_boundary_hei;
    for( std::vector< index_t >::const_iterator hei = boundary_heis.begin(); hei != boundary_heis.end(); ++hei )
    {
        const index_t originating_vertex = m_halfedges[ m_halfedges[ *hei ].opposite_he ].to_vertex;
        vertex2outgoing_boundary_hei[ originating_vertex ].insert( *hei );
        if( vertex2outgoing_boundary_hei[ originating_vertex ].size() > 1 )
        {
            std::cerr << "Butterfly vertex encountered.\n";
        }
    }
    
    // For each boundary halfedge, make its next_he one of the boundary halfedges
    // originating at its to_vertex.
    for( std::vector< index_t >::const_iterator hei = boundary_heis.begin(); hei != boundary_heis.end(); ++hei )
    {
        halfedge_t& he = m_halfedges[ *hei ];
        
        std::set< index_t >& outgoing = vertex2outgoing_boundary_hei[ he.to_vertex ];
        if( !outgoing.empty() )
        {
            std::set< index_t >::iterator outgoing_hei = outgoing.begin();
            he.next_he = *outgoing_hei;
            
            outgoing.erase( outgoing_hei );
        }
    }
    
#ifndef NDEBUG
    for( std::map< index_t, std::set< index_t > >::const_iterator it = vertex2outgoing_boundary_hei.begin(); it != vertex2outgoing_boundary_hei.end(); ++it )
    {
        assert( it->second.empty() );
    }
#endif
}

std::vector< trimesh_t::index_t > trimesh_t::boundary_vertices() const
{
    /*
    Returns a list of the vertex indices on the boundary.
    
    untested
    */
    
    std::set< index_t > result;
    for( int hei = 0; hei < m_halfedges.size(); ++hei )
    {
        const halfedge_t& he = m_halfedges[ hei ];
        
        if( -1 == he.face )
        {
            // result.extend( self.he_index2directed_edge( hei ) )
            result.insert( he.to_vertex );
            result.insert( m_halfedges[ he.opposite_he ].to_vertex );
        }
    }
    
    return std::vector< index_t >( result.begin(), result.end() );
}

std::vector< std::pair< trimesh_t::index_t, trimesh_t::index_t > > trimesh_t::boundary_edges() const
{
    /*
    Returns a list of undirected boundary edges (i,j).  If (i,j) is in the result, (j,i) will not be.
    
    untested
    */
    
    std::vector< std::pair< index_t, index_t > > result;
    for( int hei = 0; hei < m_halfedges.size(); ++hei )
    {
        const halfedge_t& he = m_halfedges[ hei ];
        
        if( -1 == he.face )
        {
            result.push_back( he_index2directed_edge( hei ) );
        }
    }
    
    return result;
}

void unordered_edges_from_triangles( const unsigned long num_triangles, const triangle_t* triangles, std::vector< edge_t >& edges_out )
{
    typedef std::set< std::pair< index_t, index_t > > edge_set_t;
    edge_set_t edges;
    for( int t = 0; t < num_triangles; ++t )
    {
        edges.insert( std::make_pair( std::min( triangles[t].i(), triangles[t].j() ), std::max( triangles[t].i(), triangles[t].j() ) ) );
        edges.insert( std::make_pair( std::min( triangles[t].j(), triangles[t].k() ), std::max( triangles[t].j(), triangles[t].k() ) ) );
        edges.insert( std::make_pair( std::min( triangles[t].k(), triangles[t].i() ), std::max( triangles[t].k(), triangles[t].i() ) ) );
    }
    
    edges_out.resize( edges.size() );
    int e = 0;
    for( edge_set_t::const_iterator it = edges.begin(); it != edges.end(); ++it, ++e )
    {
        edges_out.at(e).start() = it->first;
        edges_out.at(e).end() = it->second;
    }
}

std::vector<vertex> trimesh_t::getAllVertexPositions()
{
	std::vector<vertex> newVerts;

	for (int i = 0; i < m_faces.size(); i++)
	{
		for (int j = 0; j < m_faces[i].positions.size(); j++)
		{
			newVerts.push_back(m_faces[i].positions[j]);
		}
	}

	return newVerts;
}

vertex getAverage(std::vector<vertex> verteces)
{
	float totalX = 0, totalY = 0;
	float numOfEntries = verteces.size();

	if (numOfEntries == 0)
	{
		return vertex();
	}

	for (int i = 0; i < verteces.size(); i++)
	{
		totalX += verteces[i].x;
		totalY += verteces[i].y;
	}

	return vertex(totalX / numOfEntries, totalY / numOfEntries);
}

std::vector<vertex> trimesh_t::generateEdgePoints()
{
	vector<vertex> edgePoints;
	for (int i = 0; i < m_halfedges.size(); i++)
	{
		edgePoints.push_back(getAverage({m_vertex_positions[m_halfedges[i].to_vertex], m_vertex_positions[m_halfedges[m_halfedges[i].next_he].to_vertex]}));
	}
	return edgePoints;
}

std::vector<vertex> trimesh_t::generateNewVertexPoints()
{
	std::vector<vertex> newPoints;
	for (int i = 0; i < m_vertex_positions.size(); i++)
	{
		int valance = vertex_valence(i);
		std::vector<index_t> positions = vertex_vertex_neighbors(i);
		std::vector<vertex> midpoints;
		for (int j = 0; j < positions.size(); j++)
		{
			midpoints.push_back(to_edgepoint(i,positions[j]));
		}
		vertex midpointAverage = getAverage(midpoints);
		positions.clear();
		std::vector<vertex> facePoints;
		positions = vertex_face_neighbors(i);
		for (int j = 0; j < positions.size(); j++) 
		{
			facePoints.push_back(m_face_positions[j]);
		}
		vertex facePointAverage = getAverage(facePoints);

		float finalX = (facePointAverage.x / valance) + ((2 * midpointAverage.x)/valance) + (m_vertex_positions[i].x/valance);
		float finalY =(facePointAverage.y / valance) + ((2 * midpointAverage.y)/valance) + (m_vertex_positions[i].y/valance);
		
		newPoints.push_back(vertex(finalX,finalY));
	}
	return newPoints;
}
