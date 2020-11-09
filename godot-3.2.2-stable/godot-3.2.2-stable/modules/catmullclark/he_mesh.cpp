#include "he_mesh.h"
#include <iostream>
namespace meshparse {

using std::cout;
using std::endl;
using std::vector;

vertex::vertex() {
	loc.zero();
	normal.zero();
}

/* This is here to allow for easy breakpoints to find places where copying takes
 * place. */
inline void vertex_copy() {
	cout << "vertex copied" << endl;
}

inline void mesh_copy() {
	cout << "mesh copied" << endl;
}

vertex::vertex(const vertex &other) {
#ifdef COPY_CHECKS
	vertex_copy();
#endif
	loc = other.loc;
	normal = other.normal;
	e = other.e;
	id = other.id;
}

void vertex::addEdgePoint(Vector3 newPoint) {
	if (!(std::count(edgePoints.begin(), edgePoints.end(), newPoint))) {
		edgePoints.push_back(newPoint);
	}
}

void vertex::addFacePoint(Vector3 newPoint) {
	if (!(std::count(facePoints.begin(), facePoints.end(), newPoint))) {
		facePoints.push_back(newPoint);
	}
}

bool vertex::operator==(const vertex &other) {
	return loc == other.loc;
}

bool vertex::onboundary() const {
	edge *eloop = e;
	do
		eloop = eloop->next->pair;
	while (eloop != e && eloop != NULL);
	return eloop == NULL;
}

edge *edge::previous() const {
	edge *prev = next;
	while (prev->next != this)
		prev = prev->next;
	return prev;
}

/* If a vertex is non-manifold (meaning it isn't surrounded by faces) find the
 * first edge such that repeatedly calling edge->next->pair will get you all
 * edges associated with the vertex. */
edge *edge::rewind() const {
	if (pair == NULL) return (edge *)this;
	edge *e = pair->previous();
	while (e != this && e->pair != NULL)
		e = e->pair->previous();
	return e;
}

Vector3 edge::as_vector() const {
	return vert->loc - previous()->vert->loc;
}

Vector3 edge::midpoint() const {
	return vert->loc - 0.5 * as_vector();
}

float edge::angle_between(const edge &other) const {
	Vector3 e1 = as_vector(), e2 = other.as_vector();
	return e1.cross(e2).length();
}

face::face() {
	normal.zero();
	e = NULL;
	id = 0;
}

face::face(const face &other) {
	normal = other.normal;
	id = other.id;
	e = other.e;
}

int face::sides() const {
	int sides = 0;
	edge *e0 = e;
	do {
		sides++;
		e0 = e0->next;
	} while (e0 != e);
	return sides;
}

float face::area() const {
	float area = 0;
	edge *e0 = e;
	Vector3 v0, v1;
	do {
		v0 = e0->vert->loc;
		v1 = e0->next->vert->loc;

		area += (v0.cross(v1)).length();

		e0 = e0->next;
	} while (e0 != e);
	return area / 2;
}

Vector3 face::centroid() const {
	Vector3 centroid;
	centroid.zero();

	edge *e0 = e;
	int n = 0;
	do {
		centroid += e0->vert->loc;
		n++;
		e0 = e0->next;
	} while (e0 != e);
	centroid /= n;

	return centroid;
}

void face::calculate_normal() {
	normal = e->as_vector().cross(e->next->as_vector());
	normal.normalize();
}

mesh::mesh() {
}

/* Deep copies with pointers are NO FUN. */
mesh::mesh(const mesh &other) {
#ifdef COPY_CHECKS
	mesh_copy();
#endif
	faces = vector<face *>(other.faces.size(), NULL);
	edges = vector<edge *>(other.edges.size(), NULL);
	verteces = vector<vertex *>(other.verteces.size(), NULL);

	for (auto vit = other.verteces.begin(); vit != other.verteces.end(); vit++) {
		vertex *v = new vertex();
		v->id = (*vit)->id;
		v->loc = (*vit)->loc;
		v->normal = (*vit)->normal;
		v->e = NULL;
		verteces[(*vit)->id - 1] = v;
	}

	for (auto fit = other.faces.begin(); fit != other.faces.end(); fit++) {
		face *newf = new face();
		newf->id = (*fit)->id;
		newf->normal = (*fit)->normal;
		newf->e = NULL;
		faces[newf->id - 1] = newf;
	}

	for (auto eit = other.edges.begin(); eit != other.edges.end(); eit++) {
		edge *newe = new edge();
		newe->id = (*eit)->id;

		newe->vert = verteces[(*eit)->vert->id - 1];
		if (newe->vert->e == NULL) newe->vert->e = newe;

		newe->f = faces[(*eit)->f->id - 1];
		edges[newe->id - 1] = newe;
	}

	for (auto eit = other.edges.begin(); eit != other.edges.end(); eit++) {
		edge *e = *eit;
		edges[e->id - 1]->next = edges[e->next->id - 1];
		if (e->pair != NULL) {
			edges[e->id - 1]->pair = edges[e->pair->id - 1];
		}
	}

	for (auto fit = other.faces.begin(); fit != other.faces.end(); fit++) {
		faces[(*fit)->id - 1]->e = edges[(*fit)->e->id - 1];
		faces[(*fit)->id - 1]->calculate_normal();
	}
}

void mesh::calculate_normals(normal_mode mode) {
	if (mode == NO_NORMALS) {
		for (auto vit = verteces.begin(); vit != verteces.end(); vit++) {
			(*vit)->normal.zero();
		}
	} else {
		for (auto vit = verteces.begin(); vit != verteces.end(); vit++) {
			(*vit)->normal.zero();
		}

		for (auto fit = faces.begin(); fit != faces.end(); fit++) {
			(*fit)->calculate_normal();
			edge *e = (*fit)->e;
			do {
				e->vert->normal += (*fit)->normal;
				e = e->next;
			} while (e != (*fit)->e);
		}

		for (auto vit = verteces.begin(); vit != verteces.end(); vit++) {
			(*vit)->normal.normalize();
		}
	}
}

bounds mesh::get_bounds() const {
	bounds b;
	b.min_x = INFINITY;
	b.min_y = INFINITY;
	b.min_z = INFINITY;
	b.max_x = -INFINITY;
	b.max_y = -INFINITY;
	b.max_z = -INFINITY;

	for (auto vit = verteces.begin(); vit != verteces.end(); vit++) {
		Vector3 loc = (*vit)->loc;
		if (loc[0] < b.min_x) b.min_x = loc[0];
		if (loc[0] > b.max_x) b.max_x = loc[0];
		if (loc[1] < b.min_y) b.min_y = loc[1];
		if (loc[1] > b.max_y) b.max_y = loc[1];
		if (loc[2] < b.min_z) b.min_z = loc[2];
		if (loc[2] > b.max_z) b.max_z = loc[2];
	}

	return b;
}

void mesh::scale_to_unit_cube() {
	bounds b = get_bounds();
	Vector3 translate(
			b.min_x - (b.min_x - b.max_x) / 2,
			b.min_y - (b.min_y - b.max_y) / 2,
			b.min_z - (b.min_z - b.max_z) / 2);
	float scale = 1. / fmax(
							   b.max_x - b.min_x, fmax(b.max_y - b.min_y, b.max_z - b.min_z));

	for (auto vit = verteces.begin(); vit != verteces.end(); vit++) {
		(*vit)->loc -= translate;
		(*vit)->loc *= scale;
	}
}

bool vector_comparitor::operator()(const Vector3 &v1, const Vector3 &v2) const {
	float x_diff = v1[0] - v2[0];
	if (x_diff < -CMP_EPSILON) {
		return true;
	} else if (x_diff > CMP_EPSILON) {
		return false;
	}

	float y_diff = v1[1] - v2[1];
	if (y_diff < -CMP_EPSILON) {
		return true;
	} else if (y_diff > CMP_EPSILON) {
		return false;
	}

	float z_diff = v1[2] - v2[2];
	if (z_diff < -CMP_EPSILON) {
		return true;
	} else if (z_diff > CMP_EPSILON) {
		return false;
	}

	return false;
}

void generateVertexData(mesh &mesh) {
	for (int i = 0; i < mesh.verteces.size(); i++) {
		mesh.verteces[i]->edgePoints.clear();
		mesh.verteces[i]->facePoints.clear();
	}

	int edgeID = 0;
	int currentEdgeID = 0;
	int numOfVerteces = 0;
	Vector3 vertPositions;

	for (int i = 0; i < mesh.faces.size(); i++) {
		vertPositions = Vector3(0, 0, 0);
		numOfVerteces = 1;
		edgeID = mesh.faces[i]->e->id;
		vertPositions += mesh.edges[edgeID - 1]->vert->loc;
		currentEdgeID = mesh.faces[i]->e->next->id;

		while (currentEdgeID != edgeID) {
			vertPositions += mesh.edges[currentEdgeID - 1]->vert->loc;
			numOfVerteces++;
			currentEdgeID = mesh.edges[currentEdgeID - 1]->next->id;
		}

		vertPositions /= numOfVerteces;

		edgeID = mesh.faces[i]->e->id;
		mesh.verteces[mesh.edges[edgeID - 1]->vert->id - 1]->addEdgePoint(mesh.edges[edgeID - 1]->next->vert->loc);
		mesh.verteces[mesh.edges[edgeID - 1]->vert->id - 1]->addEdgePoint(mesh.edges[edgeID - 1]->previous()->vert->loc);
		mesh.verteces[mesh.edges[edgeID - 1]->vert->id - 1]->addFacePoint(vertPositions);
		currentEdgeID = mesh.edges[edgeID - 1]->next->id;

		while (currentEdgeID != edgeID)
		{
			mesh.verteces[mesh.edges[currentEdgeID - 1]->vert->id - 1]->addEdgePoint(mesh.edges[currentEdgeID - 1]->next->vert->loc);
			mesh.verteces[mesh.edges[currentEdgeID - 1]->vert->id - 1]->addEdgePoint(mesh.edges[currentEdgeID - 1]->previous()->vert->loc);
			mesh.verteces[mesh.edges[currentEdgeID - 1]->vert->id - 1]->addFacePoint(vertPositions);
			currentEdgeID = mesh.edges[currentEdgeID - 1]->next->id;
		}
	}
}

void mesh::subdivide(int faceIndex) {
	edge currentEdge;
	bool canReplicate = false;
	int vertID;
	int edgeToBeModifiedID;

	faces[faceIndex]->newEdges.clear();
	faces[faceIndex]->originalVerteces.clear();
	faces[faceIndex]->newVerteces.clear();
	faces[faceIndex]->originalEdges.clear();

	for (int i = 0; i < verteces.size(); i++)
	{
		faces[faceIndex]->originalVerteces.push_back(verteces[i]->id - 1);
	}

	// Add new verts
	currentEdge = *faces[faceIndex]->e;
	edgeToBeModifiedID = currentEdge.id - 1;
	faces[faceIndex]->originalEdges.push_back(edgeToBeModifiedID);

	for (int i = 0; i < verteces.size(); i++)
	{
		if (verteces[i]->loc == edges[edgeToBeModifiedID]->midpoint())
		{
			i = vertID;
			canReplicate = true;
		}
	}

	if (!canReplicate)
	{
		verteces.push_back(new vertex());
		verteces[verteces.size() - 1]->id = verteces.size();
		verteces[verteces.size() - 1]->loc = edges[edgeToBeModifiedID]->midpoint();
		vertID = verteces.size() - 1;
	}
	canReplicate = false;

	faces[faceIndex]->newVerteces.push_back(vertID);

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	faces[faceIndex]->newEdges.push_back(edges.size() - 1);
	edges[faces[faceIndex]->newEdges[0]]->next = edges[edgeToBeModifiedID]->next;
	edges[edgeToBeModifiedID]->next = edges[faces[faceIndex]->newEdges[0]];
	edges[faces[faceIndex]->newEdges[0]]->vert = edges[edgeToBeModifiedID]->vert;
	controlPoints.push_back(edges[edgeToBeModifiedID]->vert->id - 1);
	edges[edgeToBeModifiedID]->vert = verteces[vertID];


	currentEdge = *edges[edges.size() - 1]->next;
	edgeToBeModifiedID = currentEdge.id - 1;
	faces[faceIndex]->originalEdges.push_back(edgeToBeModifiedID);
	for (int i = 0; i < verteces.size(); i++) {
		if (verteces[i]->loc == edges[edgeToBeModifiedID]->midpoint()) {
			i = vertID;
			canReplicate = true;
		}
	}

	if (!canReplicate) {
		verteces.push_back(new vertex());
		verteces[verteces.size() - 1]->id = verteces.size();
		verteces[verteces.size() - 1]->loc = edges[edgeToBeModifiedID]->midpoint();
		vertID = verteces.size() - 1;
	}
	canReplicate = false;

	faces[faceIndex]->newVerteces.push_back(vertID);

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	faces[faceIndex]->newEdges.push_back(edges.size() - 1);
	edges[faces[faceIndex]->newEdges[1]]->next = edges[edgeToBeModifiedID]->next;
	edges[edgeToBeModifiedID]->next = edges[faces[faceIndex]->newEdges[1]];
	edges[faces[faceIndex]->newEdges[1]]->vert = edges[edgeToBeModifiedID]->vert;
	controlPoints.push_back(edges[edgeToBeModifiedID]->vert->id - 1);
	edges[edgeToBeModifiedID]->vert = verteces[vertID];

	currentEdge = *edges[edges.size() - 1]->next;
	edgeToBeModifiedID = currentEdge.id - 1;
	faces[faceIndex]->originalEdges.push_back(edgeToBeModifiedID);

	for (int i = 0; i < verteces.size(); i++) {
		if (verteces[i]->loc == edges[edgeToBeModifiedID]->midpoint()) {
			i = vertID;
			canReplicate = true;
		}
	}

	if (!canReplicate) {
		verteces.push_back(new vertex());
		verteces[verteces.size() - 1]->id = verteces.size();
		verteces[verteces.size() - 1]->loc = edges[edgeToBeModifiedID]->midpoint();
		vertID = verteces.size() - 1;
	}
	canReplicate = false;

	faces[faceIndex]->newVerteces.push_back(vertID);

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	faces[faceIndex]->newEdges.push_back(edges.size() - 1);
	edges[faces[faceIndex]->newEdges[2]]->next = edges[edgeToBeModifiedID]->next;
	edges[edgeToBeModifiedID]->next = edges[faces[faceIndex]->newEdges[2]];
	edges[faces[faceIndex]->newEdges[2]]->vert = edges[edgeToBeModifiedID]->vert;
	controlPoints.push_back(edges[edgeToBeModifiedID]->vert->id - 1);
	edges[edgeToBeModifiedID]->vert = verteces[vertID];

	cout << "yo esta aqui" << endl;

	for (int i = 0; i < faces[faceIndex]->newVerteces.size(); i++)
	{
		newEdgePoints.push_back(faces[faceIndex]->newVerteces[i]);
	}
}

void mesh::changeEdgePoints()
{
	for (int i = 0; i < newEdgePoints.size(); i++)
	{
		if (verteces[newEdgePoints[i]]->facePoints.size() > 1)
		{
			verteces[newEdgePoints[i]]->loc = verteces[newEdgePoints[i]]->averageFacePoints();
		} 
	}
}

void mesh::changeControlPoints()
{
	for (int i = 0; i < controlPoints.size(); i++)
	{
		int valance = verteces[controlPoints[i]]->edgePoints.size();
		if (valance > 2)
		{
			verteces[controlPoints[i]]->loc = (verteces[controlPoints[i]]->averageFacePoints() / (valance*100)) + ((2 * verteces[controlPoints[i]]->averageEdgePoints()) / (valance*100)) + (verteces[controlPoints[i]]->loc);
		}
	}
}

Vector3 vertex::averageFacePoints()
{
	Vector3 total;
	int numOfFaces = facePoints.size();

	for (int i = 0; i < facePoints.size(); i++)
	{
		total += facePoints[i];
	}

	return total / numOfFaces;
}

Vector3 vertex::averageEdgePoints()
{
	Vector3 total;
	int numOfFaces = edgePoints.size();

	for (int i = 0; i < edgePoints.size(); i++) {
		total += edgePoints[i];
	}

	return total / numOfFaces;
}

void mesh::reconnectFaces(int faceIndex)
{
	vector<int> innerFaceVerteces;

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[2]];
	edges[edges.size() - 1]->next = edges[faces[faceIndex]->newEdges[2]];
	edges[faces[faceIndex]->originalEdges[0]]->next = edges[edges.size() - 1];

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[0]];
	edges[edges.size() - 1]->next = edges[faces[faceIndex]->newEdges[0]];
	edges[faces[faceIndex]->originalEdges[1]]->next = edges[edges.size() - 1];

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->next = edges[faces[faceIndex]->newEdges[1]];
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[1]];
	edges[faces[faceIndex]->originalEdges[2]]->next = edges[edges.size() - 1];

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[0]];
	innerFaceVerteces.push_back(edges.size() - 1);

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[1]];
	innerFaceVerteces.push_back(edges.size() - 1);

	edges.push_back(new edge());
	edges[edges.size() - 1]->id = edges.size();
	edges[edges.size() - 1]->vert = verteces[faces[faceIndex]->newVerteces[2]];
	innerFaceVerteces.push_back(edges.size() - 1);

	edges[innerFaceVerteces[0]]->next = edges[innerFaceVerteces[1]];
	edges[innerFaceVerteces[1]]->next = edges[innerFaceVerteces[2]];
	edges[innerFaceVerteces[2]]->next = edges[innerFaceVerteces[0]];

	vector<int> finalEdges = faces[faceIndex]->originalEdges;

	// remove current face
	faces.erase(faces.begin() + faceIndex);

	faces.push_back(new face());
	faces[faces.size() - 1]->id = faces.size();
	faces[faces.size() - 1]->e = edges[finalEdges[0]];

	faces.push_back(new face());
	faces[faces.size() - 1]->id = faces.size();
	faces[faces.size() - 1]->e = edges[finalEdges[1]];

	faces.push_back(new face());
	faces[faces.size() - 1]->id = faces.size();
	faces[faces.size() - 1]->e = edges[finalEdges[2]];

	faces.push_back(new face());
	faces[faces.size() - 1]->id = faces.size();
	faces[faces.size() - 1]->e = edges[innerFaceVerteces[0]];
}

} // namespace meshparse
