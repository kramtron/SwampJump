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

	void ObeliskMenuController();

	bool debug = false;

	bool godMode = false;

	bool reset = false;

	struct player_struct
	{
		float x;
		float y;
		float startingX;
		float startingY;
		float vx = 0;
		float vy = 0;
		float ay = 1;

		float w;
		float h;
		float v2x;
		float v2y;
		float playerHp;
		float actualPlayerHp;
		float playerDamage;
		float startingPoints;
		float actualPoints;
		bool playerInmortal;
		float skillCooldown=1600;
		float skillActiveTime;

		bool playedBefore;
		bool dead = false;

	}player;
	fPoint disparo;
	fPoint disparoPlayer;
	bool boolDisparo = false;
	bool disparoRetroceso=true;
	iPoint before_camera;
	
	int aceleration_timer = 0;
	bool doblesalt = false;
	bool coyotejump = false;
	bool tocant_terra_abans = false;
	bool tocant_terra = false;
	bool sentit = true; //dreta true, esquerra false
	float spawnTimer1 = 3000;
	float spawnTimer2 = 3000;
	float spawnTimer3 = 3000;
	float spawnTimer4 = 3000;
	float spawnTimer5 = 3000;
	float spawnTimer6 = 3000;
	float spawnTimer7 = 3000;

	float spawn1FlyEnemicTimer = 1500;
	float spawn2FlyEnemicTimer = 1500;
	float spawn3FlyEnemicTimer = 1500;
	float spawn4FlyEnemicTimer = 1500;
	float spawn5FlyEnemicTimer = 1500;
	float spawn6FlyEnemicTimer = 1500;
	float spawn7FlyEnemicTimer = 1500;

	bool LoadState(pugi::xml_node&);

	bool LoadPlayerData(pugi::xml_node&);
	bool loadPlayerData = true;

	bool LoadScene1Data(pugi::xml_node&);
	bool loadScene1Data = true;

	struct CheckPoint {
		float x, y, w, h;
	};

	CheckPoint checkPont1;
	CheckPoint checkPont2;
	CheckPoint checkPont3;
	CheckPoint checkPont4;
	CheckPoint checkPont5;

	bool SaveState(pugi::xml_node&) const;
	bool SaveScene1State(pugi::xml_node&) const;

	SDL_Rect sensorSpawn1;
	SDL_Rect meleEnemicSpawn1;
	SDL_Rect meleEnemicSpawn2;
	SDL_Rect meleEnemicSpawn3;
	SDL_Rect meleEnemicSpawn4;
	SDL_Rect meleEnemicSpawn5;
	SDL_Rect meleEnemicSpawn6;
	SDL_Rect meleEnemicSpawn7;



	bool obelisk1Up;
	bool obelisk2Up;
	bool obelisk3Up;
	bool obelisk4Up;
	bool obelisk5Up;
	bool obeliskTp = false;

	bool insideObelisk1;
	bool insideObelisk2;
	bool insideObelisk3;
	bool insideObelisk4;
	bool insideObelisk5;
	bool enterMenu=false;
	

	bool startingGame = true;
	int menuPlace=1;

	struct Mouse {
		int x, y;
		int left=1;

	}mouse;

	//Number, digit number, position X, position Y, number separation, scale.
	void FontDraw(int score, int n, int posX, int posY, int separacio, float scale);

	SDL_Texture* nombres;

	float cont_frames = 0;

	int reloj = 0;

private:
	uint audio_hurt;
	uint audio_tp;

	SDL_Texture* points = nullptr;
	SDL_Texture* timer = nullptr;

	SDL_Texture* hpBar1 = nullptr;
	SDL_Texture* hpBar2 = nullptr;

	SDL_Texture* imgFons1 = nullptr;
	SDL_Texture* imgFons2 = nullptr;
	SDL_Texture* imgFons3 = nullptr;
	SDL_Texture* imgFons4 = nullptr;
	SDL_Texture* granota = nullptr;

	SDL_Texture* obelisk = nullptr;
	SDL_Texture* thunder = nullptr;
	SDL_Texture* menuEToEnter = nullptr;
	SDL_Texture* normalMenuZone = nullptr;
	SDL_Texture* zone1Selected = nullptr;
	SDL_Texture* zone2Selected = nullptr;
	SDL_Texture* zone3Selected = nullptr;
	SDL_Texture* zone4Selected = nullptr;
	SDL_Texture* zone5Selected = nullptr;

	SDL_Texture* arbre1 = nullptr;
	SDL_Texture* arbre2 = nullptr;
	SDL_Texture* tronc1 = nullptr;
	SDL_Texture* cartell1 = nullptr;
	SDL_Texture* cartell5 = nullptr;
	SDL_Texture* cartell8 = nullptr;
	SDL_Texture* bush1 = nullptr;
	SDL_Texture* bush3 = nullptr;
	SDL_Texture* bush8 = nullptr;

	

	float obeliskFluctuationAngle = 0, obeliskFluctuation = 0;

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
	Animation staticRAnim;
	Animation staticLAnim;

	Animation thunderAnim;
};

#endif // __SCENE_H__