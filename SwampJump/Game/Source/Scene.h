#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

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

	void DrawDecorations();

	bool debug = false;

	bool godMode = false;

	bool reset = false;

	struct player_struct
	{
		int x = 300;
		int y = 300;
		int vx = 0;
		int vy = 0;
		int ay = 1;
	}player;
	iPoint before_camera;
	
	int aceleration_timer = 0;
	bool doblesalt = false;
	bool coyotejump = false;
	bool tocant_terra_abans = false;
	bool tocant_terra = false;
	bool sentit = true; //dreta true, esquerra false
	int spawnTimer = 3000;

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

private:
	SDL_Texture* imgFons1 = nullptr;
	SDL_Texture* imgFons2 = nullptr;
	SDL_Texture* imgFons3 = nullptr;
	SDL_Texture* imgFons4 = nullptr;
	SDL_Texture* granota = nullptr;

	SDL_Texture* arbre1 = nullptr;
	SDL_Texture* arbre2 = nullptr;
	SDL_Texture* tronc1 = nullptr;
	SDL_Texture* cartell1 = nullptr;
	SDL_Texture* cartell5 = nullptr;
	SDL_Texture* cartell8 = nullptr;
	SDL_Texture* bush1 = nullptr;
	SDL_Texture* bush3 = nullptr;
	SDL_Texture* bush8 = nullptr;

	float parallax1 = 0;
	int parallax2 = 0;
	float parallax3 = 0;
	
	Animation* currentFrogAnimation = nullptr;
	Animation idleRAnim;
	Animation idleLAnim;
	Animation jumpRAnim;
	Animation jumpLAnim;
	Animation walkRAnim;
	Animation walkLAnim;
};

#endif // __SCENE_H__