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

	//si esta activa la scene
	if (active)
	{

		RectMenu1 = {700,400,200,50 };
		RectMenu2 = { 700,600,200,50 };

		//acceptar opció
		if (opcion == 0)
		{
			app->render->DrawRectangle(RectMenu1, 250, 0, 0);
			app->render->DrawRectangle(RectMenu2, 250, 250, 250);
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


	}

	return ret;
}

// Called each loop iteration
bool Scene_Intro::PostUpdate()
{
	bool ret = true;

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