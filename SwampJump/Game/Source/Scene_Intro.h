#ifndef __SCENE_INTRO_H__
#define __SCENE_INTRO_H__

#include "Module.h"

struct SDL_Texture;

class Scene_Intro : public Module
{
public:

	Scene_Intro();

	// Destructor
	virtual ~Scene_Intro();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void DebugDraw();

	int opcion = 0;

	bool settingsMenu = false;
	bool audioMenu = false;
	bool screenMenu = false;
	bool creditsMenu = false;
	int settingsOption=0;
	int volumeOption=1;

	

	bool loadPreConfig = true;

	bool LoadGameConfig(pugi::xml_node&, pugi::xml_node&, pugi::xml_node&);

	bool SaveGameConfig(pugi::xml_node&, pugi::xml_node&, pugi::xml_node&) const;

private:

	//Menu
	
	SDL_Texture* mainMenuScreen = nullptr;
	SDL_Texture* playSelected = nullptr;
	SDL_Texture* newGameSelected = nullptr;
	SDL_Texture* settingsSelected = nullptr;
	SDL_Texture* exitSelected = nullptr;

	SDL_Texture* defaultSettingsMenu = nullptr;
	SDL_Texture* xCircle = nullptr;
	SDL_Texture* xCircleSelected = nullptr;


	//Audio Menu
	SDL_Texture* audioSelected = nullptr;
	SDL_Texture* fxBar = nullptr;
	SDL_Texture* musicBar = nullptr;
	SDL_Texture* fxSelectedZone = nullptr;
	SDL_Texture* musicSelectedZone = nullptr;
	SDL_Texture* fxCircle = nullptr;
	SDL_Texture* musicCircle = nullptr;

	//Screen Menu
	SDL_Texture* screenSelected = nullptr;
	SDL_Texture* fullScreenTrue = nullptr;
	SDL_Texture* vSyncTrue = nullptr;
	SDL_Texture* fullScreenSelected = nullptr;
	SDL_Texture* vSyncSelected = nullptr;

	//Credits Menu
	SDL_Texture* creditsSelected = nullptr;


	float fxCircle_X = 1000;
	float musicCircle_X = 1000;


	SDL_Rect RectMenu1;
	SDL_Rect RectMenu2;

};


#endif // __SCENE_INTRO_H__