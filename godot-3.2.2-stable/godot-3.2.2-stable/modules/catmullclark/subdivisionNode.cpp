#include "SubdivisionNode.h"
#include <fstream>
#include <iostream>
SubdivisionNode::SubdivisionNode() {
	numSubdivisions = 0;
	redraw = true;
	he_mesh = new meshparse::mesh();
	std::ifstream infile;
	infile.open("C:\\Users\\simon\\Desktop\\untitled.obj");
	meshparse::load_obj(infile, *he_mesh);
}

//Bind all your methods used in this class

//Custom Functions
void SubdivisionNode::_ready() {

	numTriangles = he_mesh->faces.size();
	set_process(true);
	set_process_input(true);
	for (std::vector<face *>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it) {
		Vector3 v0, v1, v2;
		v0 = (*it)->e->vert->loc;
		vertices.push_back(Vector2(v0.x, v0.z));
		v1 = (*it)->e->next->vert->loc;
		vertices.push_back(Vector2(v1.x, v1.z));
		v2 = (*it)->e->next->next->vert->loc;
		vertices.push_back(Vector2(v2.x, v2.z));

		colors.append(Color(1, 1, 1));
		colors.append(Color(0, 1, 0));
		colors.append(Color(0, 0, 1));
	}

	_vertices = vertices;
	_colors = colors;
}

void SubdivisionNode::_update() {
	if (redraw) //no need to enter if we are using just the base mesh
	{
		meshparse::mesh *newMesh = new meshparse::mesh(*he_mesh); 

		for (int j = 0; j < numSubdivisions; j++)
		{
			newMesh->controlPoints.clear();
			newMesh->newEdgePoints.clear();
			int length = newMesh->faces.size();

			// Step One catmull clark
			for (int i = 0; i < length; i++)
			{
				newMesh->subdivide(i);
			}

			// Step Two catmull clark
			meshparse::generateVertexData(*newMesh);
			newMesh->changeEdgePoints();

			// Step Three catmull clark
			newMesh->changeControlPoints();


			for (int i = 0; i < length; i++)
			{
				newMesh->reconnectFaces(0);
			}
		}

		numTriangles = newMesh->faces.size();
		set_process(true);
		set_process_input(true);
		for (std::vector<face *>::iterator it = newMesh->faces.begin(); it != newMesh->faces.end(); ++it) {
			Vector3 v0, v1, v2;
			v0 = (*it)->e->vert->loc;
			vertices.push_back(Vector2(v0.x, v0.z));
			v1 = (*it)->e->next->vert->loc;
			vertices.push_back(Vector2(v1.x, v1.z));
			v2 = (*it)->e->next->next->vert->loc;
			vertices.push_back(Vector2(v2.x, v2.z));

			colors.append(Color(1, 1, 1));
			colors.append(Color(0, 1, 0));
			colors.append(Color(0, 0, 1));
		}

		_vertices = vertices;
		_colors = colors;
	}
}

void SubdivisionNode::_draw() {
	if (redraw) {
		Ref<ArrayMesh> a = memnew(ArrayMesh);
		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = _vertices; // required
		arrays[ArrayMesh::ARRAY_COLOR] = _colors;

		//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene

		a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);

		if (this != NULL)
			this->set_mesh(a);
		redraw = false;
	}
}

void SubdivisionNode::_input(InputEvent *e) {
	if (e->is_action_pressed("ui_up")) {
		numSubdivisions += 1;
		if (numSubdivisions > 5)
			numSubdivisions = 1;
		redraw = true;
	}
}

void SubdivisionNode::_notification(int p_what) {

	switch (p_what) {
		case NOTIFICATION_PROCESS: {
			if (Input::get_singleton()->is_action_pressed("ui_up")) {
				numSubdivisions += 1;
				if (numSubdivisions > 5)
					numSubdivisions = 0;
				redraw = true;
				SceneTree::get_singleton()->set_input_as_handled();
			}
			_update();

			update();
		} break;
		case NOTIFICATION_READY: {
			_ready();
		} break;
		case NOTIFICATION_DRAW: {
			_draw();
		} break;
	}
}

void changeEdgePoints()
{

}
