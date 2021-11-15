#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "ModuleEnemy.h"
#include "Map.h"
#include "p2List.h"

#include "Defs.h"
#include "Log.h"

ModuleEnemy::ModuleEnemy() : Module()
{
	name.Create("ModuleEnemy");
}

// Destructor
ModuleEnemy::~ModuleEnemy()
{}

// Called before render is available
bool ModuleEnemy::Awake()
{
	LOG("Loading Logo");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ModuleEnemy::Start()
{
	
	return true;
}

// Called each loop iteration
bool ModuleEnemy::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ModuleEnemy::Update(float dt)
{

	bool ret = true;
	meleEnemicList.add(meleEnemicCreator(meleEnemicSpawn1.x,meleEnemicSpawn1.y));
	//meleEnemicList.getFirst()->data->x += 1;
	
	return ret;
}

// Called each loop iteration
bool ModuleEnemy::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool ModuleEnemy::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void ModuleEnemy::DebugDraw()
{

}

bool ModuleEnemy::LoadMeleEnemicSpawn(pugi::xml_node& configMeleEnemicSpawn) {

	//Asigna las cordenadas de los spawns de enemigos Mele
	meleEnemicSpawn1.x = configMeleEnemicSpawn.child("spawnPosition1").attribute("x").as_int();
	meleEnemicSpawn1.y = configMeleEnemicSpawn.child("spawnPosition1").attribute("y").as_int();
	meleEnemicSpawn2.x = configMeleEnemicSpawn.child("spawnPosition2").attribute("x").as_int();
	meleEnemicSpawn2.y = configMeleEnemicSpawn.child("spawnPosition2").attribute("y").as_int();
	meleEnemicSpawn3.x = configMeleEnemicSpawn.child("spawnPosition3").attribute("x").as_int();
	meleEnemicSpawn3.y = configMeleEnemicSpawn.child("spawnPosition3").attribute("y").as_int();
	meleEnemicSpawn4.x = configMeleEnemicSpawn.child("spawnPosition4").attribute("x").as_int();
	meleEnemicSpawn4.y = configMeleEnemicSpawn.child("spawnPosition4").attribute("y").as_int();
	meleEnemicSpawn5.x = configMeleEnemicSpawn.child("spawnPosition5").attribute("x").as_int();
	meleEnemicSpawn5.y = configMeleEnemicSpawn.child("spawnPosition5").attribute("y").as_int();
	meleEnemicSpawn6.x = configMeleEnemicSpawn.child("spawnPosition6").attribute("x").as_int();
	meleEnemicSpawn6.y = configMeleEnemicSpawn.child("spawnPosition6").attribute("y").as_int();
	meleEnemicSpawn7.x = configMeleEnemicSpawn.child("spawnPosition7").attribute("x").as_int();
	meleEnemicSpawn7.y = configMeleEnemicSpawn.child("spawnPosition7").attribute("y").as_int();

	return true;
}
bool ModuleEnemy::LoadFlyEnemicSpawn(pugi::xml_node& configFlyEnemicSpawn) {

	//Asigna las cordenadas de los spawns de enemigos Voladores
	flyEnemicSpawn1.x = configFlyEnemicSpawn.child("spawnPosition1").attribute("x").as_int();
	flyEnemicSpawn1.y = configFlyEnemicSpawn.child("spawnPosition1").attribute("y").as_int();
	flyEnemicSpawn2.x = configFlyEnemicSpawn.child("spawnPosition2").attribute("x").as_int();
	flyEnemicSpawn2.y = configFlyEnemicSpawn.child("spawnPosition2").attribute("y").as_int();
	flyEnemicSpawn3.x = configFlyEnemicSpawn.child("spawnPosition3").attribute("x").as_int();
	flyEnemicSpawn3.y = configFlyEnemicSpawn.child("spawnPosition3").attribute("y").as_int();
	flyEnemicSpawn4.x = configFlyEnemicSpawn.child("spawnPosition4").attribute("x").as_int();
	flyEnemicSpawn4.y = configFlyEnemicSpawn.child("spawnPosition4").attribute("y").as_int();

	return true;
}
bool ModuleEnemy::SaveState(pugi::xml_node& configEnemicSpawn) const {


	return true;
}


MeleEnemic* ModuleEnemy::meleEnemicCreator(int x, int y) {
	
	MeleEnemic* newEnemy = new MeleEnemic();

	newEnemy->x = x;
	newEnemy->y = y;

	return newEnemy;
}
