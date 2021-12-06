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
	meleEnemyTexture = nullptr; //afegir sprite
	flyingEnemyTexture = app->tex->Load("Assets/textures/bee_spritesheet.png");

	//falta carregar
	flyingEnemy_IdleRAnim.Empty();

	flyingEnemy_IdleLAnim.Empty();
	flyingEnemy_IdleLAnim.PushBack({ 1, 0, 25, 27 });
	flyingEnemy_IdleLAnim.PushBack({ 26, 0, 24, 27 });
	flyingEnemy_IdleLAnim.PushBack({ 51, 0, 25, 28 });
	flyingEnemy_IdleLAnim.PushBack({ 76, 0, 24, 28 });
	flyingEnemy_IdleLAnim.loop = true;
	flyingEnemy_IdleLAnim.pingpong = true;
	flyingEnemy_IdleLAnim.speed = 1.0f;

	//falta carregar
	flyingEnemy_AttackRAnim.Empty();

	flyingEnemy_AttackLAnim.Empty();
	flyingEnemy_AttackLAnim.PushBack({ 1, 63, 26, 27 });
	flyingEnemy_AttackLAnim.PushBack({ 27, 63, 25, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 53, 63, 24, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 79, 63, 24, 30 });
	flyingEnemy_AttackLAnim.PushBack({ 105, 63, 25, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 131, 63, 25, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 157, 63, 25, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 184, 63, 25, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 209, 63, 24, 30 });
	flyingEnemy_AttackLAnim.PushBack({ 235, 63, 24, 29 });
	flyingEnemy_AttackLAnim.PushBack({ 261, 63, 25, 28 });
	flyingEnemy_AttackLAnim.PushBack({ 287, 63, 25, 27 });
	flyingEnemy_AttackLAnim.loop = true;
	flyingEnemy_AttackLAnim.speed = 1.0f;


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
	p2List_item<MeleEnemic*>* storage1 = meleEnemic1List.getFirst();//No solo es de enemigos mele es de todos los tipos
	angle += 0.01f;
	if (angle >= 360)angle = 0.01f;
	//SDL_Rect sensorSpawn1 = { app->moduleEnemy->meleEnemicSpawn1.x - 800,app->moduleEnemy->meleEnemicSpawn1.y - 500, 1500,1000 };

	while (storage1 != NULL) {
		


		//Mele Enemic Move
		if (storage1->data->enemicType == 0) {
			//meleEnemicMove(storage1, dt);

			SDL_Rect enemicMeleSensorRec = { storage1->data->x - 250,storage1->data->y - 130,500,300 };

			SDL_Rect atackMeleEnemicSensor = { storage1->data->x - 25,storage1->data->y-25,storage1->data->w + 50,storage1->data->h+50 };
			SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 10,25,25 };
			SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 10,25,25 };

			if (!storage1->data->enemicMeleSensor) {
				//Path predeterminado
				if (!storage1->data->movimentMeleEnemic) {
					storage1->data->x-=storage1->data->vx*dt;
				}
				else if (storage1->data->movimentMeleEnemic) {
					storage1->data->x+=storage1->data->vx*dt;
				}
			}
			if (storage1->data->enemicMeleSensor) {
				//Path de seguimiento
				LOG("Dentro de range de ataque!");

				
				storage1->data->atackTimer = storage1->data->atackTimer + (1 * dt);
				if (storage1->data->atackTimer >= 50) {
					//Ataque
					if (app->scene->player.x > (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w / 2)
						&& (app->scene->player.x) < (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w)
						&& app->scene->player.y > atackMeleEnemicSensor.y
						&& (app->scene->player.y + app->scene->player.h) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
						storage1->data->meleRightAtackBool = true;
						SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 10,25,25 };

						if ((meleRightAtackRect.x + meleRightAtackRect.w) > app->scene->player.x
							&& (meleRightAtackRect.x + meleRightAtackRect.w) < (app->scene->player.x + app->scene->player.w)
							&& meleRightAtackRect.y > app->scene->player.y
							&& meleRightAtackRect.y < (app->scene->player.y + app->scene->player.h)) {


							app->scene->player.actualPlayerHp -= storage1->data->damage;
							storage1->data->atackTime = 0;
							storage1->data->atackTimer = 0;
							storage1->data->meleRightAtackBool = false;

						}
						LOG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");


					}
					else {
						storage1->data->meleRightAtackBool = false;

					}
					if ((app->scene->player.x + app->scene->player.w) > atackMeleEnemicSensor.x
						&& (app->scene->player.x + app->scene->player.w) < (atackMeleEnemicSensor.x + (atackMeleEnemicSensor.w / 2))
						&& app->scene->player.y > atackMeleEnemicSensor.y
						&& (app->scene->player.y + app->scene->player.h) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
						storage1->data->meleLeftAtackBool = true;
						SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 10,25,25 };

						LOG("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");

						if ((meleLeftAtackRect.x) > app->scene->player.x
							&& (meleLeftAtackRect.x) < (app->scene->player.x + app->scene->player.w)
							&& meleLeftAtackRect.y > app->scene->player.y
							&& meleLeftAtackRect.y < (app->scene->player.y + app->scene->player.h)) {


							storage1->data->meleRightAtackBool = false;
							app->scene->player.actualPlayerHp -= storage1->data->damage;
							storage1->data->atackTime = 0;
							storage1->data->atackTimer = 0;
						}
					}
					else {
						storage1->data->meleLeftAtackBool = false;
					}
					storage1->data->atackTime = storage1->data->atackTime + (1 * dt);
					if (storage1->data->atackTime>=5) {
						storage1->data->atackTimer = 0;
						storage1->data->atackTime = 0;
					}
				}

			








				//storage1->data->x++;
			}
			


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
			if (!storage1->data->enemicFlySensor) {

				storage1->data->y = (400 + sin((angle)) * 60);//Falta poner el dt
				//Path predeterminado
				if (!storage1->data->movimentFlyEnemic) {
					storage1->data->x -= storage1->data->vx*dt;

				}
				else if (storage1->data->movimentFlyEnemic) {
					storage1->data->x += storage1->data->vx*dt;

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

				storage1->data->x+=2*dt;
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

				//Segun la vida del enemigo se hacen 2 cosas. 
				// EN el if se elimina el enemigo de la lista en caso de que no tenga vida.
				//En el else if le baja la vida segun el daño que haga la rana.
				if (storage1->data->actualHp <= 0) {

					MeleEnemic* b = storage1->data;
					storage1 = storage1->next;
					app->moduleEnemy->meleEnemic1List.del(app->moduleEnemy->meleEnemic1List.findNode(b));
					delete b;
					LOG("Enemigo muerto!");
				}
				else if (storage1->data->actualHp>0) {
					storage1->data->actualHp -= app->scene->player.playerDamage;
				}
			}
		}

		if (storage1 != NULL) {
			storage1 = storage1->next;

		}
	}

	flyingEnemy_AttackLAnim.Update();
	flyingEnemy_AttackRAnim.Update();
	flyingEnemy_IdleLAnim.Update();
	flyingEnemy_IdleRAnim.Update();

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
	meleEnemicsDamage = enemicsData.attribute("meleEnemicDamage").as_float();
	flyEnemicsDamage = enemicsData.attribute("flyEnemicDamage").as_float();
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
	newEnemy->w = normalEnemicsWH.w;
	newEnemy->h = normalEnemicsWH.h;
	newEnemy->hp = meleEnemicsHp;
	newEnemy->spawnPlace = spawnPlace;
	newEnemy->damage = meleEnemicsDamage;
	newEnemy->vx = meleEnemicsVelocity.x;
	newEnemy->vy = meleEnemicsVelocity.y;
	newEnemy->enemicType = 0;
	newEnemy->actualHp = meleEnemicsHp;



	return newEnemy;
}
MeleEnemic* ModuleEnemy::flyEnemicCreator(int x, int y,int spawnPlace) {

	MeleEnemic* newEnemy = new MeleEnemic();

	newEnemy->x = x;
	newEnemy->y = y;
	newEnemy->w = normalEnemicsWH.w;
	newEnemy->h = normalEnemicsWH.h;
	newEnemy->spawnPlace = spawnPlace;
	newEnemy->hp = flyEnemicsHp;
	newEnemy->damage = flyEnemicsDamage;
	newEnemy->vx = flyEnemicsVelocity.x;
	newEnemy->vy = flyEnemicsVelocity.y;
	newEnemy->actualHp = flyEnemicsHp;
	newEnemy->enemicType = 1;

	return newEnemy;
}

void ModuleEnemy::meleEnemicMove(p2List_item<MeleEnemic*>* meleEnemic, float dt) {

	/*if (meleEnemic->data->aceleration_timer <= 0) {
		meleEnemic->data->vy += meleEnemic->data->ay;
		meleEnemic->data->aceleration_timer = 10;
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) { //Aguantar el salt
			aceleration_timer = 25;
		}
	}
	else {
		meleEnemic->data->aceleration_timer -= 1 * dt;
	}

	if (meleEnemic->data->vy == 0) {
		meleEnemic->data->vy = 1;
	}*/

	//Salt
	/*if (tocant_terra) { //Si estic al terra
		doblesalt = false;
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			player.vy = -4;
			doblesalt = true;
		}
	}
	else {			//NO toco terra
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && (doblesalt || coyotejump)) {
			player.vy = -4;
			doblesalt = false;
			coyotejump = false;
			jumpRAnim.Reset();
			jumpLAnim.Reset();
		}
	}
	if (tocant_terra_abans && tocant_terra)
		coyotejump = true;*/

	//tocant_terra_abans = tocant_terra;
	//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS
		//COLISIONS
	//abans de res colision coords
	meleEnemic->data->vy = meleEnemic->data->ay;
 	meleEnemic->data->y += meleEnemic->data->vy;
	app->map->Getcolision_coords(meleEnemic->data->x,meleEnemic->data->y);

	for (int i = 0; app->map->colision_coords[i] != nullptr; ++i) {
		if ((meleEnemic->data->x + (meleEnemic->data->w - 4) + meleEnemic->data->vy > app->map->colision_coords[i]->x) && (meleEnemic->data->x + meleEnemic->data->vx < (app->map->colision_coords[i]->x + 32)) &&
			(meleEnemic->data->y + meleEnemic->data->h + meleEnemic->data->vy > app->map->colision_coords[i]->y) && (meleEnemic->data->y + meleEnemic->data->vy < app->map->colision_coords[i]->y + 32)) {

			//El player està colisionant amb una o més tiles
			if ((meleEnemic->data->x + (meleEnemic->data->w - 4) + meleEnemic->data->vx > app->map->colision_coords[i]->x) && (meleEnemic->data->x + meleEnemic->data->vx < (app->map->colision_coords[i]->x + 32) / 2) &&
				(meleEnemic->data->y + meleEnemic->data->h > app->map->colision_coords[i]->y - 1) && (meleEnemic->data->y < app->map->colision_coords[i]->y + 32 + 1)) {
				//Xoca pel costat
				meleEnemic->data->vx = 0;
			}
			else if ((meleEnemic->data->x + meleEnemic->data->vx > (app->map->colision_coords[i]->x + 32) / 2) && (meleEnemic->data->x + meleEnemic->data->vx < (app->map->colision_coords[i]->x + 32)) &&
				(meleEnemic->data->y + meleEnemic->data->h > app->map->colision_coords[i]->y + 1) && (meleEnemic->data->y < app->map->colision_coords[i]->y + 32 - 1)) {
				meleEnemic->data->vx = 0;

			}

			if ((meleEnemic->data->x + (meleEnemic->data->w - 4) > app->map->colision_coords[i]->x) && (meleEnemic->data->x < app->map->colision_coords[i]->x + 32) &&
				(meleEnemic->data->y + meleEnemic->data->h + meleEnemic->data->vy > app->map->colision_coords[i]->y) && (meleEnemic->data->y + meleEnemic->data->vy < app->map->colision_coords[i]->y + 32)) {
				//xoc vertical
				if (meleEnemic->data->vy >= 0) { //xoca amb el terra
					//tocant_terra = true;
				}
				meleEnemic->data->vy = 0;
			}
		}
	}
	//												COLISIONS COLISIONS
	//												COLISIONS COLISIONS

	//MOVIMENT
	/*meleEnemic->data->x += meleEnemic->data->vx;
	meleEnemic->data->y += meleEnemic->data->vy;
	meleEnemic->data->vx = 0;*/

}





