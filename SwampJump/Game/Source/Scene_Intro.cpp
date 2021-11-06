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
	startPress = app->tex->Load("Assets/Menu/startPress.png");
	startNotPress = app->tex->Load("Assets/Menu/startNotPress.png");
	exitPress = app->tex->Load("Assets/Menu/exitPress.png");
	exitNotPress = app->tex->Load("Assets/Menu/exitNotPress.png");

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

	
	
		//acceptar opció
		if (opcion == 0)
		{



			app->render->DrawTexture(startPress, 225, -120, NULL, 1);
			app->render->DrawTexture(exitNotPress, 348, 120, NULL, 1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) 
			{
				active = false;
				app->scene->active = true;
			}
		}

		else if (opcion == 1)
		{
			app->render->DrawTexture(startNotPress, 225, -120, NULL, 1);
			app->render->DrawTexture(exitPress, 348, 120, NULL, 1);
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				ret = false;
			}
		}

		//seleccionar opció
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) && opcion != 0)
			opcion--;
		if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN) && opcion != 1)
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