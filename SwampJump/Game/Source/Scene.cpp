#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Scene_Intro.h"
#include "Map.h"

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
	if(app->scene_intro->active == true)
		active = false;

	app->map->Load("Mapa1.tmx");
	app->map->GetColisionCoords();
	//app->map->Load("iso_walk.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	
	imgFons = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Background.png");
	granota = app->tex->Load("Assets/textures/frog.png");
	
	app->render->camera.x = 0;
	app->render->camera.y = -120;

	PlayerRect = { 16, 0, 16, 16 };
	PlayerRectA1 = { 0, 0, 16, 16 };
	PlayerRectA2 = { 0, 16, 16, 16 };
	PlayerRectJump = { 32, 0, 16, 16 };

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
	//Te coloca en el inicio del nivel
	if (reset) {
		Player.x = 400;
		Player.y = 426;
		reset=false;
	}
	//LOAD SAVE
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	//CAMERA
	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		app->render->camera.y -= 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		app->render->camera.y += 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		app->render->camera.x -= 5;
		
	}
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		app->render->camera.x += 5;
		
	}

	
	if (godMode) {
		LOG("GODMODE ON");
		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			Player.x += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			Player.x += 5;
		}

		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			Player.y += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			Player.y += 5;
		}

	}
	else if (!godMode) {
		LOG("GODMODE OFF");
		//ANIMACIO TERRA
		if (!saltant) {
			if ((SceneTimer < 40) || (SceneTimer > 80 && SceneTimer < 120)) {
				playerAnim = A1;
			}
			else if (SceneTimer >= 120) {
				playerAnim = IDLE;
			}
			else {
				playerAnim = A2;
			}
		}
		//MOVIMENT
		Player.x += Player.vx;
		Player.y += Player.vy;
		Player.vx = 0;
		//Player.vy = 0;
		if (AcelerationTimer == 0) {
			Player.vy += Player.ay;
			AcelerationTimer = 10;
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) { //Aguantar el salt
				AcelerationTimer = 25;
			}
		}
		else {
			AcelerationTimer--;
		}

		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS
		//COLISIONS
		for (int i = 0; i < 1177; ++i) {
			if ((Player.x + 64 >= app->map->colisionCoords[i].x) && (Player.x <= app->map->colisionCoords[i].x + 32) &&
				(Player.y + 64 >= app->map->colisionCoords[i].y) && (Player.y <= app->map->colisionCoords[i].y + 32)) {

				//El player est� colisionant amb una o m�s tiles

				//index m�s alt = m�s aprop de la tile
				int indexDreta = Player.x + 64 - app->map->colisionCoords[i].x;
				int indexEsquerra = -(Player.x - (app->map->colisionCoords[i].x + 32));
				int indexBaix = Player.y + 64 - app->map->colisionCoords[i].y;
				int indexDalt = -(Player.y - (app->map->colisionCoords[i].y + 32));

				int index[4];
				index[0] = indexDreta;
				index[1] = indexEsquerra;
				index[2] = indexBaix;
				index[3] = indexDalt;

				//Quin index �s m�s petit?
				for (int j = 0; j < 3; j++) {
					if (index[0] > index[j + 1]) {
						index[0] = index[j + 1];
					}
				}

				if (index[0] == indexDreta) {//colisi� dreta
					Player.vx = 0;
					Player.x = app->map->colisionCoords[i].x - 64;
				}
				if (index[0] == indexEsquerra) {//colisi� esquerra
					Player.vx = 0;
					Player.x = app->map->colisionCoords[i].x + 32;
				}
				if (index[0] == indexBaix) {//colisi� baix
					Player.vy = 0;
					saltant = false;
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) { //saltar nom�s quan toquis a terra
						Player.vy = -5;
						playerAnim = JUMP;
						saltant = true;
					}
					else {
						Player.y = app->map->colisionCoords[i].y - 64;
					}
				}
				if (index[0] == indexDalt) {//colisi� dalt
					Player.vy = 0;
					Player.y = app->map->colisionCoords[i].y + 33;
				}
			}
		}
		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS

		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			Player.vx = -2;
		}

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			Player.vx = 2;
		}
		//
	}
	


	//RENDER IMATGES
	//camera
	app->render->camera.x = 300 - Player.x; //CANVIAR

	//ImatgeFons
	app->render->DrawTexture(imgFons, -app->render->camera.x, -app->render->camera.y, NULL, 1, 3);
	
	//Draw map
	app->map->Draw();

	//Draw Granota
	switch (playerAnim) {
	case IDLE:
		app->render->DrawTexture(granota, Player.x, Player.y, &PlayerRect, 1, 4);
		break;
	case A1:
		app->render->DrawTexture(granota, Player.x, Player.y, &PlayerRectA1, 1, 4);
		break;
	case A2:
		app->render->DrawTexture(granota, Player.x, Player.y, &PlayerRectA2, 1, 4);
		break;
	case JUMP:
		app->render->DrawTexture(granota, Player.x, Player.y, &PlayerRectJump, 1, 4);
		break;
	}
	//

	//SCENE TIMER
	if (SceneTimer <= 0) {
		SceneTimer = 200;
	}
	else {
		SceneTimer--;
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

	if (Player.y > 2500) {
		reset = true;
		active = false;
		app->scene_intro->active = true;
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

bool Scene::LoadState(pugi::xml_node& configRenderer)
{

	Player.x = configRenderer.child("player").attribute("x").as_int();
	Player.y = configRenderer.child("player").attribute("y").as_int();

	return true;
}
bool Scene::SaveState(pugi::xml_node& configRenderer) const
{
	pugi::xml_node player = configRenderer.child("player");

	player.attribute("x").set_value(Player.x);
	player.attribute("y").set_value(Player.y);

	return true;
}



void Scene::DebugDraw()
{
	for (int i = 0; i < 1177; ++i) {
		SDL_Rect rectCollider = {app->map->colisionCoords[i].x,app->map->colisionCoords[i].y,32,32 };
		app->render->DrawRectangle(rectCollider, 255, 0, 0,80);
	}


}