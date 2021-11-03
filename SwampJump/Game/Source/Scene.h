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
	int scene_timer = 0;
	int timer_salt = 0;
	bool saltant = false;
	bool doblesalt = false;
	bool coyotejump = false;
	bool walking = false;
	bool sentit_moviment = true; //true cap a la dreta

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

private:
	SDL_Texture* imgFons1;
	SDL_Texture* imgFons2;
	SDL_Texture* imgFons3;
	SDL_Texture* imgFons4;
	SDL_Texture* granota;
	float parallax1 = 0;
	int parallax2 = 0;
	float parallax3 = 0;
	//SDL_Rect rect1;
	SDL_Rect PlayerRect;
	SDL_Rect PlayerRectA1;
	SDL_Rect PlayerRectA2;
	SDL_Rect PlayerRectJump;
	SDL_Rect PlayerRectWalk;
	enum PAnim {IDLE, A1, A2, JUMP, WALK};
	PAnim playerAnim = IDLE;
};

#endif // __SCENE_H__