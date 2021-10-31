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

	RectMenu1 = { 700,400,200,50 };
	RectMenu2 = { 700,600,200,50 };
	RectMenu3 = { 700,500,200,50 };
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




	//acceptar opció
	if (opcion == 0)
	{
		app->render->DrawRectangle(RectMenu1, 250, 0, 0);
		app->render->DrawRectangle(RectMenu2, 250, 250, 250);
		app->render->DrawRectangle(RectMenu3, 125, 125, 125);
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			active = false;
			app->scene->active = true;
		}
	}

	else if (opcion == 1)
	{
		app->render->DrawRectangle(RectMenu1, 250, 250, 250);
		app->render->DrawRectangle(RectMenu2, 250, 0, 0);
		app->render->DrawRectangle(RectMenu3, 125, 125, 125);

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			ret = false;
		}
	}

	//seleccionar opció
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN && opcion != 0)
		opcion--;
	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN && opcion != 1)
		opcion++;

	return ret;
}

// Called each loop iteration
bool Scene_END::PostUpdate()
{
	bool ret = true;
	
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

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