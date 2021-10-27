#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene_Logo::Scene_Logo() : Module()
{
	name.Create("scene_logo");
}

// Destructor
Scene_Logo::~Scene_Logo()
{}

// Called before render is available
bool Scene_Logo::Awake()
{
	LOG("Loading Logo");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene_Logo::Start()
{

	return true;
}

// Called each loop iteration
bool Scene_Logo::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene_Logo::Update(float dt)
{
	bool ret = true;

	//si esta activa la scene
	if (active)
	{
		//acceptar opci�
		if (timerLogo == 2000)
		{
			active = false;
			app->scene_intro->active = true;
		}
		timerLogo++;
	}

	return ret;
}

// Called each loop iteration
bool Scene_Logo::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Scene_Logo::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void Scene_Logo::DebugDraw()
{

}