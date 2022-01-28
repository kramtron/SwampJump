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

	//Default settings 
	defaultSettingsMenu = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/defaultSettingsMenu.png");
	xCircle = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/xCircle.png");
	xCircleSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/xCircleSelected.png");

	//AudioSettingsTextures
	audioSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/audioSettings.png");
	fxBar = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/fxBar.png");
	musicBar = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/musicBar.png");
	fxSelectedZone = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/mouseInFxZone.png");
	musicSelectedZone = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/mouseInMusicZone.png");
	fxCircle = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/volumeBotton.png");
	musicCircle = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/audio/volumeBotton.png");
	//Screen Menu Textures
	screenSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Screen/defaultScreenMenu.png");
	fullScreenTrue = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Screen/fullScreenTrue.png");
	vSyncTrue = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Screen/vSyncTrue.png");
	fullScreenSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Screen/fullScreenSelected.png");
	vSyncSelected= app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Screen/vSyncSelected.png");

	//Credits Menu Textures
	creditsSelected = app->tex->Load("Assets/NewGlobalMenu/SettingsMenu/Credits/credits.png");


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


	SDL_Rect audio = { 272,156,164,49 };
	SDL_Rect screen = { 272,267,197,49 };
	SDL_Rect credits = { 272,375,218,49 };
	
	if (!settingsMenu) {
		//seleccionar opció
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
				app->scene->reloj = 0;
				active = false;
				app->scene->active = true;
			}

			break;
			//Settings
		case 2:
			app->render->DrawTexture(settingsSelected, 0, 0, NULL, 1);
			//Menu de ajustes
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN) {
				settingsMenu = true;
			}


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
	}
	else if (settingsMenu) {
		//seleccionar opció

		if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)) {
			if (opcion >= 0 && opcion < 2) {
				settingsOption++;
			}
		}
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)) {
			if (opcion > 0 && opcion <= 2) {
				settingsOption--;

			}
		}
		if (x > audio.x && x<(audio.x + audio.w) && y>audio.y && y < (audio.y + audio.h)) {
			settingsOption = 0;
			
		}
		else if (x > screen.x && x<(screen.x + screen.w) && y>screen.y && y < (screen.y + screen.h)) {
			settingsOption = 1;

		}
		else if (x > credits.x && x<(credits.x + credits.w) && y>credits.y && y < (credits.y + credits.h)) {
			settingsOption = 2;

		}
		app->render->DrawTexture(defaultSettingsMenu, 0, 0, NULL, 1);
		app->render->DrawTexture(xCircle, 0, 0, NULL, 1);
		SDL_Rect xCircleRect = {1293,138,71,67};
		if (x > xCircleRect.x && x<(xCircleRect.x + xCircleRect.w) && y>xCircleRect.y && y < (xCircleRect.y + xCircleRect.h)) {
			app->render->DrawTexture(xCircleSelected, 0, 0, NULL, 1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
			{
				settingsMenu = false;
				app->SaveGameRequest();
				loadPreConfig = true;
				app->LoadGameRequest();
			}

		}
		SDL_Rect musicZone = { 535,223,855,104 };
		SDL_Rect fxZone = { 535,376,855,104 };
		SDL_Rect fullScreenZone = { 1016,202,78,78 };
		SDL_Rect vSyncZone = { 1016,372,78,78 };
		SDL_Rect fullScreenMouseZone = { 529,195,861,97 };
		SDL_Rect vSyncMouseZone = { 529,361,861,97};
		
		switch (settingsOption)
		{
		case 0:
			app->render->DrawTexture(audioSelected, 0, 0, NULL, 1);
			app->render->DrawTexture(fxBar, 0, 0, NULL, 1);
			app->render->DrawTexture(musicBar, 0, 0, NULL, 1);
			app->render->DrawTexture(fxCircle, fxCircle_X, 393, NULL, 1);
			app->render->DrawTexture(fxCircle, musicCircle_X, 237, NULL, 1);

		
			if (x > fxZone.x && x<(fxZone.x + fxZone.w) && y>fxZone.y && y < (fxZone.y + fxZone.h)) {
				volumeOption = 1;

			}
			else if (x > musicZone.x && x<(musicZone.x + musicZone.w) && y>musicZone.y && y < (musicZone.y + musicZone.h)) {
				volumeOption = 0;

			}
			if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)) {
				if (opcion >= 0 && opcion < 1) {
					volumeOption++;
				}
			}
			if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)) {
				if (opcion > 0 && opcion <= 1) {
					volumeOption--;

				}
			}

			switch (volumeOption)
			{
			case 0:
				app->render->DrawTexture(musicSelectedZone, 0, 0, NULL, 1);

				if (app->input->GetMouseButtonDown(left) == KEY_REPEAT && app->input->mouseX <= 1290 && app->input->mouseX >= 820 && app->input->mouseY >= 244 && app->input->mouseY <= 304)
				{
					musicCircle_X = app->input->mouseX - 40;
				}
				app->audio->volume_mix_max_music = ((musicCircle_X / 470) - 1.7446808851) * 128;

				app->audio->volume_mix_max_music = app->audio->volume_mix_max_music + 10;

				if (app->audio->volume_mix_max_music < 0)
				{
					app->audio->volume_mix_max_music = 0;
				}

				break;
			case 1:

				app->render->DrawTexture(fxSelectedZone, 0, 0, NULL, 1);


				if (app->input->GetMouseButtonDown(left) == KEY_REPEAT && app->input->mouseX <= 1290 && app->input->mouseX >= 820 && app->input->mouseY >= 400 && app->input->mouseY <= 460)
				{
					fxCircle_X = app->input->mouseX - 40;
				}

				app->audio->volume_mix_max_wav = ((fxCircle_X / 470) - 1.7446808851) * 128;

				app->audio->volume_mix_max_wav = app->audio->volume_mix_max_wav + 10;

				if (app->audio->volume_mix_max_wav < 0)
				{
					app->audio->volume_mix_max_wav = 0;
				}

				LOG("fxSound: %0.4f", app->audio->volume_mix_max_wav);

				break;
			}


			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
			{

				audioMenu = true;;
			}


			break;
		case 1:
			app->render->DrawTexture(screenSelected, 0, 0, NULL, 1);
			if (app->win->fullscreen) {
				app->render->DrawTexture(fullScreenTrue, 0, 0, NULL, 1);
			}
			if (vSyncMarc == true) {
				app->render->DrawTexture(vSyncTrue, 0, 0, NULL, 1);
			}
			if (x > fullScreenMouseZone.x && x<(fullScreenMouseZone.x + fullScreenMouseZone.w) && y>fullScreenMouseZone.y && y < (fullScreenMouseZone.y + fullScreenMouseZone.h)) {
				screenOption = 0;
			}
			else if (x > vSyncMouseZone.x && x<(vSyncMouseZone.x + vSyncMouseZone.w) && y>vSyncMouseZone.y && y < (vSyncMouseZone.y + vSyncMouseZone.h)) {
				screenOption = 1;
			}
			switch (screenOption)
			{
			case 0:
				if (x > fullScreenZone.x && x<(fullScreenZone.x + fullScreenZone.w) && y>fullScreenZone.y && y < (fullScreenZone.y + fullScreenZone.h)) {
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
					{
						app->win->fullscreen = !app->win->fullscreen;
						app->SaveGameRequest();	
						app->win->CleanUp();
						app->win->Awake();
					}
				}
				break;
			case 1:
				if (x > vSyncZone.x && x<(vSyncZone.x + vSyncZone.w) && y>vSyncZone.y && y < (vSyncZone.y + vSyncZone.h)) {
				
					if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
					{
						vSyncMarc = !vSyncMarc;
					}
				}
				break;
			}
			break;
		case 2:
			app->render->DrawTexture(creditsSelected, 0, 0, NULL, 1);

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->GetMouseButtonDown(left) == KEY_DOWN)
			{
				audioMenu = true;;
			}
			break;
		}
		
	}

		
		

	return ret;
}

// Called each loop iteration
bool Scene_Intro::PostUpdate()
{
	bool ret = true;

	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

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
bool Scene_Intro::LoadGameConfig(pugi::xml_node& configAudio, pugi::xml_node& configScreen, pugi::xml_node& configVsync) {

	//Audio Load
	musicCircle_X = configAudio.child("volume").attribute("music").as_float();
	fxCircle_X = configAudio.child("volume").attribute("fx").as_float();

	//Screen Load
	app->win->fullscreen = configScreen.child("fullscreen").attribute("value").as_bool();
	//Vsync Load
	return true;
}

bool Scene_Intro::SaveGameConfig(pugi::xml_node& configAudio, pugi::xml_node& configScreen, pugi::xml_node& configVsync) const{
	pugi::xml_node audioConfig = configAudio;
	//Audio Save
	configAudio.child("volume").attribute("music").set_value(musicCircle_X);
	configAudio.child("volume").attribute("fx").set_value(fxCircle_X);
	pugi::xml_node screenConfig = configScreen;

	//Screen Save
	configScreen.child("fullscreen").attribute("value").set_value(app->win->fullscreen);

	//Vsync Save

	return true;
}