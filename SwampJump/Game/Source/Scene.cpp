#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Scene_END.h"
#include "Map.h"
#include "Animation.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	if(app->scene_logo->active == true)
		active = false;

	app->map->Load("Mapa1.tmx");
	//app->map->Load("iso_walk.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	
	imgFons1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/1.png");
	imgFons2 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/2.png");
	imgFons3 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/3.png");
	imgFons4 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/5.png");
	granota = app->tex->Load("Assets/textures/frog.png");

	//Sprites Decoraci�
	arbre1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Willows/3.png");
	arbre2 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Trees/3.png");
	tronc1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Ridges/1.png");
	cartell1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/1.png");
	cartell5 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/5.png");
	cartell8 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/8.png");
	bush1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/1.png");
	bush3 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/3.png");
	bush8 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/8.png");
	
	app->render->camera.x = 0;
	app->render->camera.y = -120;

	PlayerRect = { 16, 0, 16, 16 };
	PlayerRectA1 = { 0, 0, 16, 16 };
	PlayerRectA2 = { 0, 16, 16, 16 };
	PlayerRectJump = { 32, 0, 16, 16 };
	PlayerRectWalk = { 48, 0, 16, 16 };

	sentit_moviment = true;

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	//beforeCoords player
	before_camera.x = app->render->camera.x;
	before_camera.y = app->render->camera.y;

	//Te coloca en el inicio del nivel
	if (reset) {
		player.x = 400;
		player.y = 426;
		parallax1 = 0;
		parallax2 = 0;
		parallax3 = 0;
		reset = false;
	}
	//LOAD SAVE
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();
	
	if (godMode) {
		LOG("GODMODE ON");
		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			player.x += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			player.x += 5;
		}

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			player.y += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			player.y += 5;
		}

		//CAMERA
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			app->render->camera.y -= 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			app->render->camera.y += 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			app->render->camera.x -= 5;

		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			app->render->camera.x += 5;

		}

	}
	else if (!godMode) {
		LOG("GODMODE OFF");

		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
 			player.vx = -2;
			sentit_moviment = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			player.vx = 2;
			sentit_moviment = true;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			walking = true;
		}
		else {
			walking = false;
		}
		//

		//ANIMACIO TERRA
		if (!saltant && !walking) {
			if ((scene_timer < 40) || (scene_timer > 80 && scene_timer < 120)) {
				playerAnim = A1;
			}
			else if (scene_timer >= 120) {
				playerAnim = IDLE;
			}
			else {
				playerAnim = A2;
			}
		}
		else if (walking && !saltant) {
			if (scene_timer % 40 == 0) {
				if (playerAnim != WALK) {
					playerAnim = WALK;
				}
				else {
					playerAnim = IDLE;
				}
			}
		}

		//Player.vy = 0;
		if (aceleration_timer == 0) {
			player.vy += player.ay;
			aceleration_timer = 10;
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) { //Aguantar el salt
				aceleration_timer = 25;
			}
		}
		else {
			aceleration_timer--;
		}
		//player.vy += player.ay;

		//coyote jump
		if (coyotejump) {
			coyotejump = false;
			doblesalt = true;
			saltant = true;
		}

		//doble salt
		
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && doblesalt) {
			player.vy = -4;
			doblesalt = false;
			playerAnim = WALK;
			timer_salt = 40;
		}

		if (timer_salt > 0) {
			timer_salt--;
		}
		else if (timer_salt == 0) {
			playerAnim = JUMP;
			timer_salt--;
		}
		

		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS
		//COLISIONS

		//abans de res colision coords
		app->map->Getcolision_coords(player.x);

		for (int i = 0; app->map->colision_coords[i] != nullptr; ++i) {
			if ((player.x + 64 + player.vx > app->map->colision_coords[i]->x) && (player.x + player.vx < app->map->colision_coords[i]->x + 32) &&
				(player.y + 64 + player.vy > app->map->colision_coords[i]->y) && (player.y + player.vy < app->map->colision_coords[i]->y + 32)) {

				//El player est� colisionant amb una o m�s tiles
				if ((player.x + 64 + player.vx > app->map->colision_coords[i]->x) && (player.x + player.vx < app->map->colision_coords[i]->x + 32) &&
					(player.y + 64 > app->map->colision_coords[i]->y) && (player.y < app->map->colision_coords[i]->y + 32)) {
					//Xoca pel costat
					player.vx = 0;
				}

				if ((player.x + 64 > app->map->colision_coords[i]->x) && (player.x < app->map->colision_coords[i]->x + 32) &&
					(player.y + 64 + player.vy > app->map->colision_coords[i]->y) && (player.y + player.vy < app->map->colision_coords[i]->y + 32)) {
					//xoc vertical
					if (player.vy >= 0) { //xoca amb el terra
						saltant = false;
						if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) { //saltar nom�s quan toquis a terra
							player.vy = -4;
							playerAnim = JUMP;
							saltant = true;
							doblesalt = true;
						}
						else {
							player.vy = 0;
						}
						coyotejump = true;
					}
					else if (player.vy < 0){ //xoca amb el sostre
						player.vy = 0;
					}
				}
				else {
					player.vx = 0;
				}
			}
		}
		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS

		//MOVIMENT
		player.x += player.vx;
		player.y += player.vy;
		player.vx = 0;

	}
	

	//RENDER IMATGES
	
	//camera i l�mits de camera
	app->render->camera.x = 300 - player.x;
	app->render->camera.y = -50;			//350 - player.y

	if (app->render->camera.x > 0) {
		app->render->camera.x = 0;
	}
	if (app->render->camera.x < -17600) { //19200 - 1600
		app->render->camera.x = -17600;
	}

	//parallax
	if (app->render->camera.x > before_camera.x) {
		parallax2--;
		parallax1 -= 0.5;
		parallax3 -= 1.5;
	}
	else if (app->render->camera.x < before_camera.x) {
		parallax2++;
		parallax1 += 0.5;
		parallax3 += 1.5;
	}

	if (parallax2 > 1728) {
		parallax2 = 0;
	}
	else if (parallax2 < 0) {
		parallax2 = 1728;
	}

	if (parallax1 > 1728) {
		parallax1 = 0;
	}
	else if (parallax1 < 0) {
		parallax1 = 1728;
	}

	if (parallax3 > 1728) {
		parallax3 = 0;
	}
	else if (parallax3 < 0) {
		parallax3 = 1728;
	}

	//ImatgeFons Parallax
	app->render->DrawTexture(imgFons1, -app->render->camera.x, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons2, -app->render->camera.x - parallax1, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons2, -app->render->camera.x - parallax1 + 1728, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons3, -app->render->camera.x - parallax2, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons3, -app->render->camera.x - parallax2 + 1728, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons4, -app->render->camera.x - parallax3, -app->render->camera.y - 70, NULL, 1, 3);
	app->render->DrawTexture(imgFons4, -app->render->camera.x - parallax3 + 1728, -app->render->camera.y - 70, NULL, 1, 3);
	
	//Draw decorations
	DrawDecorations();

	//Draw map
	app->map->Draw();

	//Draw Granota
	if (sentit_moviment){
		PlayerRect.y = 0;
		PlayerRectA1.y = 0;
		PlayerRectA2.y = 16;
		PlayerRectJump.y = 0;
		PlayerRectWalk.y = 0;
	}
	else {
		PlayerRect.y = 32;
		PlayerRectA1.y = 32;
		PlayerRectA2.y = 48;
		PlayerRectJump.y = 32;
		PlayerRectWalk.y = 32;
	}

	switch (playerAnim) {
	case IDLE:
		app->render->DrawTexture(granota, player.x, player.y, &PlayerRect, 1, 4);
		break;
	case A1:
		app->render->DrawTexture(granota, player.x, player.y, &PlayerRectA1, 1, 4);
		break;
	case A2:
		app->render->DrawTexture(granota, player.x, player.y, &PlayerRectA2, 1, 4);
		break;
	case JUMP:
		app->render->DrawTexture(granota, player.x, player.y, &PlayerRectJump, 1, 4);
		break;
	case WALK:
		app->render->DrawTexture(granota, player.x, player.y, &PlayerRectWalk, 1, 4);
		break;
	}
	//

	//SCENE TIMER
	if (scene_timer <= 0) {
		scene_timer = 199;
	}
	else {
		scene_timer--;
	}
	//

	
	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	//GODMODE
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		//GODMODE Activator
		godMode = !godMode;
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;
	}
	
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		reset = true;
	}

	if (player.y > 2500 || player.x > 19000) {
		reset = true;
		app->scene_end->active = true;
		active = false;
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (debug)
		DebugDraw();

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

//Carga la posicion del personaje NO SE USA EN ESTE CODIGO
bool Scene::LoadState(pugi::xml_node& configRenderer)
{

	player.x = configRenderer.child("player").attribute("x").as_int();
	player.y = configRenderer.child("player").attribute("y").as_int();

	return true;
}

//Guarda la posicion del personaje NO SE USA EN ESTE CODIGO
bool Scene::SaveState(pugi::xml_node& configRenderer) const
{
	pugi::xml_node player1 = configRenderer.child("player");

	player1.attribute("x").set_value(player.x);
	player1.attribute("y").set_value(player.y);

	return true;
}

//Dibuja los colliders
void Scene::DebugDraw()
{
	app->map->DrawColisions();

	//Dibuja los colliders cargado en ese momento
	for (int i = 0; app->map->colision_coords[i] != nullptr; ++i) {
		SDL_Rect rectCollider = {app->map->colision_coords[i]->x,app->map->colision_coords[i]->y,32,32 };
		app->render->DrawRectangle(rectCollider, 0, 70, 250,80);
	}
	//Dibuja el collider de la rana
	SDL_Rect rectPlayer = { player.x,player.y,64,64 };
	app->render->DrawRectangle(rectPlayer, 255, 255, 0, 80);
}

void Scene::DrawDecorations() {
	app->render->DrawTexture(arbre1, 2800, 64, NULL, 1, 3);
	app->render->DrawTexture(arbre2, 14016, 400, NULL, 1, 3);
	app->render->DrawTexture(tronc1, 12320, 850, NULL, 1, 3);
	app->render->DrawTexture(cartell1, 512, 420, NULL, 1, 3);
	app->render->DrawTexture(cartell5, 13420, 260, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 3648, 580, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 9856, 356, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 15350, 580, NULL, 1, 3);
	app->render->DrawTexture(bush8, 900, 754, NULL, 1, 3);
	app->render->DrawTexture(bush1, 4500, 790, NULL, 1, 3);
	app->render->DrawTexture(bush3, 8260, 790, NULL, 1, 3);
}
