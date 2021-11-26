#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Scene.h"
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
	pickUpTexture = app->tex->Load("Assets/textures/pickups.png");

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

PickUp* ModuleScore::HpCreate(int x, int y, int value) {
	PickUp* p = new PickUp({x, y, 75, 75}, PickUp::PickUpType::HP, value);
	pickUpList->add(p);
	return p;
}

PickUp* ModuleScore::CoinCreate(int x, int y, int value) {
	PickUp* p = new PickUp({ x, y, 100, 100 }, PickUp::PickUpType::COIN, value);
	pickUpList->add(p);
	return p;
}

void ModuleScore::DrawPickUps(){
	p2List_item<PickUp*>* current_pickUp = pickUpList->getFirst();
	while (current_pickUp != NULL) {
		switch (current_pickUp->data->pickUpType) {
		case PickUp::PickUpType::HP:
			SDL_Rect hpRect = { 0, 0, 0, 0 };
			app->render->DrawTexture(pickUpTexture,current_pickUp->data->rect.x, current_pickUp->data->rect.y, &hpRect);
			break;
		case PickUp::PickUpType::COIN:
			SDL_Rect coinRect = { 0, 0, 0, 0 };
			app->render->DrawTexture(pickUpTexture, current_pickUp->data->rect.x, current_pickUp->data->rect.y, &coinRect);
			break;
		}
		current_pickUp->next;
	}
}

void ModuleScore::CollidePickUps() {
	p2List_item<PickUp*>* current_pickUp = pickUpList->getFirst();
	while (current_pickUp != NULL) {

	}
}