//insert the Headername here
#ifndef SUBDIVISIONNODE_H
#define SUBDIVISIONNODE_H

#include "scene/2d/node_2d.h"

#include "scene/2d/mesh_instance_2d.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/os/input.h"
#include "he_mesh.h"
#include "objparse.h"
using namespace meshparse;
class SubdivisionNode : public MeshInstance2D {
	GDCLASS(SubdivisionNode, MeshInstance2D);

protected:
	int numSubdivisions;
	int numTriangles;
	meshparse::mesh* he_mesh;
	//original
	PoolVector2Array vertices;
	PoolColorArray colors;

	//updated
	PoolVector2Array _vertices;
	PoolColorArray _colors;
	
	bool redraw;
public:
	SubdivisionNode();

	void _notification(int p_what);
	void _update();
	void _ready();
	void _draw();
	void _input(InputEvent* e);

};

#endif
