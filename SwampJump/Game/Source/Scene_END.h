#ifndef __SCENE_END_H__
#define __SCENE_END_H__

#include "Module.h"

struct SDL_Texture;

class Scene_END : public Module
{
public:

	Scene_END();

	// Destructor
	virtual ~Scene_END();

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
private:

	SDL_Texture* gameOverStart;
	SDL_Texture* gameOverExit;

};


#endif // __SCENE_END_H__