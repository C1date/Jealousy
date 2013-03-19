#ifndef HITCHECK_H
#define HITCHECK_H

#include <Map.h>
#include <Layer.h>
#include <Tile.h>
#include <GameObject.h>

using namespace yam2d;

class HitCheck
{
public:
	HitCheck(TmxMap* map);
	~HitCheck(void);
	/*Returns a vector where the character should be exept of being inside hitbox*/
	vec2 CheckMapHit(GameObject *character);
	/*Returns string GameObjectName if inside gameObject, else returns ""*/
	std::string GetNameOfObject(GameObject *character);
	std::string GetNameOfObject(vec2 Position);
private:
	Layer::GameObjectList mapHitboxes;
	Layer::GameObjectList propertyLayer;
	
	void distanceToBorder(GameObject *hitbox, GameObject *character, vec2 *whereToMove);
};

#endif
