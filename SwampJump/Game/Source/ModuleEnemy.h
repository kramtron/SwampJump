#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__

#include "Module.h"

struct SDL_Texture;

class ModuleEnemy : public Module
{
public:

	ModuleEnemy();

	// Destructor
	virtual ~ModuleEnemy();

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

	SDL_Texture* gameIntro;

private:
};


#endif // __MODULE_ENEMY_H__