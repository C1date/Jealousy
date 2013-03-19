#include "HitCheck.h"


HitCheck::HitCheck(TmxMap* map)
{
	if (map->getLayer("Hitboxes"))
		mapHitboxes = map->getLayer("Hitboxes")->getGameObjects();
	if (map->getLayer("Properties"))
		propertyLayer = map->getLayer("Properties")->getGameObjects();
}


HitCheck::~HitCheck(void)
{
}


// Public

// Check if a character hits to a map hitbox and return the position where to move if so
vec2 HitCheck::CheckMapHit(GameObject *character)
{
	vec2 newPos = character->getPosition();
	std::vector<int> hits;

	// Check which hitboxes you are hitting
	for(int i = 0; i < mapHitboxes.size(); i++)
	{
		if(character->collidesTo(mapHitboxes[i]))
		{
			hits.push_back(i);
		}		
	}

	 //Check where to move when hitting
	if(hits.size() == 1)
	{
		distanceToBorder(mapHitboxes[hits[0]], character, &newPos);
	}
	else
	{
		for(int i = 0; i < hits.size(); i++)
		{
			vec2 distance = mapHitboxes[hits[i]]->getPosition() - character->getPosition();
			if( distance.Length() < (character->getSizeInTiles() + mapHitboxes[hits[i]]->getSizeInTiles()).Length() / 2.2f )
				distanceToBorder(mapHitboxes[hits[i]], character, &newPos);
		}
	}

	return newPos;
}


std::string HitCheck::GetNameOfObject(GameObject *character)
{
	return GetNameOfObject(character->getPosition());
}

std::string HitCheck::GetNameOfObject(vec2 Position)
{
	for(int i = 0; i < propertyLayer.size(); i++)
	{
		float sizeX = propertyLayer[i]->getSize().x / 2;
		float sizeY = propertyLayer[i]->getSize().y / 2;
		if (Position.x < propertyLayer[i]->getPosition().x - 0.5f + sizeX &&
			Position.x > propertyLayer[i]->getPosition().x - 0.5f - sizeX &&
			Position.y < propertyLayer[i]->getPosition().y - 0.5f + sizeY &&
			Position.y > propertyLayer[i]->getPosition().y - 0.5f - sizeY)
		{
			return propertyLayer[i]->getName();
		}
	}
	return "";
}



// Private

// Sets the location where to move to the vec2 pointer
void HitCheck::distanceToBorder(GameObject *hitbox, GameObject *character, vec2 *whereToMove)
{
	vec2 difference = hitbox->getPosition() - character->getPosition();

	// Coming from
	// Left
	if(difference.x > abs(difference.y))
	{
		whereToMove->x = hitbox->getPosition().x - hitbox->getSizeInTiles().x / 2 - character->getSizeInTiles().x / 2;
	}
	// Right
	else if(difference.x < -abs(difference.y))
	{
		whereToMove->x = hitbox->getPosition().x + hitbox->getSizeInTiles().x / 2 + character->getSizeInTiles().x / 2;
	}

	// Down
	else if(difference.y < -abs(difference.x))
	{
		whereToMove->y = hitbox->getPosition().y + hitbox->getSizeInTiles().y / 2 + character->getSizeInTiles().y / 2;
	}
	// Up
	else if(difference.y > abs(difference.x))
	{
		whereToMove->y = hitbox->getPosition().y - hitbox->getSizeInTiles().y / 2 - character->getSizeInTiles().y / 2;
	}
}