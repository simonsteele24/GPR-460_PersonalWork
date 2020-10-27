//insert the Headername here
#ifndef CATMULLCLARKNODE_H
#define CATMULLCLARKNODE_H

#include "scene/2d/node_2d.h"

#include "scene/2d/mesh_instance_2d.h"
#include "scene/resources/mesh.h"
#include "core/math/triangle_mesh.h"
#include "core/os/input.h"

class CatmullClarkNode : public MeshInstance2D {
	GDCLASS(CatmullClarkNode, MeshInstance2D);

protected:
	int numSubdivisions;
	int numTriangles;
	//original
	PoolVector2Array vertices;
	PoolColorArray colors;

	//updated
	PoolVector2Array _vertices;
	PoolColorArray _colors;
	bool redraw;

public:
	CatmullClarkNode();

	void _notification(int p_what);
	void _update();
	void _ready();
	void _draw();
	void _input(InputEvent *e);
};

#endif
