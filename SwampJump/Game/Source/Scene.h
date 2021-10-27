#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

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

	bool debug = false;

	bool godMode = false;

	bool reset = false;

	int timer = 0;

	struct player
	{
		int x = 300;
		int y = 300;
		int vx = 0;
		int vy = 0;
		int ay = 1;
	};
	player Player;
	
	int AcelerationTimer = 0;
	int SceneTimer = 0;
	bool saltant = false;
	bool sentitMoviment = true; //true cap a la dreta

	SDL_Rect rectFons;

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

private:
	SDL_Texture* imgFons;
	SDL_Texture* granota;
	//SDL_Rect rect1;
	SDL_Rect PlayerRect;
	SDL_Rect PlayerRectA1;
	SDL_Rect PlayerRectA2;
	SDL_Rect PlayerRectJump;
	enum PAnim {IDLE, A1, A2, JUMP};
	PAnim playerAnim = IDLE;
};

#endif // __SCENE_H__