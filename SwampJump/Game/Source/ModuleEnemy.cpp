#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "ModuleEnemy.h"
#include "ModuleScore.h"
#include "Map.h"
#include "p2List.h"
#include "Scene.h"
#include <time.h>

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
	//randomizador
	srand(time(NULL));

	//ENEMY Spritesheets
	flyingEnemyTexture = app->tex->Load("Assets/textures/bee_spritesheet.png");
	meleEnemyTexture = app->tex->Load("Assets/textures/centipede_spritesheet.png");

	audio_hurt = app->audio->LoadFx("Assets/audio/fx/Hurt.wav");

	//FLY ENEMY ANIMATION
	//Idle Animation
	flyingEnemy_IdleRAnim.Empty();
	flyingEnemy_IdleRAnim.PushBack({ 1, 33, 24, 26 });
	flyingEnemy_IdleRAnim.PushBack({ 25, 33, 25, 26 });
	flyingEnemy_IdleRAnim.PushBack({ 51, 33, 24, 26 });
	flyingEnemy_IdleRAnim.PushBack({ 75, 33, 25, 26 });
	flyingEnemy_IdleRAnim.loop = true;
	flyingEnemy_IdleRAnim.speed = 0.05f;

	flyingEnemy_IdleLAnim.Empty();
	flyingEnemy_IdleLAnim.PushBack({ 1, 0, 25, 27 });
	flyingEnemy_IdleLAnim.PushBack({ 26, 0, 24, 27 });
	flyingEnemy_IdleLAnim.PushBack({ 51, 0, 25, 28 });
	flyingEnemy_IdleLAnim.PushBack({ 76, 0, 24, 28 });
	flyingEnemy_IdleLAnim.loop = true;
	flyingEnemy_IdleLAnim.speed = 0.05f;

	//AttackAnimation
	flyingEnemy_AttackRAnim.Empty();
	flyingEnemy_AttackRAnim.PushBack({ 2, 94, 25, 26});
	flyingEnemy_AttackRAnim.PushBack({ 28, 94, 25, 27});
	flyingEnemy_AttackRAnim.PushBack({ 55, 94, 24, 28});
	flyingEnemy_AttackRAnim.PushBack({ 81, 94, 24, 28});
	flyingEnemy_AttackRAnim.PushBack({ 105, 94, 25, 27});
	flyingEnemy_AttackRAnim.PushBack({ 132, 94, 25, 27});
	flyingEnemy_AttackRAnim.PushBack({ 158, 94, 25, 27});
	flyingEnemy_AttackRAnim.PushBack({ 184, 94, 25, 27});
	flyingEnemy_AttackRAnim.PushBack({ 211, 94, 24, 28});
	flyingEnemy_AttackRAnim.PushBack({ 237, 94, 24, 28});
	flyingEnemy_AttackRAnim.PushBack({ 262, 94, 25, 28});
	flyingEnemy_AttackRAnim.PushBack({ 288, 94, 25, 26});
	flyingEnemy_AttackRAnim.loop = true;
	flyingEnemy_AttackRAnim.speed = 0.05f;

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
	flyingEnemy_AttackLAnim.speed = 0.05f;


	//MELE ANIMATIONS
	//walk animation
	meleEnemy_WalkRAnim.Empty();
	meleEnemy_WalkRAnim.PushBack({ 216, 83, 51, 39 });
	meleEnemy_WalkRAnim.PushBack({ 144, 84, 50, 38 });
	meleEnemy_WalkRAnim.PushBack({ 72, 83, 51, 39 });
	meleEnemy_WalkRAnim.PushBack({ 0, 82, 52, 40 });
	meleEnemy_WalkRAnim.loop = true;
	meleEnemy_WalkRAnim.pingpong = true;
	meleEnemy_WalkRAnim.speed = 0.05f;

	meleEnemy_WalkLAnim.Empty();
	meleEnemy_WalkLAnim.PushBack({ 1, 3, 51 , 39 });
	meleEnemy_WalkLAnim.PushBack({ 74, 4, 50, 38 });
	meleEnemy_WalkLAnim.PushBack({ 145, 3, 51, 39 });
	meleEnemy_WalkLAnim.PushBack({ 216, 2, 52, 40 });
	meleEnemy_WalkLAnim.loop = true;
	meleEnemy_WalkLAnim.pingpong = true;
	meleEnemy_WalkLAnim.speed = 0.05f;

	//attack animation
	meleEnemy_AttackRAnim.Empty();
	meleEnemy_AttackRAnim.PushBack({ 358, 307, 49, 41 });
	meleEnemy_AttackRAnim.PushBack({ 286, 304, 46, 44 });
	meleEnemy_AttackRAnim.PushBack({ 214, 304, 46, 44 });
	meleEnemy_AttackRAnim.PushBack({ 143, 304, 66, 44 });
	meleEnemy_AttackRAnim.PushBack({ 72, 318, 69, 30 });
	meleEnemy_AttackRAnim.PushBack({ 0, 318, 69, 30 });
	meleEnemy_AttackRAnim.loop = true;
	meleEnemy_AttackRAnim.speed = 0.05f;

	meleEnemy_AttackLAnim.Empty();
	meleEnemy_AttackLAnim.PushBack({ 1, 235, 49, 41 });
	meleEnemy_AttackLAnim.PushBack({ 76, 232, 46, 44 });
	meleEnemy_AttackLAnim.PushBack({ 148, 232, 46, 44 });
	meleEnemy_AttackLAnim.PushBack({ 199, 232, 66, 44 });
	meleEnemy_AttackLAnim.PushBack({ 267, 246, 69, 30 });
	meleEnemy_AttackLAnim.PushBack({ 344, 246, 65, 30 });
	meleEnemy_AttackLAnim.loop = true;
	meleEnemy_AttackLAnim.speed = 0.05f;

	//hurt animation
	meleEnemy_HurtRAnim.Empty();
	meleEnemy_HurtRAnim.PushBack({ 72, 155, 50, 39 });
	meleEnemy_HurtRAnim.loop = false;

	meleEnemy_HurtLAnim.Empty();
	meleEnemy_HurtLAnim.PushBack({ 2, 155, 50, 39 });
	meleEnemy_HurtLAnim.loop = false;

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
	
	//Animation Speeds
	flyingEnemy_AttackLAnim.speed = 0.15f * dt;
	flyingEnemy_AttackRAnim.speed = 0.15f * dt;
	flyingEnemy_IdleLAnim.speed = 0.15f * dt;
	flyingEnemy_IdleRAnim.speed = 0.15f * dt;

	meleEnemy_WalkLAnim.speed = 0.15f * dt;
	meleEnemy_WalkRAnim.speed = 0.15f * dt;
	meleEnemy_AttackLAnim.speed = 0.15f * dt;
	meleEnemy_AttackRAnim.speed = 0.15f * dt;
	meleEnemy_HurtLAnim.speed = 0.15f * dt;
	meleEnemy_HurtRAnim.speed = 0.15f * dt;

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
					storage1->data->currentAnimation = &meleEnemy_WalkLAnim;
				}
				else if (storage1->data->movimentMeleEnemic) {
					storage1->data->x+=storage1->data->vx*dt;
					storage1->data->currentAnimation = &meleEnemy_WalkRAnim;
				}
			}
			if (!app->scene->godMode) {
				if (storage1->data->enemicMeleSensor) {
					//Path de seguimiento
					LOG("Dentro de range de ataque!");


					storage1->data->atackTimer = storage1->data->atackTimer + (1 * dt);//Timer del tiempo en el que el enemigo puede volver a atacar

					if (storage1->data->atackTimer >= 50) {
						//Ataque
						//Right
						if (app->scene->player.x > (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w / 2)//If para detectar si el jugador esta tocando el sensor de ataque del enemigo
							&& (app->scene->player.x) < (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w)
							&& app->scene->player.y > atackMeleEnemicSensor.y
							&& (app->scene->player.y + app->scene->player.h) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
							storage1->data->meleRightAtackBool = true;//Activa el bool de que el enemigo está atacando
							SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 10,25,25 };//Rect del collider del ataque del enemigo

							if ((meleRightAtackRect.x + meleRightAtackRect.w) > app->scene->player.x//If para ver si el ataque del enemigo está tocando al jugador
								&& (meleRightAtackRect.x + meleRightAtackRect.w) < (app->scene->player.x + app->scene->player.w)
								&& meleRightAtackRect.y > app->scene->player.y
								&& meleRightAtackRect.y < (app->scene->player.y + app->scene->player.h)) {
								storage1->data->currentAnimation = &meleEnemy_AttackRAnim;

								if (!app->scene->player.playerInmortal) {
									app->scene->player.actualPlayerHp -= storage1->data->damage;//Quita vida al jugador
									app->audio->PlayFx(audio_hurt);
								}
								//Resetea todos los contadores y bools del ataque del enemigo
								storage1->data->atackTime = 0;
								storage1->data->atackTimer = 0;
								storage1->data->meleRightAtackBool = false;

							}


						}
						else {//Cuando el jugador no está dentro del sensor de ataque del enemigo coloca el bool de ataque en false
							storage1->data->meleRightAtackBool = false;

						}
						//Left
						//Lo mismo que arriba pero para el lado izquierdo
						if ((app->scene->player.x + app->scene->player.w) > atackMeleEnemicSensor.x
							&& (app->scene->player.x + app->scene->player.w) < (atackMeleEnemicSensor.x + (atackMeleEnemicSensor.w / 2))
							&& app->scene->player.y > atackMeleEnemicSensor.y
							&& (app->scene->player.y + app->scene->player.h) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
							storage1->data->meleLeftAtackBool = true;
							SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 10,25,25 };


							if ((meleLeftAtackRect.x) > app->scene->player.x
								&& (meleLeftAtackRect.x) < (app->scene->player.x + app->scene->player.w)
								&& meleLeftAtackRect.y > app->scene->player.y
								&& meleLeftAtackRect.y < (app->scene->player.y + app->scene->player.h)) {

								storage1->data->currentAnimation = &meleEnemy_AttackLAnim;

								storage1->data->meleRightAtackBool = false;
								if (!app->scene->player.playerInmortal) {
									app->scene->player.actualPlayerHp -= storage1->data->damage;
									app->audio->PlayFx(audio_hurt);
								}
								storage1->data->atackTime = 0;
								storage1->data->atackTimer = 0;
							}
						}
						else {
							storage1->data->meleLeftAtackBool = false;
						}
						storage1->data->atackTime = storage1->data->atackTime + (1 * dt);
						if (storage1->data->atackTime >= 5) {
							storage1->data->atackTimer = 0;
							storage1->data->atackTime = 0;
						}
					}

					//Melee Enemy in-sensor movement
					//only move if its not attacking
					if (!storage1->data->meleRightAtackBool && storage1->data->atackTime == 0) {
						if (storage1->data->x < app->scene->player.x) {	//move right
							if (EnemyWalkability(storage1->data, true)) {	//only move if its not in the limit
								storage1->data->x += storage1->data->vx * dt;
								storage1->data->currentAnimation = &meleEnemy_WalkRAnim;
							}
						}
						else {	//move left
							if (EnemyWalkability(storage1->data, false)) {	//only move if its not in the limit
								storage1->data->x -= storage1->data->vx * dt;
								storage1->data->currentAnimation = &meleEnemy_WalkLAnim;
							}
						}
					}
					
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
		}
		//Fly enemic Move
		if (storage1->data->enemicType == 1) {
			if (!storage1->data->enemicFlySensor) {
				storage1->data->y += sin(angle);//Falta poner el dt
				//Path predeterminado
				if (!storage1->data->movimentFlyEnemic) {
					storage1->data->x -= storage1->data->vx * dt;
					storage1->data->currentAnimation = &flyingEnemy_IdleLAnim;
				}
				else if (storage1->data->movimentFlyEnemic) {
					storage1->data->x += storage1->data->vx * dt;
					storage1->data->currentAnimation = &flyingEnemy_IdleRAnim;
				}
				/*if (storage1->data->x < 2850) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 3354) {
					storage1->data->movimentFlyEnemic = false;
				}*/
			}
			if (!app->scene->godMode) {

				if (storage1->data->enemicFlySensor) {	//Pathfinding Flying Enemy

						//Path de seguimiento
						//if position reached, pathfind
					if (!storage1->data->moving) {
						iPoint mov = storage1->data->pathfind();
						storage1->data->movingTo = app->map->MapToWorld(mov.x, mov.y);
						storage1->data->moving = true;
					}
					//movement
					if (storage1->data->movingTo.x == -32 && storage1->data->movingTo.y == -32) {	//if error ocurred
						storage1->data->moving = false;
					}
					else {
						if (storage1->data->x > (storage1->data->movingTo.x + 3) ||
							storage1->data->x < (storage1->data->movingTo.x - 3)) {
							if (storage1->data->movingTo.x > storage1->data->x) {	//move right
								storage1->data->x += storage1->data->vx * dt;
								storage1->data->currentAnimation = &flyingEnemy_IdleRAnim;
							}
							else if (storage1->data->movingTo.x < storage1->data->x) {	//move left
								storage1->data->x -= storage1->data->vx * dt;
								storage1->data->currentAnimation = &flyingEnemy_IdleLAnim;
							}
						}
						else {
							storage1->data->x = storage1->data->movingTo.x;
						}

						if (storage1->data->y > (storage1->data->movingTo.y + 3) ||
							storage1->data->y < (storage1->data->movingTo.y - 3)) {	//if its close to the point, no move
							if (storage1->data->movingTo.y > storage1->data->y) {	//move down
								storage1->data->y += storage1->data->vy * dt;
							}
							else if (storage1->data->movingTo.y < storage1->data->y) {	//move up
								storage1->data->y -= storage1->data->vy * dt;
							}
						}
						else {
							storage1->data->y = storage1->data->movingTo.y;
						}
					}

					if (storage1->data->x > (storage1->data->movingTo.x - 16) &&
						storage1->data->x < (storage1->data->movingTo.x + 16) &&
						storage1->data->y >(storage1->data->movingTo.y - 16) &&
						storage1->data->y < (storage1->data->movingTo.y + 16)) {
						storage1->data->moving = false;
					}


					//FLYING ENEMY ATTACK
					SDL_Rect atackMeleEnemicSensor = { storage1->data->x - 25,storage1->data->y - 25,storage1->data->w + 50,storage1->data->h + 50 };
					SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 35,25,25 };
					SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 35,25,25 };

					storage1->data->atackTimer = storage1->data->atackTimer + (1 * dt);//Timer del tiempo en el que el enemigo puede volver a atacar

					if (storage1->data->atackTimer >= 50) {
						//Ataque
						//Right
						if (app->scene->player.x > (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w / 2)//If para detectar si el jugador esta tocando el sensor de ataque del enemigo
							&& (app->scene->player.x) < (atackMeleEnemicSensor.x + atackMeleEnemicSensor.w)
							&& app->scene->player.y > atackMeleEnemicSensor.y
							&& (app->scene->player.y) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
							storage1->data->meleRightAtackBool = true;//Activa el bool de que el enemigo está atacando
							SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 35,25,25 };

							if ((meleRightAtackRect.x + meleRightAtackRect.w) > app->scene->player.x//If para ver si el ataque del enemigo está tocando al jugador
								&& (meleRightAtackRect.x + meleRightAtackRect.w) < (app->scene->player.x + app->scene->player.w)
								&& meleRightAtackRect.y > app->scene->player.y
								&& meleRightAtackRect.y < (app->scene->player.y + app->scene->player.h)) {
								storage1->data->currentAnimation = &flyingEnemy_AttackRAnim;

								if (!app->scene->player.playerInmortal) {
									app->scene->player.actualPlayerHp -= storage1->data->damage;//Quita vida al jugador
									app->audio->PlayFx(audio_hurt);
								}
								//Resetea todos los contadores y bools del ataque del enemigo
								storage1->data->atackTime = 0;
								storage1->data->atackTimer = 0;
								storage1->data->meleRightAtackBool = false;

							}


						}
						else {//Cuando el jugador no está dentro del sensor de ataque del enemigo coloca el bool de ataque en false
							storage1->data->meleRightAtackBool = false;

						}
						//Left
						//Lo mismo que arriba pero para el lado izquierdo
						if ((app->scene->player.x + app->scene->player.w) > atackMeleEnemicSensor.x
							&& (app->scene->player.x + app->scene->player.w) < (atackMeleEnemicSensor.x + (atackMeleEnemicSensor.w / 2))
							&& app->scene->player.y > atackMeleEnemicSensor.y
							&& (app->scene->player.y) < (atackMeleEnemicSensor.y + atackMeleEnemicSensor.h)) {
							storage1->data->meleLeftAtackBool = true;
							SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 35,25,25 };


							if ((meleLeftAtackRect.x) > app->scene->player.x
								&& (meleLeftAtackRect.x) < (app->scene->player.x + app->scene->player.w)
								&& meleLeftAtackRect.y > app->scene->player.y
								&& meleLeftAtackRect.y < (app->scene->player.y + app->scene->player.h)) {

								storage1->data->currentAnimation = &flyingEnemy_AttackLAnim;

								storage1->data->meleRightAtackBool = false;
								if (!app->scene->player.playerInmortal) {
									app->scene->player.actualPlayerHp -= storage1->data->damage;
									app->audio->PlayFx(audio_hurt);
								}
								storage1->data->atackTime = 0;
								storage1->data->atackTimer = 0;
							}
						}
						else {
							storage1->data->meleLeftAtackBool = false;
						}
						storage1->data->atackTime = storage1->data->atackTime + (1 * dt);
						if (storage1->data->atackTime >= 5) {
							storage1->data->atackTimer = 0;
							storage1->data->atackTime = 0;
						}
					}
				}

				SDL_Rect enemicFlySensorRec = { storage1->data->x - 500,storage1->data->y - 250,1000,600 };

				if (app->scene->player.x > enemicFlySensorRec.x && app->scene->player.x < enemicFlySensorRec.w + enemicFlySensorRec.x && app->scene->player.y<enemicFlySensorRec.h + enemicFlySensorRec.y && app->scene->player.y>enemicFlySensorRec.y) {
					storage1->data->enemicFlySensor = true;
				}
				else {
					storage1->data->enemicFlySensor = false;
				}
			}
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

					numRand = rand() % 3;
	
					if (numRand == 2)
					{
						app->modulescore->HpCreate(storage1->data->x, storage1->data->y, app->modulescore->hpUp);
					}

					MeleEnemic* b = storage1->data;
					storage1 = storage1->next;
					app->moduleEnemy->meleEnemic1List.del(app->moduleEnemy->meleEnemic1List.findNode(b));
					delete b;
					LOG("Enemigo muerto!");
				}
				else if (storage1->data->actualHp>0) {
					storage1->data->actualHp -= app->scene->player.playerDamage;

					if (storage1->data->enemicType == 0) {
						if ((storage1->data->currentAnimation == &meleEnemy_AttackLAnim) || (storage1->data->currentAnimation == &meleEnemy_WalkLAnim)) {
							storage1->data->currentAnimation = &meleEnemy_HurtLAnim;
						}
						else {
							storage1->data->currentAnimation = &meleEnemy_HurtRAnim;
						}
					}
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

	meleEnemy_WalkLAnim.Update();
	meleEnemy_WalkRAnim.Update();
	meleEnemy_AttackLAnim.Update();
	meleEnemy_AttackRAnim.Update();
	meleEnemy_HurtLAnim.Update();
	meleEnemy_HurtRAnim.Update();

	return ret;
}

// Called each loop iteration
bool ModuleEnemy::PostUpdate()
{
	bool ret = true;

	p2List_item<MeleEnemic*>* storage1 = meleEnemic1List.getFirst();
	while (storage1 != NULL) {
		
		EnemyDraw(storage1->data);

		storage1 = storage1->next;
	}

	return ret;
}

// Called before quitting
bool ModuleEnemy::CleanUp()
{
	LOG("Freeing scene");

	while (meleEnemic1List.count() != 0) {
		meleEnemic1List.del(meleEnemic1List.getFirst());
	}

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
	flyEnemicsVelocity.y = enemicsData.attribute("yFlyVelocity").as_float();
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

	newEnemy->currentAnimation = &meleEnemy_WalkLAnim;

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

	newEnemy->currentAnimation = &flyingEnemy_IdleLAnim;

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

iPoint MeleEnemic::pathfind() {
	return app->map->Pathfinding(app->map->WorldToMap(x, y),
		   app->map->WorldToMap(app->scene->player.x, app->scene->player.y));
}

void ModuleEnemy::EnemyDraw(MeleEnemic* storage) {
	if (storage->enemicType == 0) {	//mele enemy
		app->render->DrawTexture(meleEnemyTexture, storage->x - 10, storage->y -5, &storage->currentAnimation->GetCurrentFrame(), 1.0f, 1.5f);
	}
	else {	//flying enemy
		app->render->DrawTexture(flyingEnemyTexture, storage->x, storage->y, &storage->currentAnimation->GetCurrentFrame(), 1.0f, 2.0f);
	}
}

bool ModuleEnemy::EnemyWalkability(MeleEnemic* storage, bool right) {
	if (right) {	//move right?
		switch (storage->spawnPlace) {
		case 1:
			if (storage->x < 3354)
				return true;
			break;
		case 2:
			if (storage->x < 5773)
				return true;
			break;
		case 3:
			if (storage->x < 6785)
				return true;
			break;
		case 4:
			if (storage->x < 8350)
				return true;
			break;
		case 5:
			if (storage->x < 9555)
				return true;
			break;
		case 6:
			if (storage->x < 12280)
				return true;
			break;
		case 7:
			if (storage->x < 12705)
				return true;
			break;
		}
		return false;
	}
	else {	//move left?
		switch (storage->spawnPlace) {
		case 1:
			if (storage->x > 2850)
				return true;
			break;
		case 2:
			if (storage->x > 5439)
				return true;
			break;
		case 3:
			if (storage->x > 6559)
				return true;
			break;
		case 4:
			if (storage->x > 8095)
				return true;
			break;
		case 5:
			if (storage->x > 9125)
				return true;
			break;
		case 6:
			if (storage->x > 11976)
				return true;
			break;
		case 7:
			if (storage->x > 12385)
				return true;
			break;
		}
		return false;
	}
}