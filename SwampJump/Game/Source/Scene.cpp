#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "Scene_END.h"
#include "Map.h"
#include "Animation.h"
#include "ModuleEnemy.h"
#include "ModuleScore.h"


#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	if(app->scene_logo->active == true)
		active = false;


	app->map->Load("Mapa1.tmx");
	//app->map->Load("iso_walk.tmx");
	
	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
	
	imgFons1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/1.png");
	imgFons2 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/2.png");
	imgFons3 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/3.png");
	imgFons4 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/2 Background/Layers/5.png");
	granota = app->tex->Load("Assets/textures/frog.png");

	//Sprites Decoraci�
	arbre1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Willows/3.png");
	arbre2 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Trees/3.png");
	tronc1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Ridges/1.png");
	cartell1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/1.png");
	cartell5 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/5.png");
	cartell8 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Pointers/8.png");
	bush1 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/1.png");
	bush3 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/3.png");
	bush8 = app->tex->Load("Assets/TilesAssets/assets2dPlatformer/3 Objects/Bushes/8.png");
	
	app->render->camera.x = 0;
	app->render->camera.y = -120;


	// ANIMACIONS
	idleRAnim.Empty();	//Idle Right
	idleRAnim.PushBack({ 16, 0, 16, 16 });	//Idle
	idleRAnim.PushBack({ 16, 0, 16, 16 });	//Idle
	idleRAnim.PushBack({ 16, 0, 16, 16 });	//Idle
	idleRAnim.PushBack({ 0, 0, 16, 16 });	//Croar1
	idleRAnim.PushBack({ 0, 16, 16, 16 });	//Croar2
	idleRAnim.loop = true;
	idleRAnim.speed = 0.015f;

	idleLAnim.Empty();	//Idle Left
	idleLAnim.PushBack({ 16, 32, 16, 16 });	//Idle left
	idleLAnim.PushBack({ 16, 32, 16, 16 });	//Idle left
	idleLAnim.PushBack({ 16, 32, 16, 16 });	//Idle left
	idleLAnim.PushBack({ 0, 32, 16, 16 });	//Croar1 left
	idleLAnim.PushBack({ 0, 48, 16, 16 });	//Croar2 left
	idleLAnim.pingpong = true;
	idleLAnim.speed = 0.015f;

	jumpRAnim.Empty();	//Jump Right
	jumpRAnim.PushBack({ 48, 0, 16, 16 });	//walk
	jumpRAnim.PushBack({ 32, 0, 16, 16 });	//Jump
	jumpRAnim.loop = false;
	jumpRAnim.speed = 0.03f;

	jumpLAnim.Empty();	//Jump Left
	jumpLAnim.PushBack({ 48, 32, 16, 16 });	//walk left
	jumpLAnim.PushBack({ 32, 32, 16, 16 });	//Jump left
	jumpLAnim.loop = false;
	jumpLAnim.speed = 0.03f;

	walkRAnim.Empty();	//Walk Right
	walkRAnim.PushBack({ 48, 0, 16, 16 });	//Walk
	walkRAnim.PushBack({ 16, 0, 16, 16 });	//Idle
	walkRAnim.loop = true;
	walkRAnim.speed = 0.02f;

	walkLAnim.Empty();	//Walk Left
	walkLAnim.PushBack({ 48, 32, 16, 16 });	//Walk left
	walkLAnim.PushBack({ 16, 32, 16, 16 });	//Idle left
	walkLAnim.loop = true;
	walkLAnim.speed = 0.02f;
	
	currentFrogAnimation = &idleRAnim;
	// ANIMACIONS

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	//beforeCoords player
	before_camera.x = app->render->camera.x;
	before_camera.y = app->render->camera.y;

	//Te coloca en el inicio del nivel
	if (reset) {
		player.x = 300;
		player.y = 300;
		parallax1 = 0;
		parallax2 = 0;
		parallax3 = 0;
		reset = false;
	}
	//LOAD SAVE
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();
	
	if (godMode) {
		LOG("GODMODE ON");
		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
			player.x += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			player.x += 5;
		}

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			player.y += -5;
		}

		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			player.y += 5;
		}

		//CAMERA
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			app->render->camera.y -= 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			app->render->camera.y += 1;
		}
		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			app->render->camera.x -= 5;

		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			app->render->camera.x += 5;

		}

	}
	else if (!godMode) {
		LOG("GODMODE OFF");

		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
 			player.vx = -2;
			sentit = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			player.vx = 2;
			sentit = true;
		}
		//
		
		if (aceleration_timer == 0) {
			player.vy += player.ay;
			aceleration_timer = 10;
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) { //Aguantar el salt
				aceleration_timer = 25;
			}
		}
		else {
			aceleration_timer--;
		}

		if (player.vy == 0) {
			player.vy = 1;
		}

		//Salt
		if (tocant_terra) { //Si estic al terra
			doblesalt = false;
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
				player.vy = -4;
				doblesalt = true;
			}
		}
		else {			//NO toco terra
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && (doblesalt || coyotejump)) {
				player.vy = -4;
				doblesalt = false;
				coyotejump = false;
				jumpRAnim.Reset();
				jumpLAnim.Reset();
			}
		}
		if (tocant_terra_abans && tocant_terra)
			coyotejump = true;

		tocant_terra_abans = tocant_terra;
		


		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS
		//COLISIONS
		tocant_terra = false;
		//abans de res colision coords
		app->map->Getcolision_coords(player.x, player.y);

		for (int i = 0; app->map->colision_coords[i] != nullptr; ++i) {
			if ((player.x + 64 + player.vx > app->map->colision_coords[i]->x) && (player.x + player.vx < app->map->colision_coords[i]->x + 32) &&
				(player.y + 64 + player.vy > app->map->colision_coords[i]->y) && (player.y + player.vy < app->map->colision_coords[i]->y + 32)) {

				//El player est� colisionant amb una o m�s tiles
				if ((player.x + 64 + player.vx > app->map->colision_coords[i]->x) && (player.x + player.vx < app->map->colision_coords[i]->x + 32) &&
					(player.y + 64 > app->map->colision_coords[i]->y) && (player.y < app->map->colision_coords[i]->y + 32)) {
					//Xoca pel costat
					player.vx = 0;
				}

				if ((player.x + 64 > app->map->colision_coords[i]->x) && (player.x < app->map->colision_coords[i]->x + 32) &&
					(player.y + 64 + player.vy > app->map->colision_coords[i]->y) && (player.y + player.vy < app->map->colision_coords[i]->y + 32)) {
					//xoc vertical
					if (player.vy >= 0) { //xoca amb el terra
						tocant_terra = true;
					}
					player.vy = 0;
				}
			}
		}
		//												COLISIONS COLISIONS
		//												COLISIONS COLISIONS

		//MOVIMENT
		player.x += player.vx;
		player.y += player.vy;
		player.vx = 0;

	}
	
	//GESTOR ANIMACIONS
	if (tocant_terra && (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)) {
		if (sentit) { //walking right
			if (currentFrogAnimation != &walkRAnim) {
				walkRAnim.Reset();
				currentFrogAnimation = &walkRAnim;
			}
		}
		else { //walking left
			if (currentFrogAnimation != &walkLAnim) {
				walkLAnim.Reset();
				currentFrogAnimation = &walkLAnim;
			}
		}
	}
	else if (tocant_terra) {
		if (sentit) { //idle right
			if (currentFrogAnimation != &idleRAnim) {
				idleRAnim.Reset();
				currentFrogAnimation = &idleRAnim;
			}
		}
		else { //idle left
			if (currentFrogAnimation != &idleLAnim) {
				idleLAnim.Reset();
				currentFrogAnimation = &idleLAnim;
			}
		}
	}
	else {//saltant
		if (sentit) {
			if (currentFrogAnimation != &jumpRAnim) {
				//only resets in double jump
				currentFrogAnimation = &jumpRAnim;
			}
		}
		else {
			if (currentFrogAnimation != &jumpLAnim) {
				//only resets in double jump
				currentFrogAnimation = &jumpLAnim;
			}
		}
	}

	//RENDER IMATGES
	
	//camera i l�mits de camera
	app->render->camera.x = 300 - player.x;
	app->render->camera.y = -50;			//350 - player.y

	if (app->render->camera.x > 0) {
		app->render->camera.x = 0;
	}
	if (app->render->camera.x < -17600) { //19200 - 1600
		app->render->camera.x = -17600;
	}

	//parallax
	if (app->render->camera.x > before_camera.x) {
		parallax2--;
		parallax1 -= 0.5;
		parallax3 -= 1.5;
	}
	else if (app->render->camera.x < before_camera.x) {
		parallax2++;
		parallax1 += 0.5;
		parallax3 += 1.5;
	}

	if (parallax2 > 1728) {
		parallax2 = 0;
	}
	else if (parallax2 < 0) {
		parallax2 = 1728;
	}

	if (parallax1 > 1728) {
		parallax1 = 0;
	}
	else if (parallax1 < 0) {
		parallax1 = 1728;
	}

	if (parallax3 > 1728) {
		parallax3 = 0;
	}
	else if (parallax3 < 0) {
		parallax3 = 1728;
	}

	//ImatgeFons Parallax
	app->render->DrawTexture(imgFons1, -app->render->camera.x, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons2, -app->render->camera.x - parallax1, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons2, -app->render->camera.x - parallax1 + 1728, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons3, -app->render->camera.x - parallax2, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons3, -app->render->camera.x - parallax2 + 1728, -app->render->camera.y, NULL, 1, 3);
	app->render->DrawTexture(imgFons4, -app->render->camera.x - parallax3, -app->render->camera.y - 70, NULL, 1, 3);
	app->render->DrawTexture(imgFons4, -app->render->camera.x - parallax3 + 1728, -app->render->camera.y - 70, NULL, 1, 3);

	//Draw decorations
	DrawDecorations(); //2 no es dibuixen

	//Draw map
	app->map->Draw();

	//Draw Granota
	currentFrogAnimation->Update();
	app->render->DrawTexture(granota, player.x, player.y, &currentFrogAnimation->GetCurrentFrame(), 1, 4);
	//
	
	// L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	//GODMODE
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		//GODMODE Activator
		godMode = !godMode;
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) {
		debug = !debug;
	}
	
	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		reset = true;
	}

	if (player.y > 2500 || player.x > 19000) {
		reset = true;
		app->scene_end->active = true;
		active = false;
	}


	SDL_Rect meleEnemicSpawn1{ app->moduleEnemy->meleEnemicSpawn1.x,app->moduleEnemy->meleEnemicSpawn1.y,50,50 };
	SDL_Rect meleEnemicSpawn2{ app->moduleEnemy->meleEnemicSpawn2.x,app->moduleEnemy->meleEnemicSpawn2.y,50,50 };
	SDL_Rect meleEnemicSpawn3{ app->moduleEnemy->meleEnemicSpawn3.x,app->moduleEnemy->meleEnemicSpawn3.y,50,50 };
	SDL_Rect meleEnemicSpawn4{ app->moduleEnemy->meleEnemicSpawn4.x,app->moduleEnemy->meleEnemicSpawn4.y,50,50 };
	SDL_Rect meleEnemicSpawn5{ app->moduleEnemy->meleEnemicSpawn5.x,app->moduleEnemy->meleEnemicSpawn5.y,50,50 };
	SDL_Rect meleEnemicSpawn6{ app->moduleEnemy->meleEnemicSpawn6.x,app->moduleEnemy->meleEnemicSpawn6.y,50,50 };
	SDL_Rect meleEnemicSpawn7{ app->moduleEnemy->meleEnemicSpawn7.x,app->moduleEnemy->meleEnemicSpawn7.y,50,50 };
	app->render->DrawRectangle(meleEnemicSpawn1, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn2, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn3, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn4, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn5, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn6, 255, 255, 255);
	app->render->DrawRectangle(meleEnemicSpawn7, 255, 255, 255);

	SDL_Rect sensorSpawn1 = {app->moduleEnemy->meleEnemicSpawn1.x-800,app->moduleEnemy->meleEnemicSpawn1.y-500, 1500,1000};
	spawnTimer++;
	LOG("SpawnTimer: %d", spawnTimer);

	if (player.x > sensorSpawn1.x && player.x < sensorSpawn1.w+sensorSpawn1.x) {
		if (spawnTimer >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn1.x, app->moduleEnemy->meleEnemicSpawn1.y));
			spawnTimer = 0;
		}
	}


	//Lista enemigos 
	p2List_item<MeleEnemic*>* storage1 = app->moduleEnemy->meleEnemic1List.getFirst();
	while (storage1 != NULL) {
		storage1->data->x++;
		SDL_Rect enemic={ storage1->data->x,storage1->data->y,50,50 };
		SDL_Rect enemicSensor = { storage1->data->x-250,storage1->data->y-130,500,300 };
		LOG("Enemic x: %d y: %d", storage1->data->x, storage1->data->y);
		app->render->DrawRectangle(enemic, 255, 255, 0);
		app->render->DrawRectangle(enemicSensor, 255, 200, 50);

		//Elimina los enemigos cuando el personaje entra dentro del sensor enemicSensor
		if (player.x > enemicSensor.x && player.x < enemicSensor.w + enemicSensor.x&&player.y<enemicSensor.h+enemicSensor.y&&player.y>enemicSensor.y) {
			MeleEnemic* b = storage1->data;
			storage1 = storage1->next;
			app->moduleEnemy->meleEnemic1List.del(app->moduleEnemy->meleEnemic1List.findNode(b));
			delete b;
		}
		if (storage1 != NULL) {
			storage1 = storage1->next;

		}

	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (debug)
		DebugDraw();

	LOG("Player x: %d y: %d", player.x, player.y);
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

//Carga la posicion del personaje NO SE USA EN ESTE CODIGO
bool Scene::LoadState(pugi::xml_node& configRenderer)
{

	player.x = configRenderer.child("player").attribute("x").as_int();
	player.y = configRenderer.child("player").attribute("y").as_int();

	return true;
}

//Guarda la posicion del personaje NO SE USA EN ESTE CODIGO
bool Scene::SaveState(pugi::xml_node& configRenderer) const
{
	pugi::xml_node player1 = configRenderer.child("player");

	player1.attribute("x").set_value(player.x);
	player1.attribute("y").set_value(player.y);

	return true;
}

//Dibuja los colliders
void Scene::DebugDraw()
{
	app->map->DrawColisions();

	//Dibuja los colliders cargado en ese momento
	for (int i = 0; app->map->colision_coords[i] != nullptr; ++i) {
		SDL_Rect rectCollider = {app->map->colision_coords[i]->x,app->map->colision_coords[i]->y,32,32 };
		app->render->DrawRectangle(rectCollider, 0, 70, 250,80);
	}
	//Dibuja el collider de la rana
	SDL_Rect rectPlayer = { player.x,player.y,64,64 };
	SDL_Rect sensorSpawn1 = { app->moduleEnemy->meleEnemicSpawn1.x - 800,app->moduleEnemy->meleEnemicSpawn1.y - 500, 1500,1000 };
	app->render->DrawRectangle(rectPlayer, 255, 255, 0, 80);
	app->render->DrawRectangle(sensorSpawn1, 255, 255, 0, 40);

}

void Scene::DrawDecorations() {
	app->render->DrawTexture(arbre1, 2800, 64, NULL, 1, 3);
	app->render->DrawTexture(arbre2, 14016, 400, NULL, 1, 3);
	app->render->DrawTexture(tronc1, 12320, 850, NULL, 1, 3);
	app->render->DrawTexture(cartell1, 1800, 485, NULL, 1, 3);
	app->render->DrawTexture(cartell5, 13420, 260, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 3648, 580, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 9856, 356, NULL, 1, 3);
	app->render->DrawTexture(cartell8, 15350, 580, NULL, 1, 3);
	app->render->DrawTexture(bush8, 1900, 754, NULL, 1, 3);
	app->render->DrawTexture(bush1, 4500, 790, NULL, 1, 3);
	app->render->DrawTexture(bush3, 8260, 790, NULL, 1, 3);
}
