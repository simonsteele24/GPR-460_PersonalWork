#include "catmullclarkNode.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include "trimesh.h"

using namespace std;

struct Face {
	vector<int> nurbs;
};

void ReadInFile() {
	vector<triangle_t> triangles;

	// ... fill triangles ...
	triangles.resize(2);
	triangles[0].v[0] = 0;
	triangles[0].v[1] = 1;
	triangles[0].v[2] = 2;
	triangles[1].v[0] = 2;
	triangles[1].v[1] = 1;
	triangles[1].v[2] = 3;
	const int kNumVertices = 4;

	vector<edge_t> edges;
	unordered_edges_from_triangles(triangles.size(), &triangles[0], edges);

	trimesh_t mesh;
	mesh.build(kNumVertices, triangles.size(), &triangles[0], edges.size(), &edges[0]);

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

	/*ifstream myfile("C:\\Users\\simon\\Desktop\\untitled.obj");

	string input;

	vector<Vector2> verteces;
	vector<Face> newFaces;

	bool makingFace = false;
	Face tempFace;

	while (!myfile.eof()) {
		myfile >> input;

		if (input == "f")
		{
			if (makingFace == true)
			{
				newFaces.push_back(tempFace);
			}

			tempFace.nurbs.clear();
			makingFace = true;
		}

		if (makingFace)
		{
			tempFace.nurbs.push_back(1);
		}

		if (input == "v") {
			myfile >> input;
			float x = stof(input);
			myfile >> input;
			float y = stof(input);
			myfile >> input;
			float z = stof(input);
			verteces.push_back(Vector2(x, y));
		}
	}

	newFaces.push_back(tempFace);

	cout << newFaces.size() << endl;

	myfile.close();
	*/
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

	//6 vertices for the two triangles
	vertices.push_back(Vector2(0, 100));
	vertices.push_back(Vector2(100, 0));
	vertices.push_back(Vector2(0, 0));
	vertices.push_back(Vector2(0, 100));
	vertices.push_back(Vector2(100, 100));
	vertices.push_back(Vector2(100, 0));

	colors.append(Color(1, 1, 1));
	colors.append(Color(0, 1, 0));
	colors.append(Color(0, 0, 1));
	colors.append(Color(1, 0, 0));
	colors.append(Color(0, 0, 0));
	colors.append(Color(0, 1, 0));

	//Copying the data into another set
	_vertices.push_back(Vector2(0, 100));
	_vertices.push_back(Vector2(100, 0));
	_vertices.push_back(Vector2(0, 0));
	_vertices.push_back(Vector2(0, 100));
	_vertices.push_back(Vector2(100, 100));
	_vertices.push_back(Vector2(100, 0));

	_colors.append(Color(1, 1, 1));
	_colors.append(Color(0, 1, 0));
	_colors.append(Color(0, 0, 1));
	_colors.append(Color(1, 0, 0));
	_colors.append(Color(0, 0, 0));
	_colors.append(Color(0, 1, 0));
}

void CatmullClarkNode::_update() {
	int _numTriangles = pow(4, numSubdivisions);
	ReadInFile();
	if (_numTriangles > 1 && redraw) //no need to enter if we are using just the base mesh
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

/*
using std::back_inserter;
using std::cout;
using std::endl;
using std::istream;
using std::istream_iterator;
using std::istringstream;
using std::string;
using std::vector;

struct objface {
	unsigned int id;
	vector<unsigned int> vids;
	vector<unsigned int> nids;
};

struct mesh
{
	vector<Vector2> verteces;
};

struct vertex 
{
	Vector2 loc;
	int id;
};

vector<struct objface> objfaces;

int obj_parse_vertex_spec(const string vspec) {
	unsigned int vid;
	sscanf(vspec.c_str(), "%d", &vid);
	return vid;
}

void obj_parse_line(mesh &objm, string line) {
	// TODO: support vn directives
	if (line[0] == 'v' && line[1] == ' ') {
		vertex *v = new vertex();

		float x, y, z;
		sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
		v->loc = Vector2(x, y);
		v->id = objm.verteces.size() + 1;

		objm.verteces.push_back(v);
	} else if (line[0] == 'f' && line[1] == ' ') {
		istringstream tokenizer(line);
		vector<string> tokens;
		copy(istream_iterator<string>(tokenizer),
				istream_iterator<string>(),
				back_inserter<vector<string> >(tokens));

		struct objface f;
		f.id = objfaces.size() + 1;
		for (unsigned int i = 1; i < tokens.size(); i++) {
			string token = tokens[i];
			f.vids.push_back(obj_parse_vertex_spec(token));
		}

		objfaces.push_back(f);
	}
}

void obj_add_triangle(mesh &objm, vector<unsigned int> vids) {
	face *f = new face();
	f->id = objm.faces.size() + 1;

	edge *last_edge;
	for (unsigned int i = 0; i < vids.size(); i++) {
		edge *e = new edge();
		e->vert = objm.verteces[vids[i] - 1];
		objm.verteces[vids[i] - 1]->e = e;
		e->f = f;
		e->id = objm.edges.size() + 1;
		e->pair = NULL;
		if (i != 0) {
			last_edge->next = e;
		} else {
			f->e = e;
		}

		last_edge = e;
		objm.edges.push_back(e);
	}
	last_edge->next = f->e;
	f->calculate_normal();
	objm.faces.push_back(f);
}

bool load_obj(istream &file, mesh &mesh) {
	if (!file.good()) {
		cout << "Could not read file." << endl;
		return false;
	}

	string line;
	while (file.good()) {
		getline(file, line);
		obj_parse_line(mesh, line);
	}

	for (auto objf = objfaces.begin(); objf != objfaces.end(); objf++) {
		obj_add_triangle(mesh, objf->vids);
	}
	merge_half_edges(mesh);

	cout << "Loaded mesh: " << endl
		 << "  " << mesh.verteces.size() << " verteces." << endl
		 << "  " << mesh.edges.size() << " edges." << endl
		 << "  " << objfaces.size() << " faces in OBJ file." << endl;
	return true;
}
*/
