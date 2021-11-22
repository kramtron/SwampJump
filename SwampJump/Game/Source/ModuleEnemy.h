#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"
#include "p2List.h"

struct SDL_Texture;
class MeleEnemic {
public:
	MeleEnemic();
	virtual ~MeleEnemic();
public:
	int x = 0, y = 0;

	int spawnPlace;//Del 1 - 7 segun los diferentes puntos de spawn
	int enemicType;//0 para enemigos mele  1 para enemigos voladores
	
};
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

	
	bool LoadMeleEnemicSpawn(pugi::xml_node&);
	bool LoadFlyEnemicSpawn(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;



	
	p2List<MeleEnemic*>meleEnemic1List;

	MeleEnemic* meleEnemicCreator(int x, int y,int spawnPlace);
	MeleEnemic* flyEnemicCreator(int x, int y,int spawnPlace);

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

	struct FlyEnemicSpawn {

		int x = 0,
			y = 0;

	};
	FlyEnemicSpawn flyEnemicSpawn1;
	FlyEnemicSpawn flyEnemicSpawn2;
	FlyEnemicSpawn flyEnemicSpawn3;
	FlyEnemicSpawn flyEnemicSpawn4;
	
	bool loadMeleEnemicSpawn = true;
	bool loadFlyEnemicSpawn = true;

	SDL_Rect test;


private:
};


#endif // __MODULE_ENEMY_H__