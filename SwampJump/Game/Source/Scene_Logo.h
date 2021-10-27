#ifndef __SCENE_LOGO_H__
#define __SCENE_LOGO_H__

#include "Module.h"

struct SDL_Texture;

class Scene_Logo : public Module
{
public:

	Scene_Logo();

	// Destructor
	virtual ~Scene_Logo();

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

	int timerLogo = 0;

private:
};


#endif // __SCENE_LOGO_H__