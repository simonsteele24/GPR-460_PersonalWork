#include "SubdivisionNode.h"
#include <iostream>
#include <fstream>
SubdivisionNode::SubdivisionNode()
{
	numSubdivisions = 0;
	redraw = true;
	he_mesh = new meshparse::mesh();
	std::ifstream infile;
	infile.open("C:\\Users\\simon.steele\\Desktop\\untitled.obj");
	meshparse::load_obj(infile, *he_mesh);
}

//Bind all your methods used in this class



//Custom Functions
void SubdivisionNode::_ready()
{
	he_mesh->subdivide(0);
	numTriangles = he_mesh->faces.size();
	set_process(true);
	set_process_input(true);
	for (std::vector<face*>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it)
	{
		Vector3 v0, v1, v2;
		v0 = (*it)->e->vert->loc;
		vertices.push_back(Vector2(v0.x,v0.z));
		v1 = (*it)->e->next->vert->loc;
		vertices.push_back(Vector2(v1.x, v1.z));
		v2 = (*it)->e->next->next->vert->loc;
		vertices.push_back(Vector2(v2.x, v2.z));

		colors.append(Color(1, 1, 1));
		colors.append(Color(0, 1, 0));
		colors.append(Color(0, 0, 1));

	}
	for (int i = 0; i < vertices.size(); i++)
	{
		cout << "Vertex: " << i << endl << "X: " << vertices[i].x << endl << "Y: " << vertices[i].y << endl << endl;
	}

	_vertices = vertices;
	_colors = colors;
	
	////6 vertices for the two triangles 
	//vertices.push_back(Vector2(0, 100));
	//vertices.push_back(Vector2(100, 0));
	//vertices.push_back(Vector2(0, 0));
	//vertices.push_back(Vector2(0, 100));
	//vertices.push_back(Vector2(100, 100));
	//vertices.push_back(Vector2(100, 0));

	//colors.append(Color(1, 1, 1));
	//colors.append(Color(0, 1, 0));
	//colors.append(Color(0, 0, 1));
	//colors.append(Color(1, 0, 0));
	//colors.append(Color(0, 0, 0));
	//colors.append(Color(0, 1, 0));

	////Copying the data into another set
	//_vertices.push_back(Vector2(0, 100));
	//_vertices.push_back(Vector2(100, 0));
	//_vertices.push_back(Vector2(0, 0));
	//_vertices.push_back(Vector2(0, 100));
	//_vertices.push_back(Vector2(100, 100));
	//_vertices.push_back(Vector2(100, 0));



	//_colors.append(Color(1, 1, 1));
	//_colors.append(Color(0, 1, 0));
	//_colors.append(Color(0, 0, 1));
	//_colors.append(Color(1, 0, 0));
	//_colors.append(Color(0, 0, 0));
	//_colors.append(Color(0, 1, 0));

	

}

void SubdivisionNode::_update()
{	
	int _numTriangles = pow(4, numSubdivisions);
	if (_numTriangles > 1 && redraw)//no need to enter if we are using just the base mesh
	{
		_vertices.resize(0);
		_colors.resize(0);
		for (int i = 0; i < vertices.size(); i += 3)
		{
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
				
				
			while(fcounter > 0)
			{
				int bcounter = 0;
				while (bcounter < fcounter)
				{
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
				while (bcounter<fcounter-1)
				{
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

void SubdivisionNode::_draw()
{
	if (redraw)
	{
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

void SubdivisionNode::_input(InputEvent* e)
{
	if (e->is_action_pressed("ui_up"))
	{
		numSubdivisions += 1;
		if (numSubdivisions > 5)
			numSubdivisions = 1;
		redraw = true;

	}
}

void SubdivisionNode::_notification(int p_what)
{

	switch (p_what) {
	case NOTIFICATION_PROCESS:
	{
		if (Input::get_singleton()->is_action_pressed("ui_up") ){
			//numSubdivisions += 1;
			//if (numSubdivisions > 5)
				//numSubdivisions = 1;
			//redraw = true;
			SceneTree::get_singleton()->set_input_as_handled();
		}
		_update();
		
		update();
	} break;
	case NOTIFICATION_READY:
	{
		_ready();
	}break;
	case NOTIFICATION_DRAW:
	{
		_draw();
	}break;

	}
}

