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
	if (active)
	{
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			active = false;
			app->scene->active = true;
		}
	}

	return true;
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