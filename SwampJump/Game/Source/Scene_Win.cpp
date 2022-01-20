#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Scene_END.h"
#include "Scene_Win.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene_Win::Scene_Win() : Module()
{
	name.Create("scene_win");
}

// Destructor
Scene_Win::~Scene_Win()
{}

// Called before render is available
bool Scene_Win::Awake()
{
	LOG("Loading END");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene_Win::Start()
{
	points = app->tex->Load("Assets/Textures/apple.png");
	timer = app->tex->Load("Assets/Textures/cronografo.png");

	gameOverStart = app->tex->Load("Assets/Menu/gameOverPlay.png");
	gameOverExit = app->tex->Load("Assets/Menu/gameOverExit.png");

	active = false;

	return true;
}

// Called each loop iteration
bool Scene_Win::PreUpdate()
{
	return true;

}

// Called each loop iteration
bool Scene_Win::Update(float dt)
{
	bool ret = true;

	/*//Draw the apple
	app->render->DrawTexture(points, -app->render->camera.x + 20, -app->render->camera.y + 30, 0, 1, 3);
	FontDraw(app->scene->player.actualPoints, 3, -app->render->camera.x + 150, -app->render->camera.y + 35, 35, 1);


	//Draw the time
	app->render->DrawTexture(timer, -app->render->camera.x + 1530, -app->render->camera.y + 27, 0, 1, 0.1);
	FontDraw(dt, 5, -app->render->camera.x + 1500, -app->render->camera.y + 35, 35, 1);

	//Draw the score

	score += (app->scene->player.actualPoints * 33); //33 per posar algo
	score -= (dt * 0.55); // 0.55 per posar un numero*/
	
	//app->render->DrawTexture(scoreTexture, -app->render->camera.x + 1530, -app->render->camera.y + 27, 0, 1, 0.1);
	//FontDraw(score, 5, -app->render->camera.x + 1500, -app->render->camera.y + 35, 35, 1);


	//acceptar opció
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

	//seleccionar opció
	if ((app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && opcion != 0)
		opcion--;

	if ((app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && opcion != 1)
		opcion++;

	return ret;
}

// Called each loop iteration
bool Scene_Win::PostUpdate()
{
	bool ret = true;

	/*if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;*/

	return ret;
}

// Called before quitting
bool Scene_Win::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void Scene_Win::DebugDraw()
{

}

void Scene_Win::FontDraw(int score, int n, int posX, int posY, int separacio, float scale) {
	bool positive = true;
	if (score < 0) {
		positive = false;
		score = -score;
	}

	int scoreCopia = score;
	int scoreArray[10];	//max numbers
	for (int j = 0; j < n; ++j) {
		scoreArray[j] = scoreCopia % 10;
		scoreCopia /= 10;
	}

	SDL_Rect rect0 = { 259, 65, 33, 40 };
	SDL_Rect rect1 = { 25, 11, 20, 38 };
	SDL_Rect rect2 = { 80, 10, 29, 40 };
	SDL_Rect rect3 = { 141, 10, 30, 40 };
	SDL_Rect rect4 = { 200, 11, 31, 38 };
	SDL_Rect rect5 = { 261, 10, 29, 40 };
	SDL_Rect rect6 = { 19, 65, 32, 40 };
	SDL_Rect rect7 = { 82, 65, 26, 40 };
	SDL_Rect rect8 = { 140, 65, 31, 40 };
	SDL_Rect rect9 = { 199, 65, 32, 40 };
	SDL_Rect rect_ = { 0, 113, 31, 11 };

	for (int k = 0; k < n; ++k) {

		switch (scoreArray[k]) {
		case 0:
			app->render->DrawTexture(nombres, posX, posY, &rect0, scale);
			break;
		case 1:
			app->render->DrawTexture(nombres, posX, posY, &rect1, scale);
			break;
		case 2:
			app->render->DrawTexture(nombres, posX, posY, &rect2, scale);
			break;
		case 3:
			app->render->DrawTexture(nombres, posX, posY, &rect3, scale);
			break;
		case 4:
			app->render->DrawTexture(nombres, posX, posY, &rect4, scale);
			break;
		case 5:
			app->render->DrawTexture(nombres, posX, posY, &rect5, scale);
			break;
		case 6:
			app->render->DrawTexture(nombres, posX, posY, &rect6, scale);
			break;
		case 7:
			app->render->DrawTexture(nombres, posX, posY, &rect7, scale);
			break;
		case 8:
			app->render->DrawTexture(nombres, posX, posY, &rect8, scale);
			break;
		case 9:
			app->render->DrawTexture(nombres, posX, posY, &rect9, scale);
			break;
		}

		posX -= separacio; //Separació entre nombres
	}

	if (!positive) {
		app->render->DrawTexture(nombres, posX, posY + 10, &rect_, scale);
	}
}
