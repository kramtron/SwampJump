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
	CollidePickUps();

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
	DebugDrawPickUps();
}

PickUp* ModuleScore::HpCreate(int x, int y, int value = 0) {
	PickUp* p = new PickUp({ x, y, 60, 75 }, {0, 0, 32, 32}, PickUp::PickUpType::HP, value); //colliderRect, imageRect
	pickUpList.add(p);
	return p;
}

PickUp* ModuleScore::CoinCreate(int x, int y, int value = 0) {
	PickUp* p = new PickUp({ x, y, 45, 48 }, {0, 32, 16 ,16}, PickUp::PickUpType::COIN, value); //colliderRect, imageRect
	pickUpList.add(p);
	return p;
}

void ModuleScore::DrawPickUps(){
	p2List_item<PickUp*>* current_pickUp = pickUpList.getFirst();
	while (current_pickUp != NULL) {
		switch (current_pickUp->data->pickUpType) {
		case PickUp::PickUpType::HP:
			app->render->DrawTexture(pickUpTexture,current_pickUp->data->rect.x, current_pickUp->data->rect.y, &current_pickUp->data->imageRect, 1.0f, 3.0f);
			break;
		case PickUp::PickUpType::COIN:
			app->render->DrawTexture(pickUpTexture, current_pickUp->data->rect.x, current_pickUp->data->rect.y, &current_pickUp->data->imageRect, 1.0f, 3.0f);
			break;
		}
		current_pickUp = current_pickUp->next;
	}
}

void ModuleScore::DebugDrawPickUps() {
	p2List_item<PickUp*>* current_pickUp = pickUpList.getFirst();
	while (current_pickUp != NULL) {
		switch (current_pickUp->data->pickUpType) {
		case PickUp::PickUpType::HP:
			app->render->DrawRectangle(current_pickUp->data->rect, 100, 0, 0, 100);
			break;
		case PickUp::PickUpType::COIN:
			app->render->DrawRectangle(current_pickUp->data->rect, 0, 100, 100, 100);
			break;
		}
		current_pickUp = current_pickUp->next;
	}
}

void ModuleScore::CollidePickUps() {
	p2List_item<PickUp*>* current_pickUp = pickUpList.getFirst();
	while (current_pickUp != NULL) {
		if (((app->scene->player.x + 64) > current_pickUp->data->rect.x) &&
			(app->scene->player.x < (current_pickUp->data->rect.x + current_pickUp->data->rect.w)) &&
			((app->scene->player.y + 64) > current_pickUp->data->rect.y) &&
			(app->scene->player.y < (current_pickUp->data->rect.y + current_pickUp->data->rect.h))) 
		{	//Colliding
			
			switch (current_pickUp->data->pickUpType) {
			case PickUp::PickUpType::HP:	//HP effect
				
				break;
			case PickUp::PickUpType::COIN:	//COIN effect

				break;
			}

			pickUpList.del(current_pickUp);
		}
		current_pickUp = current_pickUp->next;
	}
}

bool ModuleScore::LoadPickUpsSpawn(pugi::xml_node& scoreSpawnData) {
	//meleEnemicSpawn1.x = configMeleEnemicSpawn.child("spawnPosition1").attribute("x").as_int();

	pointSpawn1.x = scoreSpawnData.child("spawnPosition1").attribute("x").as_float();
	pointSpawn1.y = scoreSpawnData.child("spawnPosition1").attribute("y").as_float();
	pointSpawn2.x = scoreSpawnData.child("spawnPosition2").attribute("x").as_float();
	pointSpawn2.y = scoreSpawnData.child("spawnPosition2").attribute("y").as_float();
	pointSpawn3.x = scoreSpawnData.child("spawnPosition3").attribute("x").as_float();
	pointSpawn3.y = scoreSpawnData.child("spawnPosition3").attribute("y").as_float();
	pointSpawn4.x = scoreSpawnData.child("spawnPosition4").attribute("x").as_float();
	pointSpawn4.y = scoreSpawnData.child("spawnPosition4").attribute("y").as_float();


	return true;

}
bool ModuleScore::LoadPointsData(pugi::xml_node& pointsData) {

	normalWhPoints.w = pointsData.attribute("width").as_float();
	normalWhPoints.h = pointsData.attribute("heigth").as_float();
	normalApplePoints = pointsData.attribute("normalApplePoints").as_float();
	goldApplePoints = pointsData.attribute("goldApplePoints").as_float();

	return true;
}

bool ModuleScore::LoadHpData(pugi::xml_node& hpData) {

	hpUp = hpData.attribute("hpUp").as_float();
	normalWhHp.w= hpData.attribute("width").as_float();
	normalWhHp.h= hpData.attribute("heigth").as_float();

	return true;
}

bool ModuleScore::SaveState(pugi::xml_node& saveData)const {

	return true;
}