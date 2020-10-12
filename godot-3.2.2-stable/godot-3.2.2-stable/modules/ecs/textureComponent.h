#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <iostream>
#include <vector>
#include "scene/2d/node_2d.h"
#include "core/core_string_names.h"

using namespace std;

class TextureComponent {

protected:
	// Strings
	String imagePath;

	// RID's
	RID canvas;

	// Textures
	Ref<Texture> texture;
	Ref<Texture> normal_map;

	// Point2's
	Point2 offset;

	// Mutators
	void setupNewTexture();

public:
	TextureComponent() {}

	// Path functions
	void path(const String &a);

	// Texture functions
	void set_texture(const Ref<Texture> &p_texture);
	Ref<Texture> get_texture() const;

	// Rect functions
	void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect, bool &r_filter_clip, int ID) const;

	// Offset functions
	void set_offset(const Point2 &p_offset);
	Point2 get_offset() const;

	// Draw functions
	void draw(const RID &canvas, const int &ID);
};

#endif
