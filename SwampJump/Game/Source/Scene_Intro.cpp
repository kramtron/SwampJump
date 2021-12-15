#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene_Intro::Scene_Intro() : Module()
{
	name.Create("scene_intro");
}

// Destructor
Scene_Intro::~Scene_Intro()
{}

// Called before render is available
bool Scene_Intro::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene_Intro::Start()
{
	active = false;
	startPress = app->tex->Load("Assets/Menu/gameMenuStart.png");
	exitPress = app->tex->Load("Assets/Menu/gameMenuExit.png");


	return true;
}

// Called each loop iteration
bool Scene_Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene_Intro::Update(float dt)
{
	bool ret = true;
	int x, y, left = 1;
	app->input->GetMousePosition(x, y);
	SDL_Rect zone1 = { 26,801,197,78 };
	SDL_Rect zone2 = { 1318,801,181,78 };

	if (x > zone1.x && x<(zone1.x + zone1.w) && y>zone1.y && y < (zone1.y + zone1.h)) {
		opcion = 0;
	}
	else if (x > zone2.x && x<(zone2.x + zone2.w) && y>zone2.y && y < (zone2.y + zone2.h)) {
		opcion = 1;
	}
		//acceptar opció
		if (opcion == 0)
		{

			app->render->camera.y = 0;

			app->render->DrawTexture(startPress, 0,0, NULL, 1);
			

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
			{
				active = false;
				app->scene->active = true;
			}
		}

		else if (opcion == 1)
		{
			app->render->camera.y = 0;

			app->render->DrawTexture(exitPress, 0,0, NULL, 1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
			{
				ret = false;
			}
		}

		//seleccionar opció
		if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && opcion != 0)
			opcion--;
		if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && opcion != 1)
			opcion++;
		

	return ret;
}

// Called each loop iteration
bool Scene_Intro::PostUpdate()
{
	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene_Intro::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void Scene_Intro::DebugDraw()
{
	
}