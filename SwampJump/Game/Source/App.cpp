#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Scene_Intro.h"
#include "Scene_Logo.h"
#include "ModuleEnemy.h"
#include "ModuleScore.h"
#include "Scene_END.h"
#include "Scene_Win.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	win = new Window();
	input = new Input();
	render = new Render();
	tex = new Textures();
	audio = new Audio();
	scene_logo = new Scene_Logo();
	moduleEnemy = new ModuleEnemy();
	modulescore = new ModuleScore();
	scene_intro = new Scene_Intro();
	scene = new Scene();
	scene_end = new Scene_END();
	scene_win = new Scene_Win();
	map = new Map();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(scene_logo);
	AddModule(scene_intro);
	AddModule(moduleEnemy);
	AddModule(modulescore);
	AddModule(scene);
	AddModule(scene_end);
	AddModule(scene_win);
	AddModule(map);

	// Render last to swap buffer
	AddModule(render);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		// L01: DONE 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
	}

	if (ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			// L01: DONE 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	LoadGame();

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

		if (ret == true)
			ret = PreUpdate();


		if (ret == true)
			ret = DoUpdate();
				
		if (ret == true)
			ret = PostUpdate();

		FinishUpdate();


	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");

	return ret;
}




pugi::xml_node App::LoadGame_Data(pugi::xml_document& configSaveGame)const {
	pugi::xml_node ret2;

	pugi::xml_parse_result result2 = configSaveGame.load_file(SAVE_STATE_FILENAME);

	if (result2 == NULL) {
		LOG("could not load xml file: %s. pugi error: %s", SAVE_STATE_FILENAME, result2.description());
	}
	else {
		ret2 = configSaveGame.child("game_state");
	}
	return ret2;
}
// ---------------------------------------------
void App::PrepareUpdate()
{
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) LoadGame();
	if (saveGameRequested == true) SaveGame();
	if (app->scene->loadPlayerData == true)LoadGame();

}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest()//Es loadGameRequest
{

	bool ret = false;
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist
	loadGameRequested = true;
}

// ---------------------------------------
void App::SaveGameRequest() const
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	saveGameRequested = true;
}

// ---------------------------------------
// L02: TODO 5: Create a method to actually load an xml file
// then call all the modules to load themselves
bool App::LoadGame()
{
	bool ret = false;

	configSaveLoad = LoadGame_Data(configSaveGame);
	loadConfig = LoadConfig(configFile2);

	if (configSaveLoad.empty() == false) {

		ret = true;

		//Carga la posicion del personaje y de la camara
		if (loadGameRequested) {

			configRenderer = configSaveLoad.child("renderer");
			app->scene->LoadState(configRenderer);
			loadGameRequested = false;

		}

		//Carga la posicion de los diferentes spawn de los enemigos mele
		if (app->moduleEnemy->loadMeleEnemicSpawn) {

			configMeleEnemicSpawn = configSaveLoad.child("meleEnemicSpawn");
			app->moduleEnemy->LoadMeleEnemicSpawn(configMeleEnemicSpawn);
			app->moduleEnemy->loadMeleEnemicSpawn = false;

		}
		if (app->moduleEnemy->loadEnemicData) {

			configEnemicData = configSaveLoad.child("enemicsData");
			app->moduleEnemy->LoadEnemicsData(configEnemicData);
			app->moduleEnemy->loadEnemicData = false;

		}
		if (app->scene->loadPlayerData) {

			configPlayerData = configSaveLoad.child("player");
			app->scene->LoadPlayerData(configPlayerData);
			app->scene->loadPlayerData = false;

		}
		if (app->scene->loadScene1Data) {

			configScene1Data = configSaveLoad.child("scene1");
			app->scene->LoadScene1Data(configScene1Data);
			app->scene->loadScene1Data = false;

		}
		if (app->modulescore->loadScoreData) {
			configScoreData = configSaveLoad.child("applePointSpawn");
			app->modulescore->LoadPickUpsSpawn(configScoreData);
			app->modulescore->loadScoreData = false;
		}
		if (app->modulescore->loadPointsData) {
			configPointsData = configSaveLoad.child("points");
			app->modulescore->LoadPointsData(configPointsData);
			app->modulescore->loadPointsData = false;

		}
		if (app->modulescore->loadHpData) {
			configHpData = configSaveLoad.child("hpPickUp");
			app->modulescore->LoadHpData(configHpData);
			app->modulescore->loadHpData = false;

		}
	}
	if(loadConfig.empty()==false)
		if (app->scene_intro->loadPreConfig) {
			configAudio = loadConfig.child("audio");
			configScreen = loadConfig.child("window");
			configVsync = loadConfig.child("renderer");
			app->scene_intro->LoadGameConfig(configAudio, configScreen, configVsync);
		}
	


	return ret;
}

// L02: TODO 7: Implement the xml save method for current state
bool App::SaveGame() 
{
	bool ret = true;

	configSaveLoad = LoadGame_Data(configSaveGame);
	loadConfig = LoadConfig(configFile2);

	if (configSaveLoad.empty() == false) {
		ret = true;
		
		//app->render->SaveState(configRenderer);
		app->scene->SaveState(configPlayerData);//Guardado de los datos del player
		app->scene->SaveScene1State(configScene1Data);//Guardado de los datos de la escena 1. Por el momento solo guarda si estan activados los obeliscos

		configSaveGame.save_file(SAVE_STATE_FILENAME);


	}
	if (loadConfig.empty() == false) {
		app->scene_intro->SaveGameConfig(configAudio, configScreen, configVsync);
		configFile2.save_file(CONFIG_FILENAME);
	}
	saveGameRequested = false;

	return ret;
}



