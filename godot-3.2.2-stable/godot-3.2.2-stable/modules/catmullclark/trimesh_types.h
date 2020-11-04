#ifndef __trimesh_types_h__
#define __trimesh_types_h__

#include <vector>
#include <iostream>
using namespace std;

    typedef long index_t;

	struct vertex
	{
		float x;
		float y;

		vertex()
		{
			x = 0;
			y = 0;
		}

		vertex(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		vertex average(vertex a, vertex b)
		{
			float newX = (a.x + b.x) / 2;
			float newY = (a.y + b.y) / 2;
			return vertex(newX, newY);
		}

		inline vertex operator=(vertex a)
		{
			x = a.x;
			y = a.y;
			return a;
		}

		inline bool operator==(vertex a)
		{
			return x == a.x && y == a.y;
		}
	};

    struct edge_t
    {
        index_t v[2];
        
        index_t& start() { return v[0]; }
        const index_t& start() const { return v[0]; }
        
        index_t& end() { return v[1]; }
        const index_t& end() const { return v[1]; }
        
        edge_t()
        {
            v[0] = v[1] = -1;
        }
    };
    
    struct triangle_t
    {
        index_t v[3];
		vector<vertex> positions;
        
        index_t& i() { return v[0]; }
        const index_t& i() const { return v[0]; }
        
        index_t& j() { return v[1]; }
        const index_t& j() const { return v[1]; }
        
        index_t& k() { return v[2]; }
        const index_t& k() const { return v[2]; }
        
        triangle_t()
        {
            v[0] = v[1] = v[2] = -1;
			positions.push_back(vertex());
			positions.push_back(vertex());
			positions.push_back(vertex());
        }
    };

#endif /* __trimesh_types_h__ */
