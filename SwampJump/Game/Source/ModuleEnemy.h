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
	float x = 0, y = 0;
	float vx, vy;
	float w, h;
	float hp;
	float damage;


	int spawnPlace;//Del 1 - 7 segun los diferentes puntos de spawn
	int enemicType;//0 para enemigos mele  1 para enemigos voladores
	
	bool atack = false;
	bool enemicFlySensor = false;//False tiene el path predeterminado True tiene el path de seguimiento
	bool movimentMeleEnemic = false;//False esquerra True dreta
	bool movimentFlyEnemic = false;//False esquerra True dreta
	bool enemicMeleSensor = false;//False tiene el path predeterminado True tiene el path de seguimiento
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
	bool LoadEnemicsData(pugi::xml_node&);

	//MeleEnemic* LoadEnemicsData(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;


	//Enemic Move
	

	float angle = 45;

	
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
	
	//Carga general de datos de enemigos
	float flyEnemicsHp;
	float meleEnemicsHp;
	float meleEnemicsDamage;
	float flyEnemicsDamage;
	struct MeleEnemicVelocity {
		float x, y;
	}meleEnemicsVelocity;
	struct FlyEnemicVelocity {
		float x, y;
	}flyEnemicsVelocity;
	struct NormalEnemicsWH {
		float w, h;
	}normalEnemicsWH;
	
	float bossEnemicDamage;
	float bossEnemicMaxHp;
	bool loadMeleEnemicSpawn = true;
	bool loadEnemicData = true;

	SDL_Rect test;
	SDL_Rect enemic;

private:
};


#endif // __MODULE_ENEMY_H__