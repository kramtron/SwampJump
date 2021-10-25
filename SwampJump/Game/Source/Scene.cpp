#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
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
	app->map->Load("Mapa1.tmx");
	app->map->GetColisionCoords();
	//app->map->Load("iso_walk.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	
	imgFons = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Background.png");
	
	app->render->camera.x = 0;
	app->render->camera.y = -50;

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
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		app->SaveGameRequest();


	//PLAYER MOVE
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		Player.vy = -2;
	}

	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		Player.vy = 2;
	}

	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		Player.vx = -2;
	}

	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		Player.vx = 2;
	}
	//

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

	//COLISIONS
	for (int i = 0; i < 1177; ++i) {
		if ((Player.x + 64 >= app->map->colisionCoords[i].x) && (Player.x <= app->map->colisionCoords[i].x + 32) &&
			(Player.y + 64 >= app->map->colisionCoords[i].y) && (Player.y <= app->map->colisionCoords[i].y + 32)) {

			if (Player.x + 64 >= app->map->colisionCoords[i].x) {
				if (Player.vx < 0) { //parar mov a l'esquerra
					Player.vx = 0;
					Player.x = app->map->colisionCoords[i].x + 33;
				}
			}
			if (Player.x <= app->map->colisionCoords[i].x + 32) {
				if (Player.vx > 0) { //parar mov a la dreta
					Player.vx = 0;
					Player.x = app->map->colisionCoords[i].x - 65;
				}
			}
			if (Player.y + 64 >= app->map->colisionCoords[i].y) {
				if (Player.vy < 0) { //parar mov amunt
					Player.vy = 0;
					Player.y = app->map->colisionCoords[i].y + 33;
				}
			}
			if (Player.y <= app->map->colisionCoords[i].y + 32) {
				if (Player.vy > 0) { //parar mov avall
					Player.vy = 0;
					Player.y = app->map->colisionCoords[i].y - 65;
				}
			}
		}
	}

	Player.x += Player.vx;
	Player.y += Player.vy;
	Player.vx = 0;
	Player.vy = 0;

	//RENDER IMATGES
	app->render->DrawTexture(imgFons, 0, 0, NULL);
	//Draw map
	app->map->Draw();

	rect1 = { Player.x,Player.y,64,64 };
	app->render->DrawRectangle(rect1, 200, 200, 200);
	
	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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
