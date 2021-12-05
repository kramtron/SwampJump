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

	obelisk = app->tex->Load("Assets/textures/obelisk/obeliskAlone.png");
	thunder = app->tex->Load("Assets/textures/thunder.png");
	menuEToEnter= app->tex->Load("Assets/textures/MenuInGame/obeliskMenuEToEnter.png");

	//Sprites Decoració
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
	staticRAnim.Empty();
	staticRAnim.PushBack({ 16, 48, 16, 16 });
	staticRAnim.loop = false;
	staticRAnim.speed = 1;

	staticLAnim.Empty();
	staticLAnim.PushBack({ 32, 48, 16, 16 });
	staticLAnim.loop = false;
	staticLAnim.speed = 1;

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
	
	thunderAnim.Empty();
	for (int i = 0; i < 13; i++) {
		thunderAnim.PushBack({ i * 64, 0, 64, 64 });
	}
	thunderAnim.loop = false;
	thunderAnim.pingpong = false;

	// ANIMACIONS

	app->modulescore->HpCreate(100, 400, 0);
	app->modulescore->HpCreate(200, 400, 0);
	app->modulescore->CoinCreate(300, 600, 0);

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

	if (app->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {
		obeliskTp = true;
	}

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
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		app->LoadGameRequest();//Cargar Datos
		loadPlayerData = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		app->SaveGameRequest();//Guardar Datos
	}
	
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
		//LOG("GODMODE OFF");
		LOG("DtScene: %.4f", dt);
		//PLAYER MOVE
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
 			player.vx = -player.v2x*dt;
			sentit = false;
		}

		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
			player.vx = player.v2x*dt;
			sentit = true;
		}
		//
		
		if (aceleration_timer <= 0) {
			player.vy += player.ay;
			aceleration_timer = 10;
			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) { //Aguantar el salt
				aceleration_timer = 25;
			}
		}
		else {
			aceleration_timer -= 1 * dt;
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
			if ((player.x + (player.w-4)  + player.vx > app->map->colision_coords[i]->x) && (player.x  + player.vx < (app->map->colision_coords[i]->x + 32)) &&
				(player.y + player.h  + player.vy > app->map->colision_coords[i]->y) && (player.y  + player.vy < app->map->colision_coords[i]->y + 32)) {

				//El player està colisionant amb una o més tiles
				if ((player.x + (player.w-4) + player.vx > app->map->colision_coords[i]->x) && (player.x + player.vx < (app->map->colision_coords[i]->x + 32)/2) &&
					(player.y + player.h > app->map->colision_coords[i]->y -1) && (player.y < app->map->colision_coords[i]->y + 32 + 1)) {
					//Xoca pel costat
					player.vx = 0;
				}
				else if ((player.x + player.vx > (app->map->colision_coords[i]->x+32)/2) && (player.x + player.vx < (app->map->colision_coords[i]->x + 32)) &&
					(player.y + player.h > app->map->colision_coords[i]->y  + 1) && (player.y < app->map->colision_coords[i]->y + 32 - 1)) {
					player.vx = 0;

				}

				if ((player.x + (player.w-4) > app->map->colision_coords[i]->x) && (player.x < app->map->colision_coords[i]->x + 32) &&
					(player.y + player.h + player.vy > app->map->colision_coords[i]->y) && (player.y + player.vy < app->map->colision_coords[i]->y + 32)) {
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
	
	//camera i límits de camera
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
		parallax2 -= 1*dt;
		parallax1 -= 0.5*dt;
		parallax3 -= 1.5*dt;
	}
	else if (app->render->camera.x < before_camera.x) {
		parallax2 += 1*dt;
		parallax1 += 0.5*dt;
		parallax3 += 1.5*dt;
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
	DrawDecorations();

	//Draw map
	app->map->Draw();
	
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

	//ObeliskDraw
	obeliskFluctuationAngle += 0.03f*dt;
	if (obeliskFluctuationAngle >= 360)
		obeliskFluctuationAngle = 1;
	obeliskFluctuation = (sin(obeliskFluctuationAngle) * 15.0f);

	//Draw Obelisk on diferents points
	app->render->DrawTexture(obelisk, checkPont1.x, checkPont1.y + obeliskFluctuation);
	app->render->DrawTexture(obelisk, checkPont2.x, checkPont2.y + obeliskFluctuation);
	app->render->DrawTexture(obelisk, checkPont3.x, checkPont3.y + obeliskFluctuation);
	app->render->DrawTexture(obelisk, checkPont4.x, checkPont4.y + obeliskFluctuation);
	app->render->DrawTexture(obelisk, checkPont5.x, checkPont5.y + obeliskFluctuation);

	SDL_Rect obelisk1Sensor = { checkPont1.x, checkPont1.y ,checkPont1.w, checkPont1.h };
	SDL_Rect obelisk2Sensor = { checkPont2.x, checkPont2.y ,checkPont2.w, checkPont2.h };
	SDL_Rect obelisk3Sensor = { checkPont3.x, checkPont3.y ,checkPont3.w, checkPont3.h };
	SDL_Rect obelisk4Sensor = { checkPont4.x, checkPont4.y ,checkPont4.w, checkPont4.h };
	SDL_Rect obelisk5Sensor = { checkPont5.x, checkPont5.y ,checkPont5.w, checkPont5.h };


	if (player.x > obelisk1Sensor.x && player.x < obelisk1Sensor.w + obelisk1Sensor.x && player.y<obelisk1Sensor.h + obelisk1Sensor.y && player.y>obelisk1Sensor.y) {
		insideObelisk1 = true;

		if (obelisk1Up) {
			app->SaveGameRequest();//Guardar Datos
			obelisk1Up = false;
		}
	}
	else {
		insideObelisk1 = false;
	}
	if (player.x > obelisk2Sensor.x && player.x < obelisk2Sensor.w + obelisk2Sensor.x && player.y<obelisk2Sensor.h + obelisk2Sensor.y && player.y>obelisk2Sensor.y) {
		insideObelisk2 = true;

		if (obelisk2Up) {
			app->SaveGameRequest();//Guardar Datos
			obelisk2Up = false;
		}
	}
	else {
		insideObelisk2 = false;

	}
	if (player.x > obelisk3Sensor.x && player.x < obelisk3Sensor.w + obelisk3Sensor.x && player.y<obelisk3Sensor.h + obelisk3Sensor.y && player.y>obelisk3Sensor.y) {
		insideObelisk3 = true;

		if (obelisk3Up) {
			app->SaveGameRequest();//Guardar Datos
			obelisk3Up = false;

		}
	}
	else {
		insideObelisk3 = false;

	}
	if (player.x > obelisk4Sensor.x && player.x < obelisk4Sensor.w + obelisk4Sensor.x && player.y<obelisk4Sensor.h + obelisk4Sensor.y && player.y>obelisk4Sensor.y) {
		insideObelisk4 = true;

		if (obelisk4Up) {
			app->SaveGameRequest();//Guardar Datos
			obelisk4Up = false;

		}
	}
	else {
		insideObelisk4 = false;

	}
	if (player.x > obelisk5Sensor.x && player.x < obelisk5Sensor.w + obelisk5Sensor.x && player.y<obelisk5Sensor.h + obelisk5Sensor.y && player.y>obelisk5Sensor.y) {
		insideObelisk5 = true;

		if (obelisk5Up){
			app->SaveGameRequest();//Guardar Datos
		obelisk5Up = false;

		}
	}
	else {
		insideObelisk5 = false;

	}
	SDL_Rect meleEnemicSpawn1={ app->moduleEnemy->meleEnemicSpawn1.x,app->moduleEnemy->meleEnemicSpawn1.y,50,50 };
	SDL_Rect meleEnemicSpawn2={ app->moduleEnemy->meleEnemicSpawn2.x,app->moduleEnemy->meleEnemicSpawn2.y,50,50 };
	SDL_Rect meleEnemicSpawn3={ app->moduleEnemy->meleEnemicSpawn3.x,app->moduleEnemy->meleEnemicSpawn3.y,50,50 };
	SDL_Rect meleEnemicSpawn4={ app->moduleEnemy->meleEnemicSpawn4.x,app->moduleEnemy->meleEnemicSpawn4.y,50,50 };
	SDL_Rect meleEnemicSpawn5={ app->moduleEnemy->meleEnemicSpawn5.x,app->moduleEnemy->meleEnemicSpawn5.y,50,50 };
	SDL_Rect meleEnemicSpawn6={ app->moduleEnemy->meleEnemicSpawn6.x,app->moduleEnemy->meleEnemicSpawn6.y,50,50 };
	SDL_Rect meleEnemicSpawn7={ app->moduleEnemy->meleEnemicSpawn7.x,app->moduleEnemy->meleEnemicSpawn7.y,50,50 };


	SDL_Rect sensorSpawn1 = { app->moduleEnemy->meleEnemicSpawn1.x - 800,app->moduleEnemy->meleEnemicSpawn1.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn2 = { app->moduleEnemy->meleEnemicSpawn2.x - 800,app->moduleEnemy->meleEnemicSpawn2.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn3 = { app->moduleEnemy->meleEnemicSpawn3.x - 800,app->moduleEnemy->meleEnemicSpawn3.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn4 = { app->moduleEnemy->meleEnemicSpawn4.x - 800,app->moduleEnemy->meleEnemicSpawn4.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn5 = { app->moduleEnemy->meleEnemicSpawn5.x - 800,app->moduleEnemy->meleEnemicSpawn5.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn6 = { app->moduleEnemy->meleEnemicSpawn6.x - 130,app->moduleEnemy->meleEnemicSpawn6.y - 100, 300,200 };
	SDL_Rect sensorSpawn7 = { app->moduleEnemy->meleEnemicSpawn7.x - 130,app->moduleEnemy->meleEnemicSpawn7.y - 100, 300,200 };

	//Se puede pasar a funciones para reducir espacio el el update
	spawnTimer1 = spawnTimer1 + (1.0f * dt);
	spawnTimer2 = spawnTimer2 + (1.0f * dt);
	spawnTimer3 = spawnTimer3 + (1.0f * dt);
	spawnTimer4 = spawnTimer4 + (1.0f * dt);
	spawnTimer5 = spawnTimer5 + (1.0f * dt);
	spawnTimer6 = spawnTimer6 + (1.0f * dt);
	spawnTimer7 = spawnTimer7 + (1.0f * dt);
	spawn1FlyEnemicTimer = spawn1FlyEnemicTimer + (1.0f * dt);
	spawn2FlyEnemicTimer = spawn2FlyEnemicTimer + (1.0f * dt);
	spawn3FlyEnemicTimer = spawn3FlyEnemicTimer + (1.0f * dt);
	spawn4FlyEnemicTimer = spawn4FlyEnemicTimer + (1.0f * dt);
	spawn5FlyEnemicTimer = spawn5FlyEnemicTimer + (1.0f * dt);
	spawn6FlyEnemicTimer = spawn6FlyEnemicTimer + (1.0f * dt);
	spawn7FlyEnemicTimer = spawn7FlyEnemicTimer + (1.0f * dt);

	
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		spawnTimer1 = 3000;
		spawnTimer2 = 3000;
		spawnTimer3 = 3000;
		spawnTimer4 = 3000;
		spawnTimer5 = 3000;
		spawnTimer6 = 3000;
		spawnTimer7 = 3000;
	}
	//Son los 7 sensores que se usan para colocar enemigos mele en la lista
	if (player.x > sensorSpawn1.x && player.x < sensorSpawn1.w + sensorSpawn1.x && player.y<sensorSpawn1.h + sensorSpawn1.y && player.y>sensorSpawn1.y) {
		if (spawnTimer1 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn1.x, app->moduleEnemy->meleEnemicSpawn1.y,1));
			spawnTimer1 = 0;
		}
	}
	if (player.x > sensorSpawn2.x && player.x < sensorSpawn2.w + sensorSpawn2.x && player.y<sensorSpawn2.h + sensorSpawn2.y && player.y>sensorSpawn2.y) {
		if (spawnTimer2 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn2.x, app->moduleEnemy->meleEnemicSpawn2.y, 2));
			spawnTimer2 = 0;
		}
	}
	if (player.x > sensorSpawn3.x && player.x < sensorSpawn3.w + sensorSpawn3.x && player.y<sensorSpawn3.h + sensorSpawn3.y && player.y>sensorSpawn3.y) {
		if (spawnTimer3 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn3.x, app->moduleEnemy->meleEnemicSpawn3.y, 3));
			spawnTimer3 = 0;
		}
	}
	if (player.x > sensorSpawn4.x && player.x < sensorSpawn4.w + sensorSpawn4.x && player.y<sensorSpawn4.h + sensorSpawn4.y && player.y>sensorSpawn4.y) {
		if (spawnTimer4 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn4.x, app->moduleEnemy->meleEnemicSpawn4.y, 4));
			spawnTimer4 = 0;
		}
	}
	if (player.x > sensorSpawn5.x && player.x < sensorSpawn5.w + sensorSpawn5.x && player.y<sensorSpawn5.h + sensorSpawn5.y && player.y>sensorSpawn5.y) {
		if (spawnTimer5 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn5.x, app->moduleEnemy->meleEnemicSpawn5.y, 5));
			spawnTimer5 = 0;
		}
	}
	if (player.x > sensorSpawn6.x && player.x < sensorSpawn6.w + sensorSpawn6.x && player.y<sensorSpawn6.h + sensorSpawn6.y && player.y>sensorSpawn6.y) {
		if (spawnTimer6 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn6.x, app->moduleEnemy->meleEnemicSpawn6.y, 6));
			spawnTimer6 = 0;
		}
	}
	if (player.x > sensorSpawn7.x && player.x < sensorSpawn7.w + sensorSpawn7.x && player.y<sensorSpawn7.h + sensorSpawn7.y && player.y>sensorSpawn7.y) {
		if (spawnTimer7 >= 3000) {
			app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->meleEnemicCreator(app->moduleEnemy->meleEnemicSpawn7.x, app->moduleEnemy->meleEnemicSpawn7.y, 7));
			spawnTimer7 = 0;
		}
	}

	//Disparo player
	
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN && !boolDisparo) {
		boolDisparo = true;
		if(sentit){
			//disparo.x = player.x + 68;
			disparo.x = 68;
			disparo.y = player.y + 5;
		}
		else {
			//disparo.x = player.x-5;
			disparo.x = -5;
			disparo.y = player.y + 5;
		}
		
	}

	//Draw PickUps
	app->modulescore->DrawPickUps();

	if (boolDisparo) {
		if (sentit) {
			disparo.y = player.y + 30;
			if (disparo.x < 200 && disparoRetroceso) {
				disparoRetroceso = true;
			}
			else {
				disparoRetroceso = false;
			}
			if (disparoRetroceso) {
				disparo.x += 8*dt;

			}
			else if (!disparoRetroceso) {
				disparo.x -= 8*dt;
			}
			if (disparo.x <  60) {
				boolDisparo = false;
				disparoRetroceso = true;
			}
			
		}
		else {
			disparo.y = player.y + 30;
			if (disparo.x > -150  && disparoRetroceso) {
				disparoRetroceso = true;
			}
			else {
				disparoRetroceso = false;
			}
			if (disparoRetroceso) {
				disparo.x -= 8*dt;
			}
			else if (!disparoRetroceso) {
				disparo.x += 8*dt;
			}
			if (disparo.x > 10) {
				boolDisparo = false;
				disparoRetroceso = true;
			}
		}
		if (sentit) {
			currentFrogAnimation = &staticRAnim;
		}
		else {
			currentFrogAnimation = &staticLAnim;
		}
		disparoPlayer.x = player.x + disparo.x;
		disparoPlayer.y = disparo.y;
		
		//Draw Tongue
		if (sentit) {
			//app->render->DrawTexture(granota, disparoPlayer.x - shotPercent - 32, disparo.y - 10, &tongueRightRectangle, 1.0f, 3.0f); //tongue printing
			SDL_Rect tongueRight = { 58, 23, 6, 7 };
			SDL_Rect tongueBody = { 40, 18, (disparo.x / 3.0f) - 10, 3 };
			app->render->DrawTexture(granota, player.x + 32, disparoPlayer.y - 5, &tongueBody, 1.0f, 3.0f);
			app->render->DrawTexture(granota, disparoPlayer.x, disparoPlayer.y - 10, &tongueRight, 1.0f, 3.0f);
		}
		else{	//left tongue
			SDL_Rect tongueLeft = { 32, 16, 6, 7 };
			SDL_Rect tongueBody = { 40, 18, (-disparo.x / 3.0f), 3 };
			app->render->DrawTexture(granota, disparoPlayer.x, disparoPlayer.y - 5, &tongueBody, 1.0f, 3.0f);
			app->render->DrawTexture(granota, disparoPlayer.x, disparo.y - 10, &tongueLeft, 1.0f, 3.0f); //tongue printing
		}

		

		//Draw Collider Tongue
		/*SDL_Rect disparoRectangle = { disparoPlayer.x, disparo.y, 10, 10 };
		app->render->DrawRectangle(disparoRectangle, 255, 0, 0);*/

	}
	

	//Draw Granota
	currentFrogAnimation->Update();
	app->render->DrawTexture(granota, player.x, player.y, &currentFrogAnimation->GetCurrentFrame(), 1, 4);
	//

	//Thunder Animation
	if (obeliskTp) {
		thunderAnim.speed = 0.20f * dt;

		app->render->DrawTexture(thunder, player.x - 64, player.y - 116, &thunderAnim.GetCurrentFrame(), 1.0f, 3.0f);
		thunderAnim.Update();

		if (thunderAnim.HasFinished()) {
			obeliskTp = false;
			thunderAnim.Reset();
		}
	}

	p2List_item<MeleEnemic*>* storage1 = app->moduleEnemy->meleEnemic1List.getFirst();
	while (storage1 != NULL) {
		if (storage1->data->spawnPlace == 1) {

			if (app->scene->player.x > sensorSpawn1.x && app->scene->player.x < sensorSpawn1.w + sensorSpawn1.x) {
				if (spawn1FlyEnemicTimer >= 1500) {
					if (storage1->data->enemicType == 0) {
						app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->flyEnemicCreator(storage1->data->x, storage1->data->y - 80, 1));
						spawn1FlyEnemicTimer = 0;
					}

				}
			}
			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 2850) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 3354) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			if (storage1->data->enemicType == 1) {

				if (storage1->data->x < 2850) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 3354) {
					storage1->data->movimentFlyEnemic = false;
				}
			}
		}
		if (storage1->data->spawnPlace == 2) {

			if (app->scene->player.x > sensorSpawn2.x && app->scene->player.x < sensorSpawn2.w + sensorSpawn2.x) {
				if (spawn2FlyEnemicTimer >= 1500) {
					if (storage1->data->enemicType == 0) {
						app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->flyEnemicCreator(storage1->data->x, storage1->data->y - 40, 2));
						spawn2FlyEnemicTimer = 0;
					}

				}
			}
			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 5439) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 5773) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			if (storage1->data->enemicType == 1) {

				if (storage1->data->x < 5439) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 5773) {
					storage1->data->movimentFlyEnemic = false;
				}
			}
		}
		if (storage1->data->spawnPlace == 3) {

			if (app->scene->player.x > sensorSpawn3.x && app->scene->player.x < sensorSpawn3.w + sensorSpawn3.x) {
				if (spawn3FlyEnemicTimer >= 1500) {
					if (storage1->data->enemicType == 0) {
						app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->flyEnemicCreator(storage1->data->x, storage1->data->y - 40, 3));
						spawn3FlyEnemicTimer = 0;
					}

				}
			}
			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 6559) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 6785) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			if (storage1->data->enemicType == 1) {

				if (storage1->data->x < 6559) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 6785) {
					storage1->data->movimentFlyEnemic = false;
				}
			}
		}
		if (storage1->data->spawnPlace == 4) {

			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 8095) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 8350) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			
		}
		if (storage1->data->spawnPlace == 5) {

			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 9125) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x >9555) {
					storage1->data->movimentMeleEnemic = false;
				}
			}

		}
		if (storage1->data->spawnPlace == 6) {

			if (app->scene->player.x > sensorSpawn6.x && app->scene->player.x < sensorSpawn6.w + sensorSpawn6.x) {
				if (spawn6FlyEnemicTimer >= 1500) {
					if (storage1->data->enemicType == 0) {
						app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->flyEnemicCreator(storage1->data->x, storage1->data->y - 30, 6));
						spawn6FlyEnemicTimer = 0;
					}

				}
			}
			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 11976) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 12280) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			if (storage1->data->enemicType == 1) {

				if (storage1->data->x < 11976) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 12280) {
					storage1->data->movimentFlyEnemic = false;
				}
			}
		}
		if (storage1->data->spawnPlace == 7) {

			if (app->scene->player.x > sensorSpawn7.x && app->scene->player.x < sensorSpawn7.w + sensorSpawn7.x) {
				if (spawn7FlyEnemicTimer >= 1500) {
					if (storage1->data->enemicType == 0) {
						app->moduleEnemy->meleEnemic1List.add(app->moduleEnemy->flyEnemicCreator(storage1->data->x, storage1->data->y - 30, 7));
						spawn7FlyEnemicTimer = 0;
					}

				}
			}
			if (storage1->data->enemicType == 0) {

				if (storage1->data->x < 12385) {
					storage1->data->movimentMeleEnemic = true;
				}
				else if (storage1->data->x > 12705) {
					storage1->data->movimentMeleEnemic = false;
				}
			}
			if (storage1->data->enemicType == 1) {

				if (storage1->data->x < 12385) {
					storage1->data->movimentFlyEnemic = true;
				}
				else if (storage1->data->x > 12705) {
					storage1->data->movimentFlyEnemic = false;
				}
			}
		}
			SDL_Rect enemic = { storage1->data->x,storage1->data->y,app->moduleEnemy->normalEnemicsWH.w,app->moduleEnemy->normalEnemicsWH.h };
			//LOG("Enemic x: %d y: %d", storage1->data->x, storage1->data->y);
			app->render->DrawRectangle(enemic, 255, 255, 0);

			//Ataque
			if (storage1->data->meleLeftAtackBool) {
				SDL_Rect meleLeftAtackRect = { storage1->data->x - 25,storage1->data->y + 10,25,25 };
				app->render->DrawRectangle(meleLeftAtackRect, 255, 0, 0);
			}
			if (storage1->data->meleRightAtackBool) {
				SDL_Rect meleRightAtackRect = { storage1->data->x + storage1->data->w ,storage1->data->y + 10,25,25 };
				app->render->DrawRectangle(meleRightAtackRect, 255, 0, 0);
			}


			storage1 = storage1->next;
			
	}
	if (insideObelisk1||insideObelisk2||insideObelisk3||insideObelisk4||insideObelisk5) {
		ObeliskMenuController();
		if (insideObelisk1&&!enterMenu) {
			app->render->DrawTexture(menuEToEnter, obelisk1Sensor.x - 50, obelisk1Sensor.y - 30);

		}
		else if (insideObelisk2&&!enterMenu) {
			app->render->DrawTexture(menuEToEnter, obelisk2Sensor.x - 50, obelisk2Sensor.y - 30);

		}
		else if (insideObelisk3&&!enterMenu) {
			app->render->DrawTexture(menuEToEnter, obelisk3Sensor.x - 50, obelisk3Sensor.y - 30);

		}
		else if (insideObelisk4&&!enterMenu) {
			app->render->DrawTexture(menuEToEnter, obelisk4Sensor.x - 50, obelisk4Sensor.y - 30);

		}
		else if (insideObelisk5&&!enterMenu) {
			app->render->DrawTexture(menuEToEnter, obelisk5Sensor.x - 50, obelisk5Sensor.y - 30);

		}
	}
	LOG("Player x: %f Player y: %f", player.x, player.y);
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

	//LOG("Player x: %d y: %d", player.x, player.y);
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


	return true;
}

bool Scene::LoadPlayerData(pugi::xml_node& playerData) {

	player.x = playerData.attribute("x").as_float();
	player.y = playerData.attribute("y").as_float();
	player.w = playerData.attribute("width").as_float();
	player.h = playerData.attribute("heigth").as_float();
	player.v2x = playerData.attribute("xVelocity").as_float();
	player.v2y = playerData.attribute("yVelocity").as_float();
	player.actualPlayerHp = playerData.attribute("actualPlayerHp").as_float();
	player.playerHp = playerData.attribute("playerHp").as_float();
	player.playerDamage = playerData.attribute("playerDamage").as_float();

	return true;
}
bool Scene::LoadScene1Data(pugi::xml_node& scene1Data) {

	checkPont1.x = scene1Data.child("checkPoint1").attribute("x").as_float();
	checkPont1.y = scene1Data.child("checkPoint1").attribute("y").as_float();
	checkPont1.w = scene1Data.child("checkPoint1").attribute("width").as_float();
	checkPont1.h = scene1Data.child("checkPoint1").attribute("height").as_float();
	insideObelisk1= scene1Data.child("checkPoint1").attribute("insideObelisk").as_bool();

	checkPont2.x = scene1Data.child("checkPoint2").attribute("x").as_float();
	checkPont2.y = scene1Data.child("checkPoint2").attribute("y").as_float();
	checkPont2.w = scene1Data.child("checkPoint2").attribute("width").as_float();
	checkPont2.h = scene1Data.child("checkPoint2").attribute("height").as_float();
	insideObelisk2 = scene1Data.child("checkPoint2").attribute("insideObelisk").as_bool();


	checkPont3.x = scene1Data.child("checkPoint3").attribute("x").as_float();
	checkPont3.y = scene1Data.child("checkPoint3").attribute("y").as_float();
	checkPont3.w = scene1Data.child("checkPoint3").attribute("width").as_float();
	checkPont3.h = scene1Data.child("checkPoint3").attribute("height").as_float();
	insideObelisk3 = scene1Data.child("checkPoint3").attribute("insideObelisk").as_bool();


	checkPont4.x = scene1Data.child("checkPoint4").attribute("x").as_float();
	checkPont4.y = scene1Data.child("checkPoint4").attribute("y").as_float();
	checkPont4.w = scene1Data.child("checkPoint4").attribute("width").as_float();
	checkPont4.h = scene1Data.child("checkPoint4").attribute("height").as_float();
	insideObelisk4 = scene1Data.child("checkPoint4").attribute("insideObelisk").as_bool();


	checkPont5.x = scene1Data.child("checkPoint5").attribute("x").as_float();
	checkPont5.y = scene1Data.child("checkPoint5").attribute("y").as_float();
	checkPont5.w = scene1Data.child("checkPoint5").attribute("width").as_float();
	checkPont5.h = scene1Data.child("checkPoint5").attribute("height").as_float();
	insideObelisk5 = scene1Data.child("checkPoint5").attribute("insideObelisk").as_bool();


	obelisk1Up = scene1Data.child("obelisksUp").attribute("obelisk1Up").as_bool();
	obelisk2Up = scene1Data.child("obelisksUp").attribute("obelisk2Up").as_bool();
	obelisk3Up = scene1Data.child("obelisksUp").attribute("obelisk3Up").as_bool();
	obelisk4Up = scene1Data.child("obelisksUp").attribute("obelisk4Up").as_bool();
	obelisk5Up = scene1Data.child("obelisksUp").attribute("obelisk5Up").as_bool();
	return true;
}
//Guarda la posicion del personaje NO SE USA EN ESTE CODIGO
bool Scene::SaveState(pugi::xml_node& playerData) const
{
	//va bien
	pugi::xml_node player1 = playerData;

	player1.attribute("x").set_value(player.x);
	player1.attribute("y").set_value(player.y);
	player1.attribute("actualPlayerHp").set_value(player.actualPlayerHp);

	return true;
}
bool Scene::SaveScene1State(pugi::xml_node& scene1Data) const {

	pugi::xml_node scene1 = scene1Data;

	scene1Data.child("obelisksUp").attribute("obelisk1Up").set_value(obelisk1Up);
	scene1Data.child("obelisksUp").attribute("obelisk2Up").set_value(obelisk2Up);
	scene1Data.child("obelisksUp").attribute("obelisk3Up").set_value(obelisk3Up);
	scene1Data.child("obelisksUp").attribute("obelisk4Up").set_value(obelisk4Up);
	scene1Data.child("obelisksUp").attribute("obelisk5Up").set_value(obelisk5Up);

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
	SDL_Rect sensorSpawn2 = { app->moduleEnemy->meleEnemicSpawn2.x - 800,app->moduleEnemy->meleEnemicSpawn2.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn3 = { app->moduleEnemy->meleEnemicSpawn3.x - 800,app->moduleEnemy->meleEnemicSpawn3.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn4 = { app->moduleEnemy->meleEnemicSpawn4.x - 800,app->moduleEnemy->meleEnemicSpawn4.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn5 = { app->moduleEnemy->meleEnemicSpawn5.x - 800,app->moduleEnemy->meleEnemicSpawn5.y - 500, 1500,1000 };
	SDL_Rect sensorSpawn6 = { app->moduleEnemy->meleEnemicSpawn6.x - 130,app->moduleEnemy->meleEnemicSpawn6.y - 100, 300,200 };
	SDL_Rect sensorSpawn7 = { app->moduleEnemy->meleEnemicSpawn7.x - 130,app->moduleEnemy->meleEnemicSpawn7.y - 100, 300,200 };

	app->render->DrawRectangle(rectPlayer, 255, 255, 0, 80);
	app->render->DrawRectangle(sensorSpawn1, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn2, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn3, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn4, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn5, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn6, 255, 255, 0, 40);
	app->render->DrawRectangle(sensorSpawn7, 255, 255, 0, 40);


	p2List_item<MeleEnemic*>* storage1 = app->moduleEnemy->meleEnemic1List.getFirst();
	while (storage1 != NULL) {

		SDL_Rect enemicSensor = { storage1->data->x - 250,storage1->data->y - 130,500,300 };
		SDL_Rect atackMeleEnemicSensor = { storage1->data->x-25 ,storage1->data->y-25 ,storage1->data->w + 50,storage1->data->h+50};
		app->render->DrawRectangle(enemicSensor, 255, 200, 50, 40);
		app->render->DrawRectangle(atackMeleEnemicSensor, 255, 255, 255,40);
		storage1 = storage1->next;
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

	//Sensores de los obeliskos
	SDL_Rect obelisk1Sensor = { checkPont1.x, checkPont1.y ,checkPont1.w, checkPont1.h };
	SDL_Rect obelisk2Sensor = { checkPont2.x, checkPont2.y ,checkPont2.w, checkPont2.h };
	SDL_Rect obelisk3Sensor = { checkPont3.x, checkPont3.y ,checkPont3.w, checkPont3.h };
	SDL_Rect obelisk4Sensor = { checkPont4.x, checkPont4.y ,checkPont4.w, checkPont4.h };
	SDL_Rect obelisk5Sensor = { checkPont5.x, checkPont5.y ,checkPont5.w, checkPont5.h };

	app->render->DrawRectangle(obelisk1Sensor, 255, 255, 255, 40);
	app->render->DrawRectangle(obelisk2Sensor, 255, 255, 255, 40);
	app->render->DrawRectangle(obelisk3Sensor, 255, 255, 255, 40);
	app->render->DrawRectangle(obelisk4Sensor, 255, 255, 255, 40);
	app->render->DrawRectangle(obelisk5Sensor,255,255,255,40);


	app->modulescore->DebugDraw();
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

void Scene::ObeliskMenuController() {
	//Zona para controlar el menu de los obeliscos que se usaran para que el jugador se transporte entre ellos
	//Primero imprimir sprite de pulsar E para entrar

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		enterMenu = !enterMenu;
	}
	
	if (enterMenu) {
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			if (menuPlace <= 5) {
				menuPlace++;
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
			if (menuPlace > 1) {
				menuPlace--;
			}
		}
		
		
		//Imprimir sprite del menu para seleccionar el sitio donde te quieras tepear

		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
			obeliskTp = true;
		}

		if (obeliskTp) {
			if (thunderAnim.GetCurrentFrame().x == 320) {
				switch (menuPlace) {
				case 1:
					if (!obelisk1Up) {
						player.x = checkPont1.x+36;
						player.y = checkPont1.y + (checkPont1.h / 2);
						enterMenu = false;
						menuPlace = 1;

					}
					else {
						//Imprimir Obelisco No conseguido
						LOG("Obleisco no conseguido");
					}
				break;

				case 2:
					if (!obelisk2Up) {
						player.x = checkPont2.x+36;
						player.y = checkPont2.y + (checkPont2.h / 2);
						enterMenu = false;
						menuPlace = 1;
					}
					else {
						//Imprimir Obelisco No conseguido
						LOG("Obleisco no conseguido");
					}
				break;

				case 3:
					if (!obelisk3Up) {
						player.x = checkPont3.x+36;
						player.y = checkPont3.y + (checkPont3.h / 2);
						enterMenu = false;
						menuPlace = 1;
					}
					else {
						//Imprimir Obelisco No conseguido
						LOG("Obleisco no conseguido");
					}
				break;

				case 4:
					if (!obelisk4Up) {
						player.x = checkPont4.x+36;
						player.y = checkPont4.y + (checkPont4.h / 2);
						enterMenu = false;
						menuPlace = 1;
					}
					else {
						//Imprimir Obelisco No conseguido
						LOG("Obleisco no conseguido");
					}
				break;

				case 5:
					if (!obelisk5Up) {
						player.x = checkPont5.x+36;
						player.y = checkPont5.y + (checkPont5.h / 2);
						enterMenu = false;
						menuPlace = 1;
					}
					else {
						//Imprimir Obelisco No conseguido
						LOG("Obleisco no conseguido");
					}
				break;
				}
			}
		}
	}

	LOG("Menu Place: %d ", menuPlace);

}
