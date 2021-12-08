#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene_Logo;
class Scene_Intro;
class ModuleEnemy;
class ModuleScore;
class Scene;
class Scene_END;
class Map;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();//Es LoadGameRequest
	void SaveGameRequest() const;
	void SetDt(float t) {
		this->dt = t;
	}
private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;
	//Load Save_game file
	pugi::xml_node LoadGame_Data(pugi::xml_document&) const;


	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGame();
	bool SaveGame();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene_Logo* scene_logo;
	ModuleEnemy* moduleEnemy;
	ModuleScore* modulescore;
	Scene_Intro* scene_intro;
	Scene* scene;
	Scene_END* scene_end;
	Map* map;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;


	pugi::xml_document configSaveGame;
	pugi::xml_node configSaveLoad;
	pugi::xml_node configRenderer;
	pugi::xml_node configMeleEnemicSpawn;
	pugi::xml_node configEnemicData;
	pugi::xml_node confighpPickUp;
	pugi::xml_node configPoints;
	pugi::xml_node configPlayerData;
	pugi::xml_node configScene1Data;
	pugi::xml_node configScoreData;


	uint frames;
	float dt;

	mutable bool saveGameRequested;
	bool loadGameRequested;
};

extern App* app;

#endif	// __APP_H__