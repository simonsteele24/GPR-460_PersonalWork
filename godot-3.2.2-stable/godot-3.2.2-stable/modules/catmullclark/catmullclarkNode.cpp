#include "catmullclarkNode.h"

#include "trimesh.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

struct Face {
	vector<int> nurbs;
};

trimesh_t ReadInFile() {
	ifstream objFile;
	string input;

	vector<vertex> verteces;
	vector<triangle_t> triangles;

	objFile.open("C:\\Users\\simon\\Desktop\\untitled.obj");

	while (!objFile.eof()) {
		objFile >> input;

		if (input == "v") {
			objFile >> input;
			float newX = stof(input);
			objFile >> input;
			objFile >> input;
			float newY = stof(input);
			verteces.push_back(vertex(newX, newY));
		}

		if (input == "f") {
			triangles.push_back(triangle_t());
			objFile >> input;
			int indexOne = input[0] - '0';
			objFile >> input;
			int indexTwo = input[0] - '0';
			objFile >> input;
			int indexThree = input[0] - '0';

			triangles.back().v[0] = indexOne - 1;
			triangles.back().v[1] = indexTwo - 1;
			triangles.back().v[2] = indexThree - 1;

			triangles.back().positions[0] = verteces[indexOne - 1];
			triangles.back().positions[1] = verteces[indexTwo - 1];
			triangles.back().positions[2] = verteces[indexThree - 1];
		}
	}

	const int kNumVertices = verteces.size();

	vector<edge_t> edges;
	unordered_edges_from_triangles(triangles.size(), &triangles[0], edges);

	trimesh_t mesh;
	mesh.build(kNumVertices, triangles.size(), &triangles, edges.size(), &edges[0], &verteces);

	vector<vertex> points;
	points = mesh.generateEdgePoints();

	// Use 'mesh' to walk the connectivity.
	vector<index_t> neighs;
	for (int vi = 0; vi < kNumVertices; ++vi) {
		mesh.vertex_vertex_neighbors(vi, neighs);

		cout << "neighbors of vertex " << vi << ": ";
		for (int i = 0; i < neighs.size(); ++i) {
			cout << ' ' << neighs.at(i);
		}
		cout << '\n';
	}
	cout << "Num Of Verteces: " << verteces.size() << endl;
	cout << "Num Of Edge Points: " << points.size() << endl;
	return mesh;
}

CatmullClarkNode::CatmullClarkNode() {
	numSubdivisions = 0;
	redraw = true;
}

//Bind all your methods used in this class

//Custom Functions
void CatmullClarkNode::_ready() {
	numTriangles = 2;
	set_process(true);
	set_process_input(true);

	trimesh_t newMesh = ReadInFile();
	vector<vertex> newPositions = newMesh.getAllVertexPositions();

	for (int i = 0; i < newPositions.size(); i++) {
		vertices.push_back(Vector2(newPositions[i].x, newPositions[i].y));
		colors.append(Color(0, 1, 0));
		_vertices.push_back(Vector2(newPositions[i].x, newPositions[i].y));
		_colors.append(Color(0, 1, 0));
	}
}

void CatmullClarkNode::_update() {
	int _numTriangles = pow(4, numSubdivisions);

	if (_numTriangles > 1 && redraw && false) //no need to enter if we are using just the base mesh
	{
		_vertices.resize(0);
		_colors.resize(0);
		for (int i = 0; i < vertices.size(); i += 3) {
			//get the three points for each triangle
			Vector2 v0 = vertices.get(i);
			Vector2 v1 = vertices.get(i + 1);
			Vector2 v2 = vertices.get(i + 2);
			Color c0 = colors.get(i);
			Color c1 = colors.get(i + 1);
			Color c2 = colors.get(i + 2);
			//find out how many triangles one triangle will subdivide into
			//you can already see not using an half edge mesh makes it so difficult to do a simple midpoint subdivision
			float increment = 1.0 / (numSubdivisions + 1);
			float u = 0;
			float v = 0; // the algorithm uses the concept of barrycentric coordinates to do the subdivision

			int fcounter = numSubdivisions + 1;

			while (fcounter > 0) {
				int bcounter = 0;
				while (bcounter < fcounter) {
					Vector2 t0 = v0 * (1 - (u + v)) + v1 * u + v * v2;
					_vertices.push_back(t0);
					Vector2 t1 = v0 * (1 - (u + increment + v)) + v1 * (u + increment) + v * v2;
					_vertices.push_back(t1);
					Vector2 t2 = v0 * (1 - (u + v + increment)) + v1 * u + (v + increment) * v2;
					_vertices.push_back(t2);

					Color ct0 = c0 * (1 - (u + v)) + c1 * u + c2 * v;
					_colors.push_back(ct0);
					Color ct1 = c0 * (1 - (u + increment + v)) + c1 * (u + increment) + c2 * v;
					_colors.push_back(ct1);
					Color ct2 = c0 * (1 - (u + v + increment)) + c1 * (v + increment) + c2 * u;
					_colors.push_back(ct2);
					u += increment;
					bcounter++;
				}
				//reverse
				u -= increment;
				v += increment;
				bcounter = 0;
				while (bcounter < fcounter - 1) {
					Vector2 t0 = v0 * (1 - (u + v)) + v1 * u + v * v2;
					_vertices.push_back(t0);
					Vector2 t1 = v0 * (1 - (u - increment + v)) + v1 * (u - increment) + v * v2;
					_vertices.push_back(t1);
					Vector2 t2 = v0 * (1 - (u + v - increment)) + v1 * u + (v - increment) * v2;
					_vertices.push_back(t2);

					Color ct0 = c0 * (1 - (u + v)) + c1 * u + c2 * v;
					_colors.push_back(ct0);
					Color ct1 = c0 * (1 - (u - increment + v)) + c1 * (u - increment) + c2 * v;
					_colors.push_back(ct1);
					Color ct2 = c0 * (1 - (u + v - increment)) + c1 * (v - increment) + c2 * u;
					_colors.push_back(ct2);
					u -= increment;
					bcounter++;
				}
				fcounter--;
			}
		}
	}
}

void CatmullClarkNode::_draw() {
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

void CatmullClarkNode::_input(InputEvent *e) {
	if (e->is_action_pressed("ui_up")) {
		ReadInFile();
		numSubdivisions += 1;
		if (numSubdivisions > 5)
			numSubdivisions = 1;
		redraw = true;
	}
}

void CatmullClarkNode::_notification(int p_what) {

	switch (p_what) {
		case NOTIFICATION_PROCESS: {
			if (Input::get_singleton()->is_action_pressed("ui_up")) {
				numSubdivisions += 1;
				if (numSubdivisions > 5)
					numSubdivisions = 1;
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
