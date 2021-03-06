#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Scene_END.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene_END::Scene_END() : Module()
{
	name.Create("scene_end");
}

// Destructor
Scene_END::~Scene_END()
{}

// Called before render is available
bool Scene_END::Awake()
{
	LOG("Loading END");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene_END::Start()
{
	gameOverStart = app->tex->Load("Assets/Menu/gameOverPlay.png");
	gameOverExit = app->tex->Load("Assets/Menu/gameOverExit.png");
	
	active = false;

	return true;
}

// Called each loop iteration
bool Scene_END::PreUpdate()
{
	return true;

}

// Called each loop iteration
bool Scene_END::Update(float dt)
{
	bool ret = true;




	//acceptar opci?
	if (opcion == 0)
	{
		app->render->camera.y = 0;
		app->render->camera.x = 0;
		app->render->DrawTexture(gameOverStart, 0, 0, NULL, 1);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			active = false;
			app->scene_intro->active = true;
		}
	}

	else if (opcion == 1)
	{
		app->render->camera.y = 0;
		app->render->camera.x = 0;
		app->render->DrawTexture(gameOverExit, 0, 0, NULL, 1);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			ret = false;
		}
	}

	//seleccionar opci?
	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && opcion != 0)
		opcion--;

	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && opcion != 1)
		opcion++;

	return ret;
}

// Called each loop iteration
bool Scene_END::PostUpdate()
{
	bool ret = true;
	
	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

	return ret;
}

// Called before quitting
bool Scene_END::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void Scene_END::DebugDraw()
{

}