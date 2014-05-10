
#ifndef STATEPLAY_H_
#define STATEPLAY_H_

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>
#include <Aurora/Graphics/Effects/SkyLight.h>
#include <Aurora/Graphics/Effects/SkyClouds.h>
#include <Aurora/Graphics/Effects/SkyDome.h>

#include "LameMob.h"
#include "CraftWorld2.h"
#include "InputHelper.h"
#include "SoundManager.h"

using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


class StatePlay : public CGameState
{
public:
	StatePlay();
	virtual ~StatePlay();

	void Init();
	void InitParametric(int terrainType,bool makeFlat,bool makeTrees,bool makePumpkins,bool makeTypes,bool makeWater,bool makeCaves,bool makeSnow,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedIII);
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();
    void makeExplosion(const int x, const int y, const int z, short r);
	void LoadTextures();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

	void LoadMap(std::string fileName,bool compressed);
	void SetWorldAndSaveName(std::string worldName,std::string fileName);
	void InitCamera();

	//keys helpers
	bool keyPressed(int currentKey);
	bool keyHold(int currentKey);
	void PutInInventory(int id, int num, bool st);

private:

	void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice);
	bool TryToMove(Vector3 moveVector,float dt);
    void ChangeInvList(short x);
	void SetDayTimeAfterLoad();
	void CraftItem2x2();
	void CraftItem3x3();
	int FindChestId(int x, int y, int z);
	void HungerTime();
	void HealthTime();

private:

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	InputHelper *mIhelper;
	Camera *fppCam;

	std::string saveFileName;
	int freeMemory;
	float freeMemoryTimer;



	CraftWorld *mWorld;
	ObjModel *cubeModel;
    SkyLight *skyLight;
	SkyDome *skyDome;

	float sunTime;
	float sunTimeTick;
	bool sunMoonSwitch;
	bool mobSpawn;
	bool startDt;
    float dT; //time of destr
    float dET; //end time of destt
    float dS; //speed of destr

    bool hurt;
    float hurt_time;


    Vector3 testPos1;

	Vector3 cubePos;
	bool showCube;

    int craftSlotId[4];
    int craftSlotAm[4];
    bool craftSlotSt[4];

    int craftSlotId3[9];
    int craftSlotAm3[9];
    bool craftSlotSt3[9];

    int craftItemId;
    int craftItemAm;
    bool craftItemSt;

    int craftItemId3;
    int craftItemAm3;
    bool craftItemSt3;

    int chestId;

	//zmienne do poruszania
	float GRAVITY;
	float JUMPVELOCITY;
	float CLIMBVELOCITY;

	Vector3 playerVelocity;
	Vector3 playerPosition;
	Vector3 newPlayerPos;
	Vector3 oldPlayerPos;

	bool walkingOnGround;
	bool jumping;
	bool headInWater;
	bool footInWater;
	bool headInLava;
	bool footInLava;
	bool invEn;
	bool craftEn;
	bool craft2xEn;
	bool craft3xEn;
	bool chestEn;
    int barPosition;
    int invXPosition;
    int invYPosition;

    float shift_x;
    float shift_y;

    int time_z;

	int ram1;
	int ram2;
	int tick;
	int tickH;
	int tick2;
	int chunks; // 0 - 7;
    int yy;

    int chunkId;

	int terrainType;

	Timer mTimer;
	float dt;

	//textures info
	int texture;
	int blue;
	int red;

	Sprite *selectInvSprite;
	Sprite *invSprite;
    Sprite *craft2xSprite;
    Sprite *craft3xSprite;
    Sprite *chestSprite;
	Sprite *barSprite;
	Sprite *crossSprite;
	Sprite *selectSprite;

	Sprite *hpCellSprite;
	Sprite *hpSprite;
	Sprite *hpHalfSprite;
	Sprite *hgCellSprite;
	Sprite *hgSprite;
	Sprite *hgHalfSprite;

	float cameraSpeed;
	float cameraMoveSpeed;

	//menu sprites
	Sprite *buttonSprite;
	Sprite *sbuttonSprite;

	int menuState;//0 game,1 menu
	bool menuOptions;
	int optionsMenuPos;
	int selectPos;

	//some settings
	bool canFly;
	bool devMode;
	bool analogLeft,analogRight,analogUp,analogDown;

	//for sound of walkinng
	float walkSoundAccu;
	bool  isWalking;

	//Headbob
	bool canHeadBob;
	float bobCycle;

	bool makeScreen;
};

#endif
