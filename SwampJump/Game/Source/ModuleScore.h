#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__

#include "Module.h"
#include "p2List.h"

struct SDL_Texture;

class ModuleScore : public Module
{
public:

	ModuleScore();

	// Destructor
	virtual ~ModuleScore();

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


	//bool SaveState(pugi::xml_node&) const;


private:
};


#endif // __MODULESCORE_H__