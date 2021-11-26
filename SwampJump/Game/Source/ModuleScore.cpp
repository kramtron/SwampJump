#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "ModuleEnemy.h"
#include "ModuleScore.h"
#include "Map.h"
#include "p2List.h"

#include "Defs.h"
#include "Log.h"

ModuleScore::ModuleScore() : Module()
{
	name.Create("ModuleScore");
}

// Destructor
ModuleScore::~ModuleScore()
{}

// Called before render is available
bool ModuleScore::Awake()
{
	LOG("Loading Logo");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool ModuleScore::Start()
{

	return true;
}

// Called each loop iteration
bool ModuleScore::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ModuleScore::Update(float dt)
{

	bool ret = true;


	return ret;
}

// Called each loop iteration
bool ModuleScore::PostUpdate()
{
	bool ret = true;
	return ret;
}

// Called before quitting
bool ModuleScore::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void ModuleScore::DebugDraw()
{

}

HitPoints* ModuleScore::PointsCreator() {

	HitPoints* newPointItem=new HitPoints();
	

	return newPointItem;
}
Score* ModuleScore::ScoreCreator() {
	Score* newScoreItem=new Score();

	

	return newScoreItem;
}
PowerUp* ModuleScore::PowerUpCreator() {
	PowerUp* newPowerUpItem=new PowerUp();

	

	return newPowerUpItem;
}