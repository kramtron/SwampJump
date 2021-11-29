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
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

ModuleEnemy::ModuleEnemy() : Module()
{
	name.Create("ModuleEnemy");
}

// Destructor
ModuleEnemy::~ModuleEnemy()
{}

MeleEnemic::MeleEnemic() {

}
MeleEnemic::~MeleEnemic() {

}
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
	
	//Lista enemigos 
	p2List_item<MeleEnemic*>* storage1 = meleEnemic1List.getFirst();
	angle += 0.01f;
	if (angle >= 360)angle = 0.01f;
	//SDL_Rect sensorSpawn1 = { app->moduleEnemy->meleEnemicSpawn1.x - 800,app->moduleEnemy->meleEnemicSpawn1.y - 500, 1500,1000 };

	while (storage1 != NULL) {

		storage1->data->w = normalEnemicsWH.w;
		storage1->data->h = normalEnemicsWH.h;

		//Mele Enemic Move
		if (storage1->data->enemicType == 0) {
			storage1->data->hp = meleEnemicsHp;
			storage1->data->damage = meleEnemicsDamage;
			storage1->data->vx = meleEnemicsVelocity.x;
			storage1->data->vy = meleEnemicsVelocity.y;
		
			if (!storage1->data->enemicMeleSensor) {
				//Path predeterminado
				if (!storage1->data->movimentMeleEnemic) {
					storage1->data->x-=storage1->data->vx;
				}
				else if (storage1->data->movimentMeleEnemic) {
					storage1->data->x+=storage1->data->vx;
				}
			}
			if (storage1->data->enemicMeleSensor) {
				//Path de seguimiento
				LOG("Dentro de range de ataque!");
				//storage1->data->x++;
			}
			SDL_Rect enemicMeleSensorRec = { storage1->data->x - 250,storage1->data->y - 130,500,300 };
			SDL_Rect atackMeleEnemicSensor = { storage1->data->x - 25,storage1->data->y - 25,storage1->data->w + 25,storage1->data->h + 25 };


			if (app->scene->player.x > enemicMeleSensorRec.x && app->scene->player.x < enemicMeleSensorRec.w + enemicMeleSensorRec.x && 
				app->scene->player.y<enemicMeleSensorRec.h + enemicMeleSensorRec.y && app->scene->player.y>enemicMeleSensorRec.y) 
			
			{
				storage1->data->enemicMeleSensor = true;

			}
			else {
				storage1->data->enemicMeleSensor = false;
			}
			if (storage1->data->atack) {

			}
		}
		//Fly enemic Move
		if (storage1->data->enemicType == 1) {

			storage1->data->hp = flyEnemicsHp;
			storage1->data->damage = flyEnemicsDamage;
			storage1->data->vx = flyEnemicsVelocity.x;
			storage1->data->vy = flyEnemicsVelocity.y;
			

			if (!storage1->data->enemicFlySensor) {

				storage1->data->y = 400 + sin(angle) * 60;
				//Path predeterminado
				if (!storage1->data->movimentFlyEnemic) {
					storage1->data->x -= 1;

				}
				else if (storage1->data->movimentFlyEnemic) {
					storage1->data->x += 1;

				}
				/*if (storage1->data->x < 2850) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 3354) {
					storage1->data->movimentFlyEnemic = false;
				}*/
			}
			if (storage1->data->enemicFlySensor) {
				//Path de seguimiento

				storage1->data->x++;
			}
			SDL_Rect enemicFlySensorRec = { storage1->data->x - 250,storage1->data->y - 130,500,300 };

			/*if (app->scene->player.x > enemicFlySensorRec.x && app->scene->player.x < enemicFlySensorRec.w + enemicFlySensorRec.x && app->scene->player.y<enemicFlySensorRec.h + enemicFlySensorRec.y && app->scene->player.y>enemicFlySensorRec.y) {
				storage1->data->enemicFlySensor = true;
			}*/
			//else {
				storage1->data->enemicFlySensor = false;
			//}
		}

		SDL_Rect enemic = {storage1->data->x,storage1->data->y,50,50};
		//LOG("Enemic x: %d y: %d", storage1->data->x, storage1->data->y);

		
		//Elimina los enemigos cuando el personaje entra dentro del sensor enemicSensor
		if (app->scene->boolDisparo) {
			if (app->scene->disparoPlayer.x > enemic.x && app->scene->disparoPlayer.x < enemic.w + enemic.x && app->scene->disparoPlayer.y<enemic.h + enemic.y && app->scene->disparoPlayer.y>enemic.y) {
				app->scene->disparoRetroceso = false;
				MeleEnemic* b = storage1->data;
				storage1 = storage1->next;
				app->moduleEnemy->meleEnemic1List.del(app->moduleEnemy->meleEnemic1List.findNode(b));
				delete b;
			}
		}
		
		if (storage1 != NULL) {
			storage1 = storage1->next;

		}

	}

	
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

bool ModuleEnemy::LoadEnemicsData(pugi::xml_node& enemicsData) {
	//Toda la carga de las caracteristicas generales de los enemigos
	flyEnemicsHp = enemicsData.attribute("flyEnemicHp").as_float();
	meleEnemicsHp = enemicsData.attribute("meleEnemicHp").as_float();
	meleEnemicsDamage = enemicsData.attribute("meleEnemicsDamage").as_float();
	flyEnemicsDamage = enemicsData.attribute("flyEnemicsDamage").as_float();
	meleEnemicsVelocity.x = enemicsData.attribute("xMeleVelocity").as_float();
	meleEnemicsVelocity.y = enemicsData.attribute("yMeleVelocity").as_float();
	flyEnemicsVelocity.x = enemicsData.attribute("xFlyVelocity").as_float();
	flyEnemicsVelocity.x = enemicsData.attribute("yFlyVelocity").as_float();
	normalEnemicsWH.w = enemicsData.attribute("width").as_float();
	normalEnemicsWH.h = enemicsData.attribute("width").as_float();
	bossEnemicMaxHp = enemicsData.attribute("bossEnemicMaxHp").as_float();
	bossEnemicDamage = enemicsData.attribute("bossEnemicDamage").as_float();
	return true;
}

bool ModuleEnemy::SaveState(pugi::xml_node& configEnemicSpawn) const {


	return true;
}


MeleEnemic* ModuleEnemy::meleEnemicCreator(int x, int y,int spawnPlace) {
	
	MeleEnemic* newEnemy = new MeleEnemic();

	newEnemy->x = x;
	newEnemy->y = y;

	newEnemy->spawnPlace = spawnPlace;
	
	newEnemy->enemicType = 0;

	return newEnemy;
}
MeleEnemic* ModuleEnemy::flyEnemicCreator(int x, int y,int spawnPlace) {

	MeleEnemic* newEnemy = new MeleEnemic();

	newEnemy->x = x;
	newEnemy->y = y;

	newEnemy->spawnPlace = spawnPlace;

	newEnemy->enemicType = 1;

	return newEnemy;
}
