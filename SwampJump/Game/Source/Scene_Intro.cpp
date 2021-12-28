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
	mainMenuScreen = app->tex->Load("Assets/NewGlobalMenu/MainMenuNoSelected.png");
	playSelected = app->tex->Load("Assets/NewGlobalMenu/StartSelected.png");
	newGameSelected = app->tex->Load("Assets/NewGlobalMenu/NewGameSelected.png");
	settingsSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsSelected.png");
	exitSelected = app->tex->Load("Assets/NewGlobalMenu/ExitSelected.png");


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
	app->render->DrawTexture(mainMenuScreen, 0, 0,NULL,1);
	int x, y, left = 1;
	app->input->GetMousePosition(x, y);
	LOG("Mouse x: %d, Mouse y: %d",x,y);
	SDL_Rect play = { 1053,170,231,70 };
	SDL_Rect newGame = { 1053,315,465,70 };
	SDL_Rect settings = { 1050,462,410,70 };
	SDL_Rect exit = { 1050,610,215,70 };

	if (x > play.x && x<(play.x + play.w) && y>play.y && y < (play.y + play.h)) {
		opcion = 0;
	}
	else if (x > newGame.x && x<(newGame.x + newGame.w) && y>newGame.y && y < (newGame.y + newGame.h)) {
		opcion = 1;
	}
	else if (x > settings.x && x<(settings.x + settings.w) && y>settings.y && y < (settings.y + settings.h)) {
		opcion = 2;
	}
	else if (x > exit.x && x<(exit.x + exit.w) && y>exit.y && y < (exit.y + exit.h)) {
		opcion = 3;
	}
	switch (opcion)
	{
		//Play current saved game
	case 0:
		app->render->camera.y = 0;

		app->render->DrawTexture(playSelected, 0, 0, NULL, 1);


		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
		{
			active = false;
			app->scene->active = true;
		}
		break;

		//NewGame
	case 1:
		app->render->camera.y = 0;
		//Falta colocar el render
		app->render->DrawTexture(newGameSelected, 0, 0, NULL, 1);
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN) {
			app->scene->player.playedBefore = false;
			active = false;
			app->scene->active = true;
		}
		
		break;
		//Settings
	case 2:
		app->render->DrawTexture(settingsSelected, 0, 0, NULL, 1);
		//Menu de ajustes
		/*
		app->win->fullscreen_window;
		app->win->fullscreen;*/
		break;
		//Exit
	case 3:
		
		
		app->render->camera.y = 0;

		app->render->DrawTexture(exitSelected, 0, 0, NULL, 1);
		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
		{
			ret = false;
		}
		break;
	}


		//seleccionar opci�
		if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)) {
			if (opcion >= 0 && opcion < 3) {
				opcion++;
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)) {
			if (opcion > 0 && opcion <= 3) {
				opcion--;
			}
		}
		

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