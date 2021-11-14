#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:

	ModuleEnemy();

	// Destructor
	virtual ~ModuleEnemy();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void DebugDraw();

	
	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

	struct MeleEnemicSpawn {

		int x = 0,
			y = 0;

	};
	MeleEnemicSpawn meleEnemicSpawn1;
	MeleEnemicSpawn meleEnemicSpawn2;
	MeleEnemicSpawn meleEnemicSpawn3;
	MeleEnemicSpawn meleEnemicSpawn4;
	MeleEnemicSpawn meleEnemicSpawn5;
	MeleEnemicSpawn meleEnemicSpawn6;
	MeleEnemicSpawn meleEnemicSpawn7;
	bool loadMeleEnemicSpawn = true;

	SDL_Rect test;

private:
};


#endif // __MODULE_ENEMY_H__