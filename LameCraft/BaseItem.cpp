#include "BaseItem.h"


BaseItem::BaseItem()
{
	textureRow = 0;
	plane = 0;

	vertices = NULL;
}

BaseItem::~BaseItem()
{
	if(vertices != NULL)
	{
		free(vertices);
	}
}

item_t BaseItem::getBaseID(){	return 0;}
