#ifndef __SCENE_WIN_H__
#define __SCENE_WIN_H__

#include "Module.h"

struct SDL_Texture;

class Scene_Win : public Module
{
public:

	Scene_Win();

	// Destructor
	virtual ~Scene_Win();

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
	float score = 0;

	struct Mouse {
		int x, y;
		int left = 1;

	}mouse;

private:

	SDL_Texture* points = nullptr;
	SDL_Texture* apples = nullptr;
	SDL_Texture* timer = nullptr;
	SDL_Texture* scoreTexture = nullptr;

	SDL_Texture* nombres;

	SDL_Texture* gameOverStart;
	SDL_Texture* exitSelect;
	SDL_Texture* returnSelected;

	void FontDraw(int score, int n, int posX, int posY, int separacio, float scale);

};


#endif // __SCENE_WIN_H__