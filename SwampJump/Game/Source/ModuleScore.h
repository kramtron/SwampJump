#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__

#include "Module.h"
#include "p2List.h"

struct SDL_Texture;

class HitPoints
{
public:

	int x = 0;
	int y = 0;
	int w = 20;
	int h = 20;
	int heal = 0;
	bool enable = false;

	HitPoints()
	{

	}

private:

};


class Score
{
public:

	int x = 0;
	int y = 0;
	int w = 80;
	int h = 80;
	int value = 0;
	bool enable = false;

	Score()
	{

	}

private:

};

class PowerUp
{
public:

	int x = 0;
	int y = 0;
	int w = 35;
	int h = 35;
	int type = 0;
	bool enable = false;

	PowerUp()
	{

	}

private:

};

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

	HitPoints* PointsCreator();
	Score* ScoreCreator();
	PowerUp* PowerUpCreator();
	//bool SaveState(pugi::xml_node&) const;
	p2List<HitPoints*>* hitPointsList;
	p2List<Score*>* ScoreList;
	p2List<PowerUp*>* PwerUpList;

private:
};


#endif // __MODULESCORE_H__