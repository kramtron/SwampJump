#ifndef __MODULESCORE_H__
#define __MODULESCORE_H__

#include "Module.h"
#include "p2List.h"
#include "Scene.h"

struct SDL_Texture;

class PickUp
{
public:
	SDL_Rect rect = { 0, 0, 100, 100 };
	bool enable = false;
	enum class PickUpType {HP, COIN, POWERUP}pickUpType = PickUpType::HP;
	int value = 0;

	PickUp(SDL_Rect rect, PickUpType pickUpType, int value)
	{
		this->rect = rect;
		this->pickUpType = pickUpType;
		this->value = value;
	}
	
	~PickUp(){
	}
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

	PickUp* HpCreate(int x, int y, int value);
	PickUp* CoinCreate(int x, int y, int value);
	//bool SaveState(pugi::xml_node&) const;
	p2List<PickUp*> pickUpList;
	
private:
	//void DrawPickUps();
	void DebugDrawPickUps();
	void CollidePickUps();
	void DeletePickUp(p2List_item<PickUp*>* item);
	SDL_Texture* pickUpTexture = nullptr;
};


#endif // __MODULESCORE_H__