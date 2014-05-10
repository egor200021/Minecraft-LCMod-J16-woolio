#ifndef BASEITEM_H
#define BASEITEM_H

#include <Aurora/Graphics/Vertex.h>

using namespace Aurora::Graphics;

typedef unsigned short item_t;

class BaseItem
{
public:
	//texture info
	int textureRow;
	float plane;
	//vertices to show in bar or in hand
	CraftPSPVertex *vertices;

	BaseItem();
	virtual ~BaseItem();

	static item_t getBaseID();

};

#endif
