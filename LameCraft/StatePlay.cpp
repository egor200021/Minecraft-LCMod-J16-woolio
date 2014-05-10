#include "StatePlay.h"
#include "TextureHelper.h"

#include "WorldGenerator.h"

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define TEXTURE_CHUNKS 8

StatePlay::StatePlay()
{
    mRender = NULL;
    mSystemMgr = NULL;
    fppCam = NULL;

    //utils
    freeMemory = 0;
    freeMemoryTimer = 0.0f;

    showCube = true;

    //zmienne do poruszania
    GRAVITY = -6.8f;
    JUMPVELOCITY = 4.6f;
    CLIMBVELOCITY = 2.5f;

    walkingOnGround = false;
    jumping = false;
    headInWater = false;
    footInWater = false;
    headInLava = false;
    footInLava = false;
    invEn = false;
    craft3xEn = false;
    craft2xEn = false;
    chestEn = false;

    chunkId = 0;
    chunks = 0;
    tick2 = 0;
    //---*
    startDt = false;
    dET = 0;
    dS = 0;
    dT = 0;

    testPos1.x = -1;
    testPos1.y = -1;
    testPos1.z = -1;
    //---*

    yy = 0;

    barPosition = 0;
    invXPosition = 0;
    invYPosition = 0;

    shift_x = 0.0f;
    shift_y = 0.0f;

    craftItemId = -1;
    craftItemAm = -1;
    craftItemSt = 0;

    craftItemId3 = -1;
    craftItemAm3 = -1;
    craftItemSt3 = 0;
    tick = 0;
    tickH = 0;
    hurt = false;
    hurt_time = 0;
    chestId = -1;

    ram1 = 0;
    ram2 = 0;
    dt = 0.0f;
    sunTime = 21600.0f;//6 am
    sunTimeTick = 0.0f;
    sunMoonSwitch = true;

    cameraSpeed = 2.0f / 60.0f;
    cameraMoveSpeed = 4.0f/ 60.0f;

    //stete to game
    menuState = 0;
    selectPos = 0;

    //flying
    time_z = 0;
    canFly = false;
    devMode = false;
    makeScreen = false;

    //bob
	canHeadBob = true;
	bobCycle = 0.0f;

	mobSpawn = false;

	for(int i = 0; i <= 3; i += 1)
    {
        craftSlotId[i] = -1;
        craftSlotAm[i] = -1;
        craftSlotSt[i] = 0;
    }

    for(int i = 0; i <= 8; i += 1)
    {
        craftSlotId3[i] = -1;
        craftSlotAm3[i] = -1;
        craftSlotSt3[i] = 0;
    }
}

StatePlay::~StatePlay()
{

}

void StatePlay::InitCamera()
{
    fppCam = new Camera();
    fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
    mRender->SetActiveCamera(fppCam);
}

void StatePlay::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,80.0f,64.0f);

    WorldGenerator *mGen = new WorldGenerator();

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(128, 16);
    mGen->initRandompMap(128, 16, mWorld);
    delete mGen;
    //mWorld->initRandompMap(128,16);
    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(5);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    dt = mTimer.GetDeltaTime();

    //block sets info

    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one

    //std::floor

    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;
}

void StatePlay::InitParametric(int terrainType,bool makeFlat,bool makeTrees,bool makePumpkins,bool makeWater,bool makeCaves,bool makeTypes,bool makeIron,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedIII)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,80.0f,64.0f);

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(128, 16);

    WorldGenerator *mGen = new WorldGenerator();
    mGen->initRandompMap(128,16, mWorld, terrainType,makeFlat,makeTrees,makePumpkins,makeTypes,makeWater,makeIron,makeCaves,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,seedIII);
    delete mGen;
    //mWorld->initRandompMap(128,16,terrainType,makeFlat,makeTrees,makeWater,makeCaves);
    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(5);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    dt = mTimer.GetDeltaTime();

    //block sets info
    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one


    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

}

void StatePlay::SetWorldAndSaveName(std::string worldName,std::string fileName)
{
    if(mWorld != NULL)
    {
        sprintf(mWorld->worldName,"%s",worldName.c_str());
    }
    saveFileName = fileName;
}

void StatePlay::makeExplosion(const int x, const int y, const int z, short r)
{

}

void StatePlay::ChangeInvList(short x)
{

}

void StatePlay::LoadMap(std::string fileName,bool compressed)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //save name
    saveFileName = fileName;
    //
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,80.0f,64.0f);

    //then create our perfect world
    mWorld = new CraftWorld();

    if(compressed)
    {
        mWorld->LoadCompressedWorld(saveFileName);
        //set player pos from map
        playerPosition = mWorld->GetPlayerPos();
        newPlayerPos  = mWorld->GetPlayerPos();
        oldPlayerPos = mWorld->GetPlayerPos();
        mWorld->SetWolrdTime(mWorld->worldDayTime);
    }
    else
    {
        mWorld->LoadWorld(saveFileName.c_str());
        mWorld->SetWolrdTime(5);
    }

    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    dt = mTimer.GetDeltaTime();

    //block sets info
    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one

    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    SetDayTimeAfterLoad();
}

void StatePlay::LoadTextures()
{
    //terrain texure
    texture = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain);

    //water filter
    blue = TextureHelper::Instance()->GetTexture(TextureHelper::Blue);


    red = TextureHelper::Instance()->GetTexture(TextureHelper::Red);


    //bar image
    barSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,0,182,22);
    barSprite->SetPosition(240,253);
    barSprite->Scale(1.75f,1.75f);

    selectSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),1,23,22,22);
    selectSprite->SetPosition(100,253);
    selectSprite->Scale(1.75f,1.75f);

    crossSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),201,13,9,9);
    crossSprite->SetPosition(240,136);
    crossSprite->Scale(2.0f,2.0f);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,22,200,20);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,62,200,20);
    sbuttonSprite->SetPosition(240,150);

    invSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv),0,0,182,62);//200
    invSprite->SetPosition(240,185);
    invSprite->Scale(1.75f,1.75f);

    craft2xSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv),20,62,81,41);
    craft2xSprite->SetPosition(151,99);
    craft2xSprite->Scale(1.75f,1.75f);

    craft3xSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv),200,0,103,62);
    craft3xSprite->SetPosition(170,80);
    craft3xSprite->Scale(1.75f,1.75f);

    chestSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv),0,0,182,41);
    chestSprite->SetPosition(240,60);
    chestSprite->Scale(1.75f,1.75f);

    selectInvSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv),0,61,8,8);
    selectInvSprite->SetPosition(100,20);
    selectInvSprite->Scale(1.0f,1.0f);

    hpCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),209,0,9,10);
    hpCellSprite->SetPosition(100,21);
    hpCellSprite->Scale(2.0f,2.0f);

    hpSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),200,0,9,10);
    hpSprite->SetPosition(100,22);
    hpSprite->Scale(2.0f,2.0f);

    hpHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),238,0,9,10);
    hpHalfSprite->SetPosition(100,23);
    hpHalfSprite->Scale(2.0f,2.0f);

    hgCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),218,9,10,10);
    hgCellSprite->SetPosition(100,24);
    hgCellSprite->Scale(2.0f,2.0f);

    hgSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),228,9,10,10);
    hgSprite->SetPosition(100,25);
    hgSprite->Scale(2.0f,2.0f);

    hgHalfSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),238,9,10,10);
    hgHalfSprite->SetPosition(100,26);
    hgHalfSprite->Scale(2.0f,2.0f);

    cubeModel = new ObjModel();
    cubeModel->LoadObj("Assets/Lamecraft/textureCube.obj");
    cubeModel->Optimize();

    //sky dome
    if(terrainType == 4)
    {
        skyDome = new SkyDome();
	    skyDome->CreateSkyDomeMesh();

	    skyDome->SetTexture(TextureHelper::Instance()->GetTexture(TextureHelper::NetherSky));
	    skyDome->timeOfDay = 0.1f;

	    skyLight = new SkyLight();
	    skyLight->SetTexture(TextureHelper::Instance()->GetTexture(TextureHelper::Sun));
    }else
    {
        skyDome = new SkyDome();
	    skyDome->CreateSkyDomeMesh();

	    skyDome->SetTexture(TextureHelper::Instance()->GetTexture(TextureHelper::Sky));
	    skyDome->timeOfDay = 0.1f;

	    skyLight = new SkyLight();
	    skyLight->SetTexture(TextureHelper::Instance()->GetTexture(TextureHelper::Sun));

    }
}



void StatePlay::SetDayTimeAfterLoad()
{
if(!mWorld->freezeDayTime)
{
	if(mWorld->worldVersion >=3)
	{
		if(mWorld->worldDayTime >= 5.0f && mWorld->worldDayTime < 21.0f)
		{
			skyLight->SetTexture(TextureManager::Instance()->GetTextureNumber("Assets/Lamecraft/sun.png"));
			sunMoonSwitch = true;
		}else
		{
			skyLight->SetTexture(TextureManager::Instance()->GetTextureNumber("Assets/Lamecraft/moon.png"));
			sunMoonSwitch = false;
		}

		sunTime = mWorld->sunTime;
		skyDome->timeOfDay = mWorld->worldDayTime * 0.041666f;
	}
}
}
void StatePlay::Enter()
{
    RenderManager::InstancePtr()->SetPerspective(55.0f, 480.0f / 272.0f, 0.18f, 1000.f);
}
void StatePlay::CleanUp()
{
    delete mRender->mCam;
    mRender->mCam = NULL;
    delete buttonSprite;
    delete sbuttonSprite;
    delete barSprite;
    delete selectSprite;
    delete crossSprite;
    delete invSprite;
    delete selectInvSprite;
    delete craft2xSprite;
    delete craft3xSprite;
    delete chestSprite;
    delete hpCellSprite;
    delete hpSprite;
    delete hpHalfSprite;
    delete hgCellSprite;
    delete hgSprite;
    delete hgHalfSprite;
    delete cubeModel;
    delete skyDome;
    delete skyLight;


    //delete fppCam;
    delete mWorld;

}

void StatePlay::Pause()
{

}

void StatePlay::Resume()
{

}

void StatePlay::CraftItem2x2()
{
    int result = 0;
    for(int i = 0; i <= 3; i ++)
    {
        if(craftSlotId[i] != -1)
        {
            result += craftSlotId[i];
        }
    }

    switch(result)
    {
    case 8:
        if(craftSlotId[0] == 8 || craftSlotId[1] == 8 || craftSlotId[2] == 8 || craftSlotId[3] == 8)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 31:
        if(craftSlotId[0] == 31 || craftSlotId[1] == 31 || craftSlotId[2] == 31 || craftSlotId[3] == 31)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 1156:
        if(craftSlotId[0] == 289 && craftSlotId[1] == 289 && craftSlotId[2] == 289 && craftSlotId[3] == 289)
        {
            craftItemId = 27;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    case 99:
        if(craftSlotId[0] == 99 || craftSlotId[1] == 99 || craftSlotId[2] == 99 || craftSlotId[3] == 99)
        {
            craftItemId = 283;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 136:
        if(craftSlotId[0] == 34)
        {
            craftItemId = 105;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    case 68:
        if((craftSlotId[0] == 34 && craftSlotId[2] == 34)  || (craftSlotId[1] == 34 && craftSlotId[3] == 34))
        {
            craftItemId = 276;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 553:
        if((craftSlotId[0] == 277 && craftSlotId[2] == 276) || (craftSlotId[1] == 277 && craftSlotId[3] == 276))
        {
            craftItemId = 48;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;


    case 556: //scirrors
        if((craftSlotId[0] == 278 && craftSlotId[3] == 278))
        {
            craftItemId = 275;
            craftItemSt = 0;
            craftItemAm = 239;
        }
    break;

    default:
        craftItemId = -1;
        craftItemAm = -1;
        craftItemSt = 0;
    break;

    }
}

int StatePlay::FindChestId(int x, int y, int z)
{
    int o;
    o = -1;
    for(int i = 0; i <= 31; i++)
    {
        if (mWorld->chestX[i] == x && mWorld->chestY[i] == y && mWorld->chestZ[i] == z)
        {
            o = i;
        }
    }

    return o;
}


void StatePlay::CraftItem3x3()
{
    int result = 0;
    for(int i = 0; i <= 8; i ++)
    {
        if(craftSlotId3[i] != -1)
        {
            result += craftSlotId3[i];
        }
    }

    switch(result)
    {
    case 8://planks
        if(craftSlotId3[0] == 8 || craftSlotId3[1] == 8 || craftSlotId3[2] == 8 || craftSlotId3[3] == 8 || craftSlotId3[4] == 8 || craftSlotId3[5] == 8 || craftSlotId3[6] == 8 || craftSlotId3[7] == 8 || craftSlotId3[8] == 8)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 31:// planks
        if(craftSlotId3[0] == 31 || craftSlotId3[1] == 31 || craftSlotId3[2] == 31 || craftSlotId3[3] == 31 || craftSlotId3[4] == 31 || craftSlotId3[5] == 31 || craftSlotId3[6] == 31 || craftSlotId3[7] == 31 || craftSlotId3[8] == 31)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 68://sticks
        if((craftSlotId3[0] == 34 && craftSlotId3[3] == 34)  || (craftSlotId3[1] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[2] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[6] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[5] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 276;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 136://crafting
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 105;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 553://torches
        if((craftSlotId3[0] == 277 && craftSlotId3[3] == 276) || (craftSlotId3[1] == 277 && craftSlotId3[4] == 276) || (craftSlotId3[2] == 277 && craftSlotId3[5] == 276) || (craftSlotId3[3] == 277 && craftSlotId3[6] == 276) || (craftSlotId3[4] == 277 && craftSlotId3[7] == 276) || (craftSlotId3[5] == 277 && craftSlotId3[8] == 276))
        {
            craftItemId3 = 48;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;


    case 556: //scirrors
        if((craftSlotId3[0] == 278 && craftSlotId3[4] == 278) || (craftSlotId3[1] == 278 && craftSlotId3[5] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[7] == 278) || (craftSlotId3[4] == 278 && craftSlotId3[8] == 278))
        {
            craftItemId3 = 275;
            craftItemSt3 = 0;
            craftItemAm3 = 239;
        }
    break;

    case 99://clay
        if(craftSlotId[0] == 99 || craftSlotId[1] == 99 || craftSlotId[2] == 99 || craftSlotId[3] == 99 || craftSlotId[4] == 99 || craftSlotId[5] == 99 || craftSlotId[6] == 99 || craftSlotId[7] == 99 || craftSlotId[8] == 99)
        {
            craftItemId = 283;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    // half blocks

    case 108://cobblestone
        if((craftSlotId[0] == 36 && craftSlotId[1] == 36 && craftSlotId[2] == 36) || (craftSlotId[3] == 36 && craftSlotId[4] == 36 && craftSlotId[5] == 36) || (craftSlotId[6] == 36 && craftSlotId[7] == 36 && craftSlotId[8] == 36))
        {
            craftItemId = 82;
            craftItemSt = 1;
            craftItemAm = 3;
        }
    break;

    case 102://planks
        if((craftSlotId[0] == 34 && craftSlotId[1] == 34 && craftSlotId[2] == 34) || (craftSlotId[3] == 34 && craftSlotId[4] == 34 && craftSlotId[5] == 34) || (craftSlotId[6] == 34 && craftSlotId[7] == 34 && craftSlotId[8] == 34))
        {
            craftItemId = 86;
            craftItemSt = 1;
            craftItemAm = 3;
        }
    break;

    case 9://stone
        if((craftSlotId[0] == 3 && craftSlotId[1] == 3 && craftSlotId[2] == 3) || (craftSlotId[3] == 3 && craftSlotId[4] == 3 && craftSlotId[5] == 3) || (craftSlotId[6] == 3 && craftSlotId[7] == 3 && craftSlotId[8] == 3))
        {
            craftItemId = 84;
            craftItemSt = 1;
            craftItemAm = 3;
        }
    break;


    // end


    //wooden instruments
    case 654:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34 && craftSlotId3[2] == 34)
        {
            craftItemId3 = 250;
            craftItemSt3 = 0;
            craftItemAm3 = 60;

        }
        else if(craftSlotId3[0] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34)
        {
            craftItemId3 = 265;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
        break;

    case 620:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34)
        {
            craftItemId3 = 270;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    case 586:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 260;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;
    //stone instruments
    case 660:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36 && craftSlotId3[2] == 36)
        {
            craftItemId3 = 251;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        else if(craftSlotId3[0] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 36 && craftSlotId3[3] == 36)
        {
            craftItemId3 = 266;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
        break;

    case 624:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36)
        {
            craftItemId3 = 271;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    case 588:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 261;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    //iron instruments
    case 1386:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278 && craftSlotId3[2] == 278)
        {
            craftItemId3 = 252;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
        else if(craftSlotId3[0] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 278 && craftSlotId3[3] == 278)
        {
            craftItemId3 = 267;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
        break;

    case 1108:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278)
        {
            craftItemId3 = 272;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    case 830:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 262;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;
    //diamond instruments
    case 1389:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279 && craftSlotId3[2] == 279)
        {
            craftItemId3 = 253;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        else if(craftSlotId3[0] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 279 && craftSlotId3[3] == 278)
        {
            craftItemId3 = 268;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
        break;

    case 1110:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279)
        {
            craftItemId3 = 273;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    case 831:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 263;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
        else
        {
            craftItemId3 = -1;
            craftItemSt3 = 0;
            craftItemAm3 = -1;
        }
    break;

    case 2502: //iron block
        if(craftSlotId3[0] == 278 && craftSlotId3[1] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[4] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[7] == 278 && craftSlotId3[8] == 278)
        {
            craftItemId3 = 66;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 66: //iron block to bars
        if(craftSlotId3[0] == 66 || craftSlotId3[1] == 66 || craftSlotId3[2] == 66 && craftSlotId3[3] == 66 || craftSlotId3[4] == 66 || craftSlotId3[5] == 66 || craftSlotId3[6] == 66 && craftSlotId3[7] == 66 || craftSlotId3[8] == 66)
        {
            craftItemId3 = 278;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2520: //gold block
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 65;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 65: //gold block to bars
        if(craftSlotId3[0] == 65 || craftSlotId3[1] == 65 || craftSlotId3[2] == 65 && craftSlotId3[3] == 65 || craftSlotId3[4] == 65 || craftSlotId3[5] == 65 || craftSlotId3[6] == 65 && craftSlotId3[7] == 65 || craftSlotId3[8] == 65)
        {
            craftItemId3 = 280;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2511: //diamond block
        if(craftSlotId3[0] == 279 && craftSlotId3[1] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[4] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[7] == 279 && craftSlotId3[8] == 279)
        {
            craftItemId3 = 64;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 64: //diamond block to diamonds
        if(craftSlotId3[0] == 64 || craftSlotId3[1] == 64 || craftSlotId3[2] == 64 && craftSlotId3[3] == 64 || craftSlotId3[4] == 64 || craftSlotId3[5] == 64 || craftSlotId3[6] == 64 && craftSlotId3[7] == 64 || craftSlotId3[8] == 64)
        {
            craftItemId3 = 279;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 1932: //ladder
        if(craftSlotId3[0] == 276 && craftSlotId3[2] == 276 && craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276 && craftSlotId3[6] == 276 && craftSlotId3[8] == 276)
        {
            craftItemId3 = 6;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;


    /*'furnace' recipes*/
    case 2253: //iron bar
        if(craftSlotId3[0] == 281 && craftSlotId3[4] == 5 && craftSlotId3[1] == 281 && craftSlotId3[2] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[6] == 281 && craftSlotId3[7] == 281 && craftSlotId3[8] == 281 )
        {
            craftItemId3 = 280;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 2289: //golden bar
        if(craftSlotId3[0] == 281 && craftSlotId3[4] == 41 && craftSlotId3[1] == 281 && craftSlotId3[2] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[6] == 281 && craftSlotId3[7] == 281 && craftSlotId3[8] == 281 )
        {
            craftItemId3 = 278;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1131: //glass
        if(craftSlotId3[4] == 7 && craftSlotId3[1] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[7] == 281)
        {
            craftItemId3 = 40;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1112: //fireitem from sticks
        if(craftSlotId3[4] == 8 && craftSlotId3[1] == 276 && craftSlotId3[3] == 276 && craftSlotId3[5] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 281;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1135: //fireitem from sticks
        if(craftSlotId3[4] == 31 && craftSlotId3[1] == 276 && craftSlotId3[3] == 276 && craftSlotId3[5] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 281;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1401: //fireitem from coal
        if(craftSlotId3[4] == 277 && craftSlotId3[1] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[7] == 281)
        {
            craftItemId3 = 281;
            craftItemSt3 = 1;
            craftItemAm3 = 6;
        }
    break;

    case 1406: //fireitem from lignitecoal
        if(craftSlotId3[4] == 282 && craftSlotId3[1] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[7] == 281)
        {
            craftItemId3 = 281;
            craftItemSt3 = 1;
            craftItemAm3 = 12;
        }
    break;

    case 1407: //brick
        if(craftSlotId3[4] == 283 && craftSlotId3[1] == 281 && craftSlotId3[3] == 281 && craftSlotId3[5] == 281 && craftSlotId3[7] == 281)
        {
            craftItemId3 = 289;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    //end

    case 1156: //brickblock
        if((craftSlotId3[0] == 289 && craftSlotId3[1] == 289 && craftSlotId3[3] == 289 && craftSlotId3[4] == 289) || (craftSlotId3[1] == 289 && craftSlotId3[2] == 289 && craftSlotId3[4] == 289 && craftSlotId3[5] == 289) || (craftSlotId3[3] == 289 && craftSlotId3[4] == 289 && craftSlotId3[6] == 289 && craftSlotId3[7] == 289) || (craftSlotId3[4] == 289 && craftSlotId3[5] == 289 && craftSlotId3[7] == 289 && craftSlotId3[8] == 289))
        {
            craftItemId3 = 27;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 272: //chest
        if(craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[3] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[0] == 34 && craftSlotId3[6] == 34 && craftSlotId3[8] == 34)
        {
            craftItemId3 = 100;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 861: //bread
        if((craftSlotId3[0] == 287 && craftSlotId3[1] == 287 && craftSlotId3[2] == 287) || (craftSlotId3[3] == 287 && craftSlotId3[4] == 287 && craftSlotId3[5] == 287) || (craftSlotId3[6] == 287 && craftSlotId3[7] == 287 && craftSlotId3[8] == 287))
        {
            craftItemId3 = 288;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 2524: //golden apple
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 284 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 285;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    default:
        craftItemId3 = -1;
        craftItemAm3 = -1;
        craftItemSt3 = 0;
    break;

    }
}

void StatePlay::HandleEvents(StateManager* sManager)
{
    //update delta time
    dt = mTimer.GetDeltaTime();

    cameraSpeed = 2.0f * dt;
    cameraMoveSpeed = 4.0f * dt;

    //free memory counter
    if(devMode)
    {
        freeMemoryTimer += dt;
        if(freeMemoryTimer > 1.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }

    //update input
    mSystemMgr->InputUpdate();
    if(mWorld->HP > 0)
    {
    if(menuState == 0)//game state
    {
        if(invEn == false)
        {
        if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
        {
            barPosition != 8 ? barPosition ++ : barPosition = 0;

            selectSprite->SetPosition(100 + (barPosition * 35),253);
            startDt = 0;
            dT = 0;
            dET = 0;
            dS = 0;
        }
        //switch right
        if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
        {
            barPosition != 0 ? barPosition -- : barPosition = 8;

            selectSprite->SetPosition(100 + (barPosition * 35),253);
            startDt = 0;
            dT = 0;
            dET = 0;
            dS = 0;
        }
        //menu
        if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
        {
            menuState = 1;
            menuOptions = false;
            optionsMenuPos = 0;
        }

        //camera input
        //rotate uo
        if(keyHold(InputHelper::Instance()->getButtonToAction(4)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->PitchView(cameraSpeed);

            if (shift_y > -0.06)
            {

                shift_y -= 0.005;
            }
        }
        else
        {
            if (shift_y < 0)
            {

                shift_y += 0.005;
            }
        }
        //rotate down
        if(keyHold(InputHelper::Instance()->getButtonToAction(5)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->PitchView(-cameraSpeed);

            if (shift_y < 0.06)
            {

                shift_y += 0.005;
            }
        }
        else
        {
            if (shift_y > 0)
            {

                shift_y -= 0.005;
            }
        }
        //rotate left
        if(keyHold(InputHelper::Instance()->getButtonToAction(6)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->RotateView(cameraSpeed,0,1,0);

            if (shift_x < 0.06)
            {

                shift_x += 0.005;
            }
        }
        else
        {
            if (shift_x > 0)
            {

                shift_x -= 0.005;
            }
        }
        //rotate right
        if(keyHold(InputHelper::Instance()->getButtonToAction(7)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->RotateView(-cameraSpeed,0,1,0);

            if (shift_x > -0.06)
            {

                shift_x -= 0.005;
            }
        }
        else
        {
            if (shift_x < 0)
            {

                shift_x += 0.005;
            }
        }

        //move right
        if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->StrafePhysic(cameraMoveSpeed);
        }
        //move left
        if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            fppCam->StrafePhysic(-cameraMoveSpeed);
        }

        //move back
        if(keyHold(InputHelper::Instance()->getButtonToAction(1)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            if(canFly)
                fppCam->MovePhysic(-cameraMoveSpeed);
            else
                fppCam->MovePhysicNoY(-cameraMoveSpeed);
        }

        //move forward
        if(keyHold(InputHelper::Instance()->getButtonToAction(0)))
        {
            if (startDt == true)
            {
                startDt = false;
            }
            if(canFly)
                fppCam->MovePhysic(cameraMoveSpeed);
            else
                fppCam->MovePhysicNoY(cameraMoveSpeed);

        }

        if((keyPressed(InputHelper::Instance()->getButtonToAction(13)))&&(keyPressed(InputHelper::Instance()->getButtonToAction(14))))
        {
            invEn = true;
            craft2xEn = true;
            if (startDt == true)
            {
                startDt = false;
            }
        }

        //add cube
        if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
        {
            if (startDt == true)
            {
                startDt = false;
            }

            if (mWorld->invId[27+barPosition] == 288)
            {
                mWorld->HG += 8;

                if(mWorld->HG > 20)
                {
                    mWorld->HG = 20;
                }
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0)
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            if (mWorld->invId[27+barPosition] == 284)
            {
                mWorld->HG += 4;

                if(mWorld->HG > 20)
                {
                    mWorld->HG = 20;
                }
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0)
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            if (mWorld->invId[27+barPosition] == 285)
            {
                mWorld->HG = 20;
                mWorld->HP = 20;
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0)
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            bobCycle = 0;

            //add cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //get position and view vector
            Vector3 testPos;

            //move to the target +=0.5
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);
                /*for(int i = 0; i < 7; i += 1)
                {
                    if (pLamemob[i] != 0)
                    {
                        if (testPos.x > ((pLamemob[i]->pos.x-0.5) - pLamemob[i]->collideBox.x/2) && (testPos.x-0.5) < (pLamemob[i]->pos.x + pLamemob[i]->collideBox.x/2) && (testPos.z-0.5) > (pLamemob[i]->pos.z - pLamemob[i]->collideBox.z/2) && (testPos.z-0.5) > (pLamemob[i]->pos.z + pLamemob[i]->collideBox.z/2) && (testPos.y - 0.5) > (pLamemob[i]->pos.y - pLamemob[i]->collideBox.y/2) && (testPos.y - 0.5) > (pLamemob[i]->pos.y + pLamemob[i]->collideBox.y/2))
                        {
                            if(pLamemob[i]->HP < 10)
                            {
                                delete pLamemob[i];
                                pLamemob[i] = 0;
                                return;
                            }
                            pLamemob[i]->HP -= 2;
                            return;
                        }
                    }
                }*/


                //check if we are touch something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z))
                {

                if(mWorld->invId[27+barPosition] >= 270 && mWorld->invId[27+barPosition] <= 274)
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 1)
                    {
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 2;
                        if(rand() % 10 == 1)
                        {
                            PutInInventory(286,1,1);
                        }

                        mWorld->invAm[27+barPosition] -= 1;
                        if(mWorld->invAm[27+barPosition] == 0)
                        {
                            mWorld->invAm[27+barPosition] = -1;
                            mWorld->invId[27+barPosition] = -1;
                            mWorld->invSt[27+barPosition] = 0;
                        }
                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 2)
                    {
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 79;
                        mWorld->invAm[27+barPosition] -= 1;

                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }
                }


                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == Crafting::getID())
                    {

                        invEn = true;
                        craft3xEn = true;
                        return;

                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == Chest::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 131 || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 132 || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 133)
                    {
                        chestId = FindChestId(testPos.x,testPos.y,testPos.z);

                        if(chestId != -1)
                        {
                            craft2xEn = false;
                            craft3xEn = false;
                            invEn = true;
                            chestEn = true;
                            return;
                        }

                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == TrapDoor::getID())
                    {
                        mSoundMgr->doorSound();

                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        //Delete the actual TNT just in case
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = TrapDoor2::getID();
                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == TrapDoor2::getID())
                    {
                        mSoundMgr->doorSound();

                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        //Delete the actual TNT just in case
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = TrapDoor::getID();
                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }


                    BoundingBox testBox = BoundingBox(Vector3(cubePos.x - 0.5f,cubePos.y - 0.5f,cubePos.z - 0.5f),Vector3(cubePos.x + 0.5f,cubePos.y + 0.5f,cubePos.z + 0.5f));
                    Ray tesRay = Ray(fppCam->m_vPosition,rayDir);

                    float distance = -1.0f;
                    tesRay.hasIntersected(testBox,distance);

                    if(distance != -1.0f)
                    {
                        Vector3 hitPos = fppCam->m_vPosition + (rayDir * distance);
                        Vector3 normal = (hitPos - cubePos);
                        normal.normalize();

                        Vector3 testPos2;

                        if(normal.x < -0.66f)
                            testPos2.x = -1.0f;
                        else if(normal.x > 0.66f)
                            testPos2.x = 1.0f;
                        else
                            testPos2.x = 0.0f;

                        if(normal.y < -0.66f)
                            testPos2.y = -1.0f;
                        else if(normal.y > 0.66f)
                            testPos2.y = 1.0f;
                        else
                            testPos2.y = 0.0f;

                        if(normal.z < -0.66f)
                            testPos2.z = -1.0f;
                        else if(normal.z > 0.66f)
                            testPos2.z = 1.0f;
                        else
                            testPos2.z = 0.0f;


                        testPos2 += testPos;

                        //check if this block is empty
                        if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID() || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Cloud::getID())
                        {
                            //now check if player is not there ;) we don't want to place cubes where we stand
                            int boxX = (int)testPos2.x;
                            int boxY = (int)testPos2.y;
                            int boxZ = (int)testPos2.z;

                            BoundingBox blockBox = BoundingBox(Vector3(boxX,boxY,boxZ),Vector3(boxX + 1,boxY + 1,boxZ + 1));
                            BoundingBox playerBox = BoundingBox(Vector3(playerPosition.x - 0.15f,playerPosition.y - 1.5f,playerPosition.z - 0.15f),Vector3(playerPosition.x + 0.15f,playerPosition.y + 0.2f,playerPosition.z + 0.15f));

                            if(!blockBox.intersect(playerBox))
                            {
                                //check if you want put light source or normal block
                                if(mWorld->CanPutBlockHere(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]))
                                {
                                    if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
                                    {
                                        mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
                                    }

                                    if (mWorld->invId[27+barPosition]<250)
                                    {
                                        if(mWorld->invId[27+barPosition] == 100)
                                        {
                                            for(int i = 0; i <= 31; i++)
                                            {
                                                if(mWorld->chestX[i] == -1)
                                                {
                                                   mWorld->chestX[i] = testPos2.x;
                                                   mWorld->chestY[i] = testPos2.y;
                                                   mWorld->chestZ[i] = testPos2.z;
                                                   break;
                                                }
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition]!=-1)
                                        {
                                            int dX, dZ;

                                                switch(mWorld->invId[27+barPosition])
                                                {
                                                case 74:

                                                dX = playerPosition.x - testPos2.x;
                                                dZ = playerPosition.z - testPos2.z;

                                                if(dX < 0)
                                                {
                                                    dX *= -1;
                                                }

                                                if(dZ < 0)
                                                {
                                                    dZ *= -1;
                                                }

                                                if(testPos2.z > playerPosition.z && dZ > dX)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 123;
                                                }
                                                if(testPos2.z < playerPosition.z && dZ > dX)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 124;
                                                }
                                                if(testPos2.x > playerPosition.x && dX > dZ)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
                                                }
                                                if(testPos2.x < playerPosition.x && dX > dZ)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 122;
                                                }
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
                                                }
                                                break;

                                                case 100:

                                                dX = playerPosition.x - testPos2.x;
                                                dZ = playerPosition.z - testPos2.z;

                                                if(dX < 0)
                                                {
                                                    dX *= -1;
                                                }

                                                if(dZ < 0)
                                                {
                                                    dZ *= -1;
                                                }

                                                if(testPos2.z > playerPosition.z && dZ > dX)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 132; // 3
                                                }
                                                if(testPos2.z < playerPosition.z && dZ > dX)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 133; // 4
                                                }
                                                if(testPos2.x > playerPosition.x && dX > dZ)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 100; // 1
                                                }
                                                if(testPos2.x < playerPosition.x && dX > dZ)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 131; // 2
                                                }
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 100;
                                                }
                                                break;



                                                default:
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = mWorld->invId[27+barPosition];
                                                break;
                                                }

                                            if(mWorld->invAm[27+barPosition]==1)
                                            {
                                                mWorld->invAm[27+barPosition]= -1;
                                                mWorld->invId[27+barPosition]= -1;
                                                mWorld->invSt[27+barPosition]= 0;
                                            }
                                            else
                                            {
                                                mWorld->invAm[27+barPosition]-= 1;
                                            }

                                            }
                                    }
                                    else
                                    {
                                        if(mWorld->invId[27+barPosition] == 286)
                                        {
                                            if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 79)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 134;
                                                mWorld->invAm[27+barPosition] -= 1;
                                                if(mWorld->invAm[27+barPosition] == 0)
                                                {
                                                   mWorld->invAm[27+barPosition] = -1;
                                                   mWorld->invSt[27+barPosition] = 0;
                                                   mWorld->invId[27+barPosition] = -1;
                                                }
                                            }
                                        }
                                    }


                                    if (mWorld->invId[27+barPosition]==39)
                                    {
                                        for(int x1 = testPos2.x-2; x1 < testPos2.x+2; x1++)
                                        {
                                        for(int y1 = testPos2.y-2; y1 < testPos2.y+2; y1++)
                                        {
                                        for(int z1 = testPos2.z-2; z1 < testPos2.z+2; z1++)
                                        {
                                            if (mWorld->GetBlock(x1,y1,z1) == 4)
                                            {
                                                mWorld->GetBlock(x1,y1,z1) = 0;
                                            }
                                        }
                                        }
                                        }
                                    }

                                    mWorld->blockPlaced += 1;

                                    int chunkTarget = mWorld->getChunkId(testPos2);

                                    if(chunkTarget != -1)
                                    {
                                        mSoundMgr->PlayPlopSound();

                                        //rebuild
                                        if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
                                        {
                                            mWorld->RebuildChunksLight(testPos2,chunkTarget,(mWorld->invId[27+barPosition]));
                                        }
                                        else
                                        {
                                            //check if there are light sources nearby
                                            mWorld->UpdateLightAreaIn(testPos2);

                                            //rebuild chunks
                                            mWorld->rebuildChunk(chunkTarget);
                                            mWorld->rebuildTransparentChunk(chunkTarget);
                                            //rebuild chunks that are near this chunk
                                            mWorld->rebuildNearestChunks(chunkTarget,testPos2);
                                        }
                                    }
                                }

                                fppCam->needUpdate = true;
                            }
                        }
                    }

                    break;
                }
            }


        }

        if(keyPressed(InputHelper::Instance()->getButtonToAction(13)))
        {
            //remove cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we are takin our positiona and view vector
            Vector3 testPos2;

            testPos2 = Vector3(-1,-1,-1);

            //we are moving slowly to the target +=0.5
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos2 = fppCam->m_vPosition + (rayDir * i);

                //check if we touch something
                if(mWorld->BlockEditable(testPos2.x,testPos2.y,testPos2.z))
                {
                    if (startDt == false)
                    {
                        testPos1.x  = testPos2.x;
                        testPos1.y  = testPos2.y;
                        testPos1.z  = testPos2.z;
                        switch(mWorld->BlockMaterial(testPos2.x,testPos2.y,testPos2.z))
                        {
                            case 2:

                            dET = 72;
                            if(mWorld->invId[27+barPosition] == 250)
                            {
                                dS = 1.5;
                            }
                            else if(mWorld->invId[27+barPosition] == 251)
                            {
                                dS = 3;
                            }
                            else if(mWorld->invId[27+barPosition] == 252)
                            {
                                dS = 5;
                            }
                            else if(mWorld->invId[27+barPosition] == 253)
                            {
                                dS = 8;
                            }
                            else
                            {
                                dS = 0.5;
                            }
                            break;

                            case 1:

                            dET = 40;
                            if(mWorld->invId[27+barPosition] == 265)
                            {
                                dS = 3;
                            }
                            else if(mWorld->invId[27+barPosition] == 266)
                            {
                                dS = 5;
                            }
                            else if(mWorld->invId[27+barPosition] == 267)
                            {
                                dS = 6;
                            }
                            else if(mWorld->invId[27+barPosition] == 268)
                            {
                                dS = 8;
                            }
                            else
                            {
                                dS = 1.5;
                            }
                            break;

                            case 3:

                            dET = 55;
                            if(mWorld->invId[27+barPosition] == 260)
                            {
                                dS = 6;
                            }
                            else if(mWorld->invId[27+barPosition] == 261)
                            {
                                dS = 8;
                            }
                            else if(mWorld->invId[27+barPosition] == 262)
                            {
                                dS = 10;
                            }
                            else if(mWorld->invId[27+barPosition] == 263)
                            {
                                dS = 12;
                            }
                            else
                            {
                                dS = 2.5;
                            }
                            break;

                            case 4:

                            dET = 41;
                            if(mWorld->invId[27+barPosition] == 275)
                            {
                                dS = 12;
                            }
                            else
                            {
                                dS = 5;
                            }
                            break;

                            default:
                            dET = 15;
                            dS = 1;
                            break;

                        }
                        dT = 0;
                        startDt = true;
                    }

                }
            }
        }

        //remove cube
        if(keyHold(InputHelper::Instance()->getButtonToAction(13)))
        {
            if (startDt == true)
            {



            dT < dET ? dT += dS : dT = 0;


                    //remove block99
                    if (dT >= dET)
                    {
                        bool wasLight = false;
                        block_t oldBlock = 0;

                    if(mWorld->LightSourceBlock(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z)))//if it's light block
                    {
                        oldBlock = mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z);
                        wasLight = true;
                    }


                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 100 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 131 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 132 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 133) // if it is chest
                        {
                            chestId = FindChestId(testPos1.x,testPos1.y,testPos1.z);
                            if(chestId != -1)
                            {
                                for(int i = 0; i <= 17; i++)
                                {
                                    mWorld->chestSlotId[(chestId*18)+i] = -1;
                                    mWorld->chestSlotAm[(chestId*18)+i] = -1;
                                    mWorld->chestSlotSt[(chestId*18)+i] = 0;
                                }
                                mWorld->chestX[chestId] = -1;
                                mWorld->chestY[chestId] = -1;
                                mWorld->chestZ[chestId] = -1;
                            }
                        }
                    //mWorld->BlockSoundAtPos(testPos1);

                        if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 275)
                        {
                            mWorld->invAm[27+barPosition] -= 1;

                            if(mWorld->invAm[27+barPosition] == 0)
                            {
                                mWorld->invId[27+barPosition] = -1;
                                mWorld->invAm[27+barPosition] = -1;
                                mWorld->invSt[27+barPosition] = 0;
                            }
                        }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) != 9 && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) != 136)
                    {
                        PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                    }
                    else
                    {
                        if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 9)
                        {
                            if(mWorld->invId[27+barPosition] != 275)
                            {

                                if (rand() % 20 == 1)
                                {
                                    PutInInventory(284,1,1);
                                }

                                if (rand() % 20 >= 17)
                                {
                                    PutInInventory(121,1,1);
                                }

                            }
                            else
                            {
                                PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                            }
                        }
                        else
                        {
                            PutInInventory(287,1,1);
                            PutInInventory(286,1 + rand() % 2,1);
                        }
                    }





                    mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                    mWorld->blockDestroyed += 1;
                    int   chunkTarget = mWorld->getChunkId(testPos1);

                    //check if this block is a support for light block
                    mWorld->CheckForTorchSupport(testPos1.x,testPos1.y,testPos1.z,mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z));


                    //before rebuilding update light info
                    if(wasLight)
                    {
                        mWorld->RemoveLigtSourceAtPosition(testPos1.x,testPos1.y,testPos1.z,oldBlock);
                    }

                    if(chunkTarget != -1)
                    {
                        //rebuild
                        if(wasLight)
                        {
                            mWorld->RebuildChunksLight(testPos1,chunkTarget,oldBlock);
                        }
                        else
                        {
                            //check if there are light sources nearby
                            mWorld->UpdateLightAreaIn(testPos1);

                            //rebuild chunks
                            mWorld->rebuildChunk(chunkTarget);
                            mWorld->rebuildTransparentChunk(chunkTarget);
                            mWorld->rebuildNearestChunks(chunkTarget,testPos1);
                        }
                    }

                    fppCam->needUpdate = true;
                    testPos1 = Vector3(-1,-1,-1);
                    startDt = false;
                    dT = 0;
                    dET = 0;
                    dS = 0;
                    chestId = -1;
                    return;
                    }
                }

        }
        else
        {
            if (startDt != false)
            {
                dT = 0;
                startDt = false;
                chestId = -1;
            }

        }


        //jump
        if(keyHold(InputHelper::Instance()->getButtonToAction(12)))
        {
            if (headInWater || headInLava)	//Legit swimming
            {
                if (walkingOnGround)
                {
                    jumping = true;
                }else
                {
                    playerVelocity.y = 0.4 * JUMPVELOCITY;
                    walkingOnGround = false;
                }
            }
            if ((!headInWater || !headInLava) && !walkingOnGround && (footInWater || footInLava))	//Your above he water, so Jump out
            {
                playerVelocity.y = 0.9 * JUMPVELOCITY;
                walkingOnGround = false;
            }
            if(walkingOnGround)	//Just in case...
            {
                jumping = true;
            }
            else
                jumping = false;	//Don't bounce
        }

        }

        //INVENTORY

        else
        {
        //Craft item
        if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
        {
            if(craft2xEn == true)
            {
            if(craftItemId != -1)
            {

                if(mWorld->mId == craftItemId)
                {
                    if(craftItemSt == 1)
                    {
                        if(mWorld->mAm+craftItemAm <= 64)
                        {
                            for(int i = 0; i <= 3; i++)
                            {
                                craftSlotAm[i] -= 1;
                                if(craftSlotAm[i] == 0)
                                {
                                    craftSlotId[i] = -1;
                                    craftSlotAm[i] = -1;
                                    craftSlotSt[i] = 0;
                                }
                            }

                            mWorld->mAm += craftItemAm;

                            CraftItem2x2();
                        }
                    }
                }

                if(mWorld->mId == -1)
                {
                    for(int i = 0; i <= 3; i++)
                    {
                        craftSlotAm[i] -= 1;
                        if(craftSlotAm[i] == 0)
                        {
                            craftSlotId[i] = -1;
                            craftSlotAm[i] = -1;
                            craftSlotSt[i] = 0;
                        }
                    }
                    mWorld->mId = craftItemId;
                    mWorld->mAm = craftItemAm;
                    mWorld->mSt = craftItemSt;

                    CraftItem2x2();

                }
            }
            }


            if(craft3xEn == true)
            {
            if(craftItemId3 != -1)
            {

                if(mWorld->mId == craftItemId3)
                {
                    if(craftItemSt3 == 1)
                    {
                        if(mWorld->mAm+craftItemAm3 <= 64)
                        {
                            for(int i = 0; i <= 8; i++)
                            {
                                craftSlotAm3[i] -= 1;
                                if(craftSlotAm3[i] == 0)
                                {
                                    craftSlotId3[i] = -1;
                                    craftSlotAm3[i] = -1;
                                    craftSlotSt3[i] = 0;
                                }
                            }

                            mWorld->mAm += craftItemAm3;

                            CraftItem3x3();
                        }
                    }
                }

                if(mWorld->mId == -1)
                {
                    for(int i = 0; i <= 8; i++)
                    {
                        craftSlotAm3[i] -= 1;
                        if(craftSlotAm3[i] == 0)
                        {
                            craftSlotId3[i] = -1;
                            craftSlotAm3[i] = -1;
                            craftSlotSt3[i] = 0;
                        }
                    }
                    mWorld->mId = craftItemId3;
                    mWorld->mAm = craftItemAm3;
                    mWorld->mSt = craftItemSt3;

                    CraftItem3x3();

                }
            }
            }
        }

        //switch right
        if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
        {
            if (craftEn == 0)
            {
                invXPosition != 8 ? invXPosition ++ : invXPosition = 8;

                selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
            }
            else
            {
                if(craft2xEn == 1)
                {
                    invXPosition != 1 ? invXPosition ++ : invXPosition = 1;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),80+(invYPosition * 35));
                }
                if(craft3xEn == 1)
                {
                    invXPosition != 2 ? invXPosition ++ : invXPosition = 2;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }
                if(chestEn == 1)
                {
                    invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }

            }

        }

        //switch left
        if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
        {
            if (craftEn == 0)
            {
                invXPosition != 0 ? invXPosition -- : invXPosition = 0;

                selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
            }
            else
            {
                invXPosition != 0 ? invXPosition -- : invXPosition = 0;
                if(craft2xEn == 1)
                {
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),80+(invYPosition * 35));
                }
                if(craft3xEn == 1)
                {
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }
                if(chestEn == 1)
                {
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }
            }



        }

        //switch down
        if(keyPressed(InputHelper::Instance()->getButtonToAction(11)))
        {
            if (craftEn == 0)
            {
                invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
                selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
            }
            else
            {
                if (craft2xEn == 1)
                {
                    if (invYPosition == 1)
                    {
                        craftEn = 0;
                        invYPosition = 0;
                        invXPosition = 0;
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
                        return;
                    }
                    invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),80+(invYPosition * 35));
                }

                if (craft3xEn == 1)
                {
                    if (invYPosition == 2)
                    {
                        craftEn = 0;
                        invYPosition = 0;
                        invXPosition = 0;
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
                        return;
                    }
                    invYPosition != 2 ? invYPosition ++ : invYPosition = 2;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }

                if (chestEn == 1)
                {
                    if (invYPosition == 1)
                    {
                        craftEn = 0;
                        invYPosition = 0;
                        invXPosition = 0;
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
                        return;
                    }
                    invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                    selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                }
            }
        }

        //switch up
        if(keyPressed(InputHelper::Instance()->getButtonToAction(10)))
        {
            if (craftEn == 0)
            {

                if (invYPosition == 0)
                {
                    craftEn = 1;
                    invXPosition = 0;
                    invYPosition = 0;
                    if(craft2xEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),80+(invYPosition * 35));
                    }
                    if(craft3xEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                    }
                    if(chestEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                    }
                    return;
                }
                invYPosition != 0 ? invYPosition -- : invYPosition = 0;
                selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
            }
            else
            {
                invYPosition != 0 ? invYPosition -- : invYPosition = 0;

                    if(craft2xEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),80+(invYPosition * 35));
                    }
                    if(craft3xEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                    }
                    if(chestEn == 1)
                    {
                        selectInvSprite->SetPosition(100 + (invXPosition * 35),45+(invYPosition * 35));
                    }
            }


        }

        if((keyPressed(InputHelper::Instance()->getButtonToAction(12))))
        {
            invEn = false;
            craft2xEn = false;
            craft3xEn = false;
            chestEn = 0;
            invXPosition = 0;
            invYPosition = 0;
            chestId = -1;
            selectInvSprite->SetPosition(100 + (invXPosition * 35),150+(invYPosition * 35));
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if (craftEn == 0)
            {
            if (mWorld->mId == -1)
            {
                if (mWorld->invId[invYPosition*9 + invXPosition] != -1)
                {
                    mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
                    mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
                    mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
                    mWorld->invId[invYPosition*9 + invXPosition] = -1;
                    mWorld->invAm[invYPosition*9 + invXPosition] = -1;
                    mWorld->invSt[invYPosition*9 + invXPosition] = 0;
                }
            }
            else
            {
                if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
                {
                    mWorld->invId[invYPosition*9 + invXPosition]=mWorld->mId;
                    mWorld->invAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                    mWorld->invSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                    mWorld->mId = -1;
                    mWorld->mAm = -1;
                    mWorld->mSt = 0;
                }

                if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                {
                    if(mWorld->invSt[invYPosition*9 + invXPosition] == 1)
                    {
                    if (mWorld->invAm[invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                    {
                        mWorld->invAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                    }
                    else
                    {
                        mWorld->mAm = (mWorld->invAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                        mWorld->invAm[invYPosition*9 + invXPosition]=64;
                    }
                    }
                }
            }

            }
            else
            {
            if (craft2xEn == 1)
            {
            if (mWorld->mId == -1)
            {
                if (craftSlotId[invYPosition*2 + invXPosition] != -1)
                {
                    mWorld->mId = craftSlotId[invYPosition*2 + invXPosition];
                    mWorld->mAm = craftSlotAm[invYPosition*2 + invXPosition];
                    mWorld->mSt = craftSlotSt[invYPosition*2 + invXPosition];
                    craftSlotId[invYPosition*2 + invXPosition] = -1;
                    craftSlotAm[invYPosition*2 + invXPosition] = -1;
                    craftSlotSt[invYPosition*2 + invXPosition] = 0;
                }
            }
            else
            {
                if (craftSlotId[invYPosition*2 + invXPosition] == -1)
                {
                    craftSlotId[invYPosition*2 + invXPosition]=mWorld->mId;
                    craftSlotAm[invYPosition*2 + invXPosition]=mWorld->mAm;
                    craftSlotSt[invYPosition*2 + invXPosition]=mWorld->mSt;
                    mWorld->mId = -1;
                    mWorld->mAm = -1;
                    mWorld->mSt = 0;
                }

                if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                {
                    if(craftSlotSt[invYPosition*2 + invXPosition] == 1)
                    {
                    if (craftSlotAm[invYPosition*2 + invXPosition]+mWorld->mAm < 64)
                    {
                        craftSlotAm[invYPosition*2 + invXPosition]+=mWorld->mAm;
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                    }
                    else
                    {
                        mWorld->mAm = (craftSlotAm[invYPosition*2 + invXPosition] + mWorld->mAm) - 64;
                        craftSlotAm[invYPosition*2 + invXPosition]=64;
                    }
                    }
                }
            }
            }
            if (craft3xEn == 1)
            {
            if (mWorld->mId == -1)
            {
                if (craftSlotId3[invYPosition*3 + invXPosition] != -1)
                {
                    mWorld->mId = craftSlotId3[invYPosition*3 + invXPosition];
                    mWorld->mAm = craftSlotAm3[invYPosition*3 + invXPosition];
                    mWorld->mSt = craftSlotSt3[invYPosition*3 + invXPosition];
                    craftSlotId3[invYPosition*3 + invXPosition] = -1;
                    craftSlotAm3[invYPosition*3 + invXPosition] = -1;
                    craftSlotSt3[invYPosition*3 + invXPosition] = 0;
                }
            }
            else
            {
                if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
                {
                    craftSlotId3[invYPosition*3 + invXPosition]=mWorld->mId;
                    craftSlotAm3[invYPosition*3 + invXPosition]=mWorld->mAm;
                    craftSlotSt3[invYPosition*3 + invXPosition]=mWorld->mSt;
                    mWorld->mId = -1;
                    mWorld->mAm = -1;
                    mWorld->mSt = 0;
                }

                if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                {
                    if(craftSlotSt3[invYPosition*3 + invXPosition] == 1)
                    {
                    if (craftSlotAm3[invYPosition*3 + invXPosition]+mWorld->mAm < 64)
                    {
                        craftSlotAm3[invYPosition*3 + invXPosition]+=mWorld->mAm;
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                    }
                    else
                    {
                        mWorld->mAm = (craftSlotAm3[invYPosition*3 + invXPosition] + mWorld->mAm) - 64;
                        craftSlotAm3[invYPosition*3 + invXPosition]=64;
                    }
                    }
                }
            }
            }
            //Chest
            if (chestEn == 1)
            {
            if (mWorld->mId == -1)
            {
                if (mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] != -1)
                {
                    mWorld->mId = mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition];
                    mWorld->mAm = mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition];
                    mWorld->mSt = mWorld->chestSlotSt[(chestId*18)+invYPosition*9 + invXPosition];
                    mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] = -1;
                    mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition] = -1;
                    mWorld->chestSlotSt[(chestId*18)+invYPosition*9 + invXPosition] = 0;
                }
            }
            else
            {
                if (mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] == -1)
                {
                    mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition]=mWorld->mId;
                    mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition]=mWorld->mAm;
                    mWorld->chestSlotSt[(chestId*18)+invYPosition*9 + invXPosition]=mWorld->mSt;
                    mWorld->mId = -1;
                    mWorld->mAm = -1;
                    mWorld->mSt = 0;
                }

                if (mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] == mWorld->mId)
                {
                    if(mWorld->chestSlotSt[(chestId*18)+invYPosition*9 + invXPosition] == 1)
                    {
                    if (mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                    {
                        mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition]+=mWorld->mAm;
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                    }
                    else
                    {
                        mWorld->mAm = (mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                        mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition]=64;
                    }
                    }
                }
            }
            }


            }
            if (craft2xEn == 1)
            {
                CraftItem2x2();
            }

            if (craft3xEn == 1)
            {
                CraftItem3x3();
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_SQUARE))
        {
            if(mWorld->mSt == 1)
            {
            if (craftEn == 0)
            {
                if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                {
                    if (mWorld->invAm[invYPosition*9 + invXPosition] != 64)
                    {
                        mWorld->invAm[invYPosition*9 + invXPosition] += 1;

                        mWorld->mAm -= 1;

                        if(mWorld->mAm == 0)
                        {
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                        }
                    }

                }

            if (mWorld->mId != -1)
            {
               if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
               {
                   mWorld->invId[invYPosition*9 + invXPosition] = mWorld->mId;
                   mWorld->invAm[invYPosition*9 + invXPosition] = 1;
                   mWorld->invSt[invYPosition*9 + invXPosition] = 1;

                   mWorld->mAm -= 1;

                   if(mWorld->mAm == 0)
                   {
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                   }
               }
           }
        }
        else
        {
        if (craft2xEn == 1)
        {
            if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                {
                    if (craftSlotAm[invYPosition*2 + invXPosition] != 64)
                    {
                        craftSlotAm[invYPosition*2 + invXPosition] += 1;

                        mWorld->mAm -= 1;

                        if(mWorld->mAm == 0)
                        {
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                        }
                    }

                }

            if (mWorld->mId != -1)
            {
               if (craftSlotId[invYPosition*2 + invXPosition] == -1)
               {
                   craftSlotId[invYPosition*2 + invXPosition] = mWorld->mId;
                   craftSlotAm[invYPosition*2 + invXPosition] = 1;
                   craftSlotSt[invYPosition*2 + invXPosition] = 1;

                   mWorld->mAm -= 1;

                   if(mWorld->mAm == 0)
                   {
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                   }
               }
           }
        }

        if (craft3xEn == 1)
        {
            if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                {
                    if (craftSlotAm3[invYPosition*3 + invXPosition] != 64)
                    {
                        craftSlotAm3[invYPosition*3 + invXPosition] += 1;

                        mWorld->mAm -= 1;

                        if(mWorld->mAm == 0)
                        {
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                        }
                    }

                }

            if (mWorld->mId != -1)
            {
               if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
               {
                   craftSlotId3[invYPosition*3 + invXPosition] = mWorld->mId;
                   craftSlotAm3[invYPosition*3 + invXPosition] = 1;
                   craftSlotSt3[invYPosition*3 + invXPosition] = 1;

                   mWorld->mAm -= 1;

                   if(mWorld->mAm == 0)
                   {
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                   }
               }
           }
        }

    /* Chest */
    if (chestEn == 1)
        {
            if (mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] == mWorld->mId)
                {
                    if (mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition] != 64)
                    {
                        mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition] += 1;

                        mWorld->mAm -= 1;

                        if(mWorld->mAm == 0)
                        {
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                        }
                    }

                }

            if (mWorld->mId != -1)
            {
               if (mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] == -1)
               {
                   mWorld->chestSlotId[(chestId*18)+invYPosition*9 + invXPosition] = mWorld->mId;
                   mWorld->chestSlotAm[(chestId*18)+invYPosition*9 + invXPosition] = 1;
                   mWorld->chestSlotSt[(chestId*18)+invYPosition*9 + invXPosition] = 1;

                   mWorld->mAm -= 1;

                   if(mWorld->mAm == 0)
                   {
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                   }
               }
           }
        }

        }


        }
            if (craft2xEn == 1)
            {
                CraftItem2x2();
            }

            if (craft3xEn == 1)
            {
                CraftItem3x3();
            }
        }
    }
    }
    else if(menuState == 1) //menu state
    {
        //turn off menu with the same key
        if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
        {
            menuState = 0;
            menuOptions = false;
            optionsMenuPos = 0;
            selectPos = 0;
        }

        //menu keys
        if(menuOptions)
        {
            //up, down
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                optionsMenuPos--;
                if(optionsMenuPos < 0)
                    optionsMenuPos = 6;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                optionsMenuPos++;
                if(optionsMenuPos > 6)
                    optionsMenuPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            //back
            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 0;
                menuOptions = false;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                //fly

                //devmode
                if(optionsMenuPos == 1)
                    devMode = !devMode;

                //take screenshot
                if(optionsMenuPos == 2)
                    makeScreen = true;

                //rename
                if(optionsMenuPos == 3)
                {
                    unsigned short test[128];
                    unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                    if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                    {
                        std::string newWorldName = "";
                        for(int j = 0; test[j]; j++)
                        {
                            unsigned c = test[j];

                            if(32 <= c && c <= 127) // print ascii only
                                newWorldName += c;
                        }

                        sprintf(mWorld->worldName,"%s",newWorldName.c_str());
                    }
                }

                if(optionsMenuPos == 4)
                    mSoundMgr->playerSounds = !mSoundMgr->playerSounds;

                if(optionsMenuPos == 5)
                {
                    canHeadBob = !canHeadBob;

                    bobCycle = 0.0f;
                }


                if(optionsMenuPos == 6)
                {
                    //mWorld->freezeDayTime = !mWorld->freezeDayTime;
                    menuState = 2;
                    optionsMenuPos = 0;
                    selectPos = 0;
                }

            }
        }
        else
        {
            //up, down
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                selectPos--;
                if(selectPos < 0)
                    selectPos = 5;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                selectPos++;
                if(selectPos > 5)
                    selectPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 0;
                selectPos = 0;
                optionsMenuPos = 0;
                menuOptions = false;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(selectPos == 0)//resume
                {
                    menuState = 0;
                }
                if(selectPos == 1)//options
                {
                    optionsMenuPos = 0;
                    menuOptions = true;
                }
                if(selectPos == 2)//options
                {
                    menuState = 3;
                    selectPos = 0;
                }
                if(selectPos == 3)//save
                {
                    mWorld->sunTime = sunTime;
                    mWorld->SaveCompressedWorld(saveFileName.c_str());
                    menuState = 0;
                }
                if(selectPos == 4)//save end exit
                {
                    //save
                    mWorld->sunTime = sunTime;
                    mWorld->SaveCompressedWorld(saveFileName.c_str());
                    //exit
                    sManager->PopState();
                }
                if(selectPos == 5)//exit
                {
                    //exit
                    sManager->PopState();
                }
            }
        }
    }
    if (menuState == 2)
    {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                selectPos--;
                if(selectPos < 0)
                    selectPos = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                selectPos++;
                if(selectPos > 2)
                    selectPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 0;
                menuState = 1;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(selectPos == 1)//resume
                {
                    mWorld->skyRender = !mWorld->skyRender;
                }

            }


        if(selectPos == 0)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
            {
                if(mWorld->fogLevel != 3)
                {
                  mWorld->fogLevel++;
                  mSoundMgr->PlayMenuSound();
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
            {
                if(mWorld->fogLevel != 0)
                {
                  mWorld->fogLevel--;
                  mSoundMgr->PlayMenuSound();
                }
            }
        }
    }
    if (menuState == 3)
    {


            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 0;
                menuState = 1;
            }


    }
    }
    else
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
                playerPosition.x = newPlayerPos.x;
                playerPosition.y = newPlayerPos.y;
                playerPosition.z = newPlayerPos.z;

            mWorld->UpdatePlayerZoneBB(playerPosition);	//Move player back to original spawn point
            fppCam->m_vPosition = playerPosition;
            cameraSpeed = 2.0/ 60.0f;	//Possibly fix camera bug
            fppCam->RotateView(0,0,90,0);
            mWorld->HP = 20;
            mWorld->HG = 20;
        }
    }
}


void StatePlay::Update(StateManager* sManager)
{
    if(menuState == 0)//game state
    {
        {
            tick2 < 40 ? tick2 += 1 : tick2 = 0;
            if (tick2==38)
            {
                for(int i = chunks*1; i < (chunks+1)*1; i++)
                {
                    mWorld->UpdateChunkBlocks(chunks);
                    mWorld->rebuildChunk(chunks);
                    mWorld->rebuildTransparentChunk(chunks);
                }
                chunks += 1;
                if (chunks == 510)
                {
                    chunks = 0;
                }
            }
        }

        {
            tick < 2000 ? tick ++ : tick = 0;
            if(tick == 980)
            {
                HungerTime();
            }

            tickH < 500 ? tickH ++ : tickH = 0;
            if(tickH == 480)
            {
                HealthTime();
            }


            if (hurt_time > 0)
            {
                hurt_time -= 0.1f;
            }
            if (hurt_time <= 0)
            {
                hurt = false;
            }
        }

        if(walkingOnGround == false)
        {
            yy += 1;
        }

        if(fppCam->needUpdate)
        {
            showCube = false;

            //show pick cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we take position and view vector
            Vector3 testPos ;

            //moving slowly to the target
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);

                //check if we touching something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z))
                {
                    //if yes then show pick cube
                    cubePos.x = (int)testPos.x + 0.5f;
                    cubePos.y = (int)testPos.y + 0.5f;
                    cubePos.z = (int)testPos.z + 0.5f;

                    showCube = true;
                    break;
                }
            }

        }

        int soundBlockType = -1;

        //update player position
        if(dt < 0.1f)
        {
            yy = 0;
            Vector3 delta = fppCam->m_vView - fppCam->m_vPosition;
            playerPosition = fppCam->m_vPosition;

            //gravity
            Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
            Vector3 legsPosition = playerPosition + Vector3(0.0f, -1.0f, 0.0f);
            Vector3 headPosition = playerPosition + Vector3(0.0f, 0.1f, 0.0f);

            //foot in water
            if(mWorld->PlayerInWater(legsPosition))
                footInWater = true;
            else
                footInWater = false;

            //check if head is is in the water
            if(mWorld->PlayerInWater(headPosition))
            {
                //change gravity
                playerVelocity.y += (GRAVITY/3.0f) * dt;
                headInWater = true;
            }
            else
            {
                headInWater = false;
                playerVelocity.y += GRAVITY * dt;
            }

            if(mWorld->PlayerInLava(legsPosition))
                footInLava = true;
            else
                footInLava = false;

            //check if head is is in the Lava
            if(mWorld->PlayerInLava(headPosition))
            {
                //change gravity
                playerVelocity.y += (GRAVITY/3.0f) * dt;
                headInLava = true;
            }
            else
            {
                headInLava = false;
                playerVelocity.y += GRAVITY * dt;
            }

            //check if we are standing on ground
            if(mWorld->SolidAtPointForPlayer(footPosition) || mWorld->SolidAtPointForPlayer(headPosition))
            {
                walkingOnGround = true;
                soundBlockType = mWorld->BlockSoundAtPos(footPosition);

                // If the player has their head stuck in a block, push them down.
                if (mWorld->SolidAtPointForPlayer(headPosition))
                {
                    int blockIn = (int)(headPosition.y);
                    playerPosition.y = (float)(blockIn - 0.15f);
                }

                // If the player is stuck in the ground, bring them out.
                // This happens because we're standing on a block at -1.5, but stuck in it at -1.4, so -1.45 is the sweet spot.
                if (mWorld->SolidAtPointForPlayer(footPosition))
                {
                    int blockOn = (int)(footPosition.y);
                    playerPosition.y = (float)(blockOn + 1 + 1.45f);
                }


                playerVelocity.y = 0.0f;

                //dodatkowa logika podczas stania na klocku
                //jump
                if(jumping)
                {
                    playerVelocity.y = 1.2f * JUMPVELOCITY;
                    jumping = false;
                    walkingOnGround = false;
                }

            }
            else
            {

                walkingOnGround = false;
            }

            //update position
            if(!canFly)
                playerPosition += playerVelocity * dt;
            else
                playerVelocity.y = 0.0f;


            //collision with walls
            isWalking = false;
            Vector3 moveVector = fppCam->m_vVelocity;

            if(moveVector.x != 0.0f || moveVector.z != 0.0f)
            {
                if(TryToMove(moveVector,dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(0,0,moveVector.z),dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(moveVector.x,0,0),dt))
                {
                    isWalking = true;
                }
            }


            //update camera
            fppCam->m_vPosition = playerPosition;
            fppCam->m_vView = fppCam->m_vPosition + delta;
            fppCam->m_vVelocity = Vector3(0,0,0);
            fppCam->needUpdate = true;
        }

        if(fppCam->needUpdate)
        {
            mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
        }

        //walking sound
       if(isWalking && walkingOnGround && (!footInWater || !footInLava))
		{
			if(walkSoundAccu > 0.5f || walkSoundAccu == 0.0f)
			{
				mSoundMgr->PlayWalkSound(soundBlockType);
				walkSoundAccu = 0.0f;
			}
			walkSoundAccu += dt;

			if(canHeadBob)
			{
                bobCycle += dt*2;
                if(bobCycle>2.1f)
                {
                    bobCycle=0.0f;
                }
                float bobSine = sinf(bobCycle*180.0f*DEG_TO_RAD);

                fppCam->m_vOffset = Vector3(0.0f,0.05f*bobSine,0.0f);

			}

		}
		else
		{
			walkSoundAccu = 0.0f;
			fppCam->m_vOffset = Vector3(0.0f,0.0f,0.0f);
            if(bobCycle < 0.54)
            {
                bobCycle > 0.0f ? bobCycle -= 0.08 : bobCycle = 0;
            }
            if(bobCycle > 0.54 && bobCycle < 1.075)
            {
                bobCycle < 1.064f ? bobCycle += 0.08 : bobCycle = 0;
            }
			if (bobCycle > 1.075 && bobCycle < 1.62)
            {
                bobCycle > 1.084f ? bobCycle -= 0.08 : bobCycle = 0;
            }
            if ( bobCycle > 1.62)
            {
                bobCycle < 2.15 ? bobCycle += 0.08 : bobCycle = 0;
            }

		}
    }

    mWorld->UpdateWorldTime(dt);

    if(!mWorld->freezeDayTime)
	{
		//update skydome - every hour
			skyDome->timeOfDay = mWorld->worldDayTime * 0.041666f;

			//update sky and sun light time
			//23 000 morning
			//62 500 evening
			//39500 whole day
			//16 normal hours of day
				//2468,75 - hour / 50 seconds(hour in game)
				//49,375
			//8 hours of night
				//4937,5 - hour / 50 seconds
				//98,75  in the night

			if(mWorld->worldDayTime >= 5.0f && mWorld->worldDayTime < 21.0f)
			{
				sunTime += 49.375f * dt;//72
				if(!sunMoonSwitch)//switch to sun texture and reset position
				{
					skyLight->SetTexture(TextureManager::Instance()->GetTextureNumber("Assets/Lamecraft/sun.png"));
					sunTime = 21600.0f;//6 am
					sunMoonSwitch = true;
				}
			}else
			{
				sunTime += 98.75 * dt;//72
				if(sunMoonSwitch)//switch to sun texture and reset position
				{
					skyLight->SetTexture(TextureManager::Instance()->GetTextureNumber("Assets/Lamecraft/moon.png"));

					sunTime = 21600.0f;//6 am
					sunMoonSwitch = false;
				}
			}
	}
}


void StatePlay::Draw(StateManager* sManager)
{

    {
        time_z < 1000 ? time_z += 1 : time_z = 0;

        if (time_z==600)
        {
        chunkId = mWorld->getChunkId(playerPosition);
        mWorld->UpdateChunkBlocks(chunkId);
        mWorld->rebuildChunk(chunkId);
        mWorld->rebuildTransparentChunk(chunkId);
            short r = rand() % 5;

            if (r==2)
            {
                if (playerPosition.y < 50)
                {
                    mSoundMgr->PlayCaveSound();
                }
            }
        }
    }
	//start rendering
	bool needUpdate = fppCam->needUpdate;
	mRender->StartFrame();

	//draw sky and sun/moon
	{
		sceGumPushMatrix();
		ScePspFVector3 move = {-64,-64,-64};
		sceGumTranslate(&move);

		//draw skydome
		if (mWorld->skyRender == true)
        {
            skyDome->Render();
        }
            skyLight->Render();

        //skyClouds->Render();

		//draw sun/moon
		skyLight->UpdateLightSource(skyLight->TimeToAngle(sunTime));

		sceGumPopMatrix();
	}

	TextureManager::Instance()->SetTextureModeulate(texture);

	//draw level

	sceGuFog( (mWorld->fogLevel + 1) * 10.0f,(mWorld->fogLevel + 1) * 40.0f,GU_COLOR(mWorld->fogColor.x,mWorld->fogColor.y,mWorld->fogColor.z,1.0f));	// Fog parameters 100.75
	//sceGuAmbientColor(0xff282828);
	//sceGuFog( 0.0f, 128.75f, 0x00CCCCff );	// Fog parameters
	sceGuEnable(GU_FOG );	// Enable fog

	sceGumPushMatrix();
	mWorld->drawWorld(fppCam->mFrustum,needUpdate);
	sceGumPopMatrix();

	sceGuDisable(GU_FOG );	// disable fog

	if(makeScreen)
	{
		//end frame now to update frame buffer
		mRender->EndFrame();
		//make screenshot
		mRender->TakeNextScreenshot();
		makeScreen = false;
	}

	//render pick cube
	if(showCube)
	{
		//cubePos = fppCam->m_vPosition;
		sceGumPushMatrix();

		ScePspFVector3 move = {cubePos.x,cubePos.y,cubePos.z};
		sceGumTranslate(&move);

		sceGuEnable(GU_BLEND);
		sceGuColor(0xFFFFFFFF);

		//GU_COLOR()
		mRender->Draw(cubeModel);
		sceGuDisable(GU_BLEND);

		sceGumPopMatrix();
	}

	//render cube in right hand
	{
	    if(mWorld->invId[27+barPosition] != -1)
        {
        if(mWorld->invId[27+barPosition] < 250)
        {
		TextureManager::Instance()->SetTextureModeulate(texture);
		sceGumPushMatrix();

		//set view matrix to identity
		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		//translate
		float cubeBob = + sinf(bobCycle*180.0f*DEG_TO_RAD)*-0.1f+0.05f;
		ScePspFVector3 move = {0.47f+cubeBob+shift_x,-0.32f+shift_y,-0.7f};
		sceGumTranslate(&move);
		//rotate


		sceGumRotateX(0.2792f);
		sceGumRotateY(0.3853f);
		//scale
		ScePspFVector3 scale = {0.25f,0.25f,0.25f};
		sceGumScale(&scale);

		//draw cube
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		mWorld->drawCubes(mWorld->invId[27+barPosition]);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

		sceGumMatrixMode(GU_MODEL);
		sceGumPopMatrix();
        }

        if(mWorld->invId[27+barPosition] >= 250)
        {
		TextureManager::Instance()->SetTextureModeulate(texture);
		sceGumPushMatrix();

		//set view matrix to identity
		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		//translate
		float cubeBob = + sinf(bobCycle*180.0f*DEG_TO_RAD)*-0.1f+0.05f;
		ScePspFVector3 move = {0.36f+cubeBob+shift_x,-0.17f+shift_y,-0.7f};
		sceGumTranslate(&move);
		//rotate


		sceGumRotateX(0.2792f);
		sceGumRotateY(0.3853f);
		sceGumRotateZ(3);
		//scale
		ScePspFVector3 scale = {0.25f,0.25f,0.25f};
		sceGumScale(&scale);

		//draw cube
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		mWorld->drawItems(mWorld->invId[27+barPosition]);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

		sceGumMatrixMode(GU_MODEL);
		sceGumPopMatrix();
        }

        }
	}



	//gui
	mRender->SetOrtho(0,0,0,0,0,0);

    if(mWorld->HP <= 0)
	{
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,0.5f));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

	}


    if(hurt == true)
	{

		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,hurt_time));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

	}

	if(headInWater)
	{
	    GRAVITY = -4.0f;
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,0.7f));
		TextureManager::Instance()->SetTextureModeulate(blue);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);
	}
	else
    {
        GRAVITY = -6.8f;
    }


	if(headInLava)
	{
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,0.7f));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);
	}

	//gui
	sceGuDisable(GU_DEPTH_TEST);
	sceGuDepthMask(1);
	sceGuEnable(GU_BLEND);
	sceGuColor(GU_COLOR(1,1,1,1.0f));

	barSprite->Draw();


	if (invEn == false)
    {

        //HP and HG RENDERING
        for(int i = 1; i <= 10; i++)
        {
            hpCellSprite->SetPosition(60+i*16,224);
            hpSprite->SetPosition(60+i*16,224);
            hpHalfSprite->SetPosition(60+i*16,226);
            hpCellSprite->Draw();
            if(i * 2 <= mWorld->HP)
            {
                hpSprite->Draw();
            }
            if((i * 2 - mWorld->HP) == 1)
            {
                hpHalfSprite->Draw();
            }

            hgCellSprite->SetPosition(242+i*16,226);
            hgSprite->SetPosition(244+i*16,226);
            hgHalfSprite->SetPosition(246+i*16,226);
            hgCellSprite->Draw();
            if(i * 2 <= mWorld->HG)
            {
                hgSprite->Draw();
            }
            if((i * 2 - mWorld->HG) == 1)
            {
                hgHalfSprite->Draw();
            }
        }







        crossSprite->Draw();
        selectSprite->Draw();
    }
    else
    {
        invSprite->Draw();
        if (craft2xEn == true)
        {
            craft2xSprite->Draw();
        }
        if (craft3xEn == true)
        {
            craft3xSprite->Draw();
        }
        if (chestEn == true)
        {
            chestSprite->Draw();
        }

    }



	sceGuDisable(GU_BLEND);

	//draw 3d cubes on 2d panel
	TextureManager::Instance()->SetTextureModeulate(texture);

        //Inventory
        if(invEn == true)
        {
            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                if(mWorld->invId[i*9+j] != -1)
                {
                sceGumPushMatrix();

                ScePspFVector3 loc = {100+j*35,148+i*35,0.0f};
                sceGumTranslate(&loc);

                if(mWorld->invId[i*9+j] < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(mWorld->invId[i*9+j]);
                sceGuFrontFace(GU_CCW);
                }

                if(mWorld->invId[i*9+j] >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(mWorld->invId[i*9+j]);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
                }

                }
            }
            //2X2 Crafting
            if(craft2xEn == true)
            {
            for(int i = 0; i <= 1; i++)
            {
                for(int j = 0; j <= 1; j++)
                {
                if(craftSlotId[i*2+j] != -1)
                {
                sceGumPushMatrix();

                ScePspFVector3 loc = {100+j*35,78+i*35,0.0f};
                sceGumTranslate(&loc);

                if(craftSlotId[i*2+j] < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(craftSlotId[i*2+j]);
                sceGuFrontFace(GU_CCW);
                }

                if(craftSlotId[i*2+j] >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(craftSlotId[i*2+j]);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
                }

                }


            }
            //End

            //Item which we are crafting
            if (craftItemId != -1)
            {

                sceGumPushMatrix();

                ScePspFVector3 loc = {205,78,0.0f};
                sceGumTranslate(&loc);

                if(craftItemId < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(craftItemId);
                sceGuFrontFace(GU_CCW);
                }

                if(craftItemId >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(craftItemId);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
            }


            //End


            }

            //3X3 Crafting
            if(craft3xEn == true)
            {
            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 2; j++)
                {
                if(craftSlotId3[i*3+j] != -1)
                {
                sceGumPushMatrix();

                ScePspFVector3 loc = {100+j*35,43+i*35,0.0f};
                sceGumTranslate(&loc);

                if(craftSlotId3[i*3+j] < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(craftSlotId3[i*3+j]);
                sceGuFrontFace(GU_CCW);
                }

                if(craftSlotId3[i*3+j] >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(craftSlotId3[i*3+j]);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
                }

                }


            }
            //End

            //Item which we are crafting 3x
            if (craftItemId3 != -1)
            {

                sceGumPushMatrix();

                ScePspFVector3 loc = {240,78,0.0f};
                sceGumTranslate(&loc);

                if(craftItemId3 < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(craftItemId3);
                sceGuFrontFace(GU_CCW);
                }

                if(craftItemId3 >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(craftItemId3);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
            }


            //End


            }

            //Chest rendering
            if(chestEn == true)
            {
            for(int i = 0; i <= 1; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                if(mWorld->chestSlotId[(chestId*18)+i*9+j] != -1)
                {
                sceGumPushMatrix();

                ScePspFVector3 loc = {100+j*35,43+i*35,0.0f};
                sceGumTranslate(&loc);

                if(mWorld->chestSlotId[(chestId*18)+i*9+j] < 250)
                {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(mWorld->chestSlotId[(chestId*18)+i*9+j]);
                sceGuFrontFace(GU_CCW);
                }

                if(mWorld->chestSlotId[(chestId*18)+i*9+j] >= 250)
                {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(mWorld->chestSlotId[(chestId*18)+i*9+j]);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
                }

                }


            }
            }




            if (mWorld->mId != -1)
            {
            sceGumPushMatrix();
            if (craftEn == 1)
            {
                if (craft2xEn == 1)
                {
                ScePspFVector3 loc = {100 + (invXPosition * 35),56+(invYPosition * 35),0.0f};
                sceGumTranslate(&loc);
                }
                if (craft3xEn == 1)
                {
                ScePspFVector3 loc = {100 + (invXPosition * 35),21+(invYPosition * 35),0.0f};
                sceGumTranslate(&loc);
                }
                if (chestEn == 1)
                {
                ScePspFVector3 loc = {100 + (invXPosition * 35),21+(invYPosition * 35),0.0f};
                sceGumTranslate(&loc);
                }
            }
            else
            {
                ScePspFVector3 loc = {100 + (invXPosition * 35),126+(invYPosition * 35),0.0f};
                sceGumTranslate(&loc);
            }

            if (mWorld->mId < 250)
            {
            ScePspFVector3 sca = {17,17,17.0f};
            sceGumScale(&sca);

            //rotate
            sceGumRotateX(2.5f);
            sceGumRotateY(0.9f);
            sceGuFrontFace(GU_CW);
            mWorld->drawCubes(mWorld->mId);
            sceGuFrontFace(GU_CCW);
            }

            if (mWorld->mId >= 250)
            {
            ScePspFVector3 sca = {32,32,32.0f};
            sceGumScale(&sca);

            //rotate
            sceGumRotateX(0.0f);
            sceGumRotateY(0.0f);
            sceGuFrontFace(GU_CW);
            mWorld->drawItems(mWorld->mId);
            sceGuFrontFace(GU_CCW);
            }

            sceGumPopMatrix();

            }

        }

        //End



	for(int k = 0; k <= 8; k++)
	{
	    if(mWorld->invId[27+k] != -1)
        {
		sceGumPushMatrix();
		ScePspFVector3 loc = {100+k*35,253,0.0f};
        sceGumTranslate(&loc);

            if(mWorld->invId[27+k] < 250)
            {
                ScePspFVector3 sca = {17,17,17.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(mWorld->invId[27+k]);
                sceGuFrontFace(GU_CCW);
            }

            if(mWorld->invId[27+k] >= 250)
            {
                ScePspFVector3 sca = {32,32,32.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGumRotateZ(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(mWorld->invId[27+k]);
                sceGuFrontFace(GU_CCW);
            }

		sceGumPopMatrix();
        }

	}

	sceGuEnable(GU_DEPTH_TEST);
	sceGuDepthMask(0);

    //text
    if(mWorld->HP <= 0 )
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        mRender->DebugPrint(240,100,"YOU DIE. PRESS X TO RESPAWN.");

    }
        if(invEn == true)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            selectInvSprite->Draw();

            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    if(mWorld->invId[i*9+j] != -1)
                    {
                        mRender->DebugPrint(100+j*35,163+i*35,"%i",mWorld->invAm[i*9+j]);
                    }
                }
            }

            if (mWorld->mId != -1)
            {
                if (craftEn == 0)
                {
                    mRender->DebugPrint(100 + (invXPosition * 35),141+(invYPosition * 35),"%i",mWorld->mAm);
                }
                else
                {
                    if(craft2xEn == 1)
                    {
                        mRender->DebugPrint(100 + (invXPosition * 35),71+(invYPosition * 35),"%i",mWorld->mAm);
                    }
                    if(craft3xEn == 1)
                    {
                        mRender->DebugPrint(100 + (invXPosition * 35),36+(invYPosition * 35),"%i",mWorld->mAm);
                    }
                    if(chestEn == 1)
                    {
                        mRender->DebugPrint(100 + (invXPosition * 35),36+(invYPosition * 35),"%i",mWorld->mAm);
                    }
                }
            }

            if(craft2xEn == true)
            {
                for(int i = 0; i <= 1; i++)
                {
                    for(int j = 0; j <= 1; j++)
                    {
                        if(craftSlotId[i*2+j] != -1)
                        {
                            mRender->DebugPrint(100+j*35,93+i*35,"%i",craftSlotAm[i*2+j]);
                        }
                    }
                }

                if(craftItemId != -1)
                {
                    mRender->DebugPrint(205,93,"%i",craftItemAm);
                }
            }

            if(craft3xEn == true)
            {
                for(int i = 0; i <= 2; i++)
                {
                    for(int j = 0; j <= 2; j++)
                    {
                        if(craftSlotId3[i*3+j] != -1)
                        {
                            mRender->DebugPrint(100+j*35,58+i*35,"%i",craftSlotAm3[i*3+j]);
                        }
                    }
                }

                if(craftItemId3 != -1)
                {
                    mRender->DebugPrint(240,93,"%i",craftItemAm3);
                }
            }

            if(chestEn == true)
            {
                for(int i = 0; i <= 1; i++)
                {
                    for(int j = 0; j <= 8; j++)
                    {
                        if(mWorld->chestSlotId[(chestId*18)+i*9+j] != -1)
                        {
                            mRender->DebugPrint(100+j*35,58+i*35,"%i",mWorld->chestSlotAm[(chestId*18)+i*9+j]);
                        }
                    }
                }

            }
            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);
        }


            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));
            for(int k = 0; k <= 8; k++)
            {
                if (mWorld->invAm[27+k] > 1){mRender->DebugPrint(100+k*35,268,"%i",mWorld->invAm[27+k]);}
            }
            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);


    //menu buttons
    if(menuState == 1)
    {
        if(menuOptions)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,40);
            buttonSprite->Draw();

            //fly
            buttonSprite->SetPosition(240,70);
            buttonSprite->Draw();

            //dev menu
            buttonSprite->SetPosition(240,100);
            buttonSprite->Draw();

            //screenshot
            buttonSprite->SetPosition(240,130);
            buttonSprite->Draw();

            //rename map
            buttonSprite->SetPosition(240,160);
            buttonSprite->Draw();

            //player sounds
            buttonSprite->SetPosition(240,190);
            buttonSprite->Draw();

            //headBob
            buttonSprite->SetPosition(240,220);
            buttonSprite->Draw();

            //selected button
            sbuttonSprite->SetPosition(240,(optionsMenuPos * 30) + 40);
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            //draw subtitles on buttons
            canFly == true ? mRender->DebugPrint(240,45,"Difficult: Peaceful"): mRender->DebugPrint(240,45,"Difficult: Peaceful");
            devMode == true ? mRender->DebugPrint(240,75,"DevMode : ON"): mRender->DebugPrint(240,75,"DevMode : OFF");
            mRender->DebugPrint(240,105,"Take Screenshot");
            mRender->DebugPrint(240,135,"Change map name");
            mSoundMgr->playerSounds == true ? mRender->DebugPrint(240,165,"Player sounds: ON"):mRender->DebugPrint(240,165,"Player sounds: OFF");
            canHeadBob == true ? mRender->DebugPrint(240,195,"Head bob: ON"):mRender->DebugPrint(240,195,"Head bob: OFF");
            mRender->DebugPrint(240,225,"Next");
        }
        else
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,70);
            buttonSprite->Draw();

            //resume
            buttonSprite->SetPosition(240,100);
            buttonSprite->Draw();

            //options
            buttonSprite->SetPosition(240,130);
            buttonSprite->Draw();

            //save
            buttonSprite->SetPosition(240,160);
            buttonSprite->Draw();

            //quit
            buttonSprite->SetPosition(240,190);
            buttonSprite->Draw();

            //quit and save
            buttonSprite->SetPosition(240,220);
            buttonSprite->Draw();

            //selected button
            sbuttonSprite->SetPosition(240,(selectPos * 30) + 70);
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            //draw subtitles on buttons
            mRender->DebugPrint(240,75,"Resume");
            mRender->DebugPrint(240,105,"Options");
            mRender->DebugPrint(240,135,"Statistics");
            mRender->DebugPrint(240,165,"Save");
            mRender->DebugPrint(240,195,"Save and Exit");
            mRender->DebugPrint(240,225,"Exit");
        }
    }
    else
    {
    if(menuOptions)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,40);
            buttonSprite->Draw();

            buttonSprite->SetPosition(240,70);
            buttonSprite->Draw();

            buttonSprite->SetPosition(240,100);
            buttonSprite->Draw();
            //selected button
            sbuttonSprite->SetPosition(240,(selectPos * 30) + 40);
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            //draw subtitles on buttons
            switch(mWorld->fogLevel)
            {
            case 0: mRender->DebugPrint(240,45,"Fog : tiny"); break;
            case 1: mRender->DebugPrint(240,45,"Fog : short"); break;
            case 2: mRender->DebugPrint(240,45,"Fog : normal"); break;
            case 3: mRender->DebugPrint(240,45,"Fog : far"); break;
            }
            mWorld->skyRender == true ? mRender->DebugPrint(240,75,"Beautiful sky: ON"):mRender->DebugPrint(240,75,"Beautiful sky: OFF");
            mWorld->freezeDayTime == true ? mRender->DebugPrint(240,105,""):mRender->DebugPrint(240,105,"");

        }
    }
    if (menuState == 3)
    {
        mRender->DebugPrint(240,105,"Blocks Placed: %i",mWorld->blockPlaced);
        mRender->DebugPrint(240,135,"Blocks Destroyed: %i",mWorld->blockDestroyed);

    }

    //debug info
    if(devMode)
    {
        mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000000);

        if(dt > 0.0f)
            mRender->DebugPrint(20,20,"fps: %4.2f",(1.0f/dt));
        mRender->DebugPrint(20,30,"cpu: %d%%",mRender->GetCpuUsage());
        mRender->DebugPrint(20,40,"gpu: %d%%",mRender->GetGpuUsage());
        mRender->DebugPrint(20,50,"memory: %d",freeMemory);
        mRender->DebugPrint(20,60,"poly: %d",(mWorld->GetDrawntTrianglesCount() / 3));
        mRender->DebugPrint(20,70,"verts: %d",mWorld->GetDrawntTrianglesCount());
        mRender->DebugPrint(20,80,"day time: %f",mWorld->worldDayTime);
        mRender->DebugPrint(20,90,"sky time: %f",skyDome->timeOfDay);
        mRender->DebugPrint(20,100,"sun time: %f",sunTime);
        mRender->DebugPrint(20,110,"player.x: %f",playerPosition.x);
        mRender->DebugPrint(20,120,"player.y: %f",playerPosition.y);
        mRender->DebugPrint(20,130,"player.z: %f",playerPosition.z);
        mRender->DebugPrint(20,150,"Cycle %f",bobCycle);
        mRender->DebugPrint(20,160,"chunk %i",chunks);


        mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);
    }

    //end frame
    mRender->EndFrame();
}

//additional functions
void StatePlay::advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice)
{
    int start, end;

    // blit maximizing the use of the texture-cache

    for (start = sx, end = sx+sw; start < end; start += slice, dx += slice)
    {
        TexturesPSPVertex16* vertices = (TexturesPSPVertex16*)sceGuGetMemory(2 * sizeof(TexturesPSPVertex16));
        int width = (start + slice) < end ? slice : end-start;

        vertices[0].u = start;
        vertices[0].v = sy;
        vertices[0].x = dx;
        vertices[0].y = dy;
        vertices[0].z = 0;

        vertices[1].u = start + width;
        vertices[1].v = sy + sh;
        vertices[1].x = dx + width;
        vertices[1].y = dy + sh;
        vertices[1].z = 0;

        sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
    }
}

bool StatePlay::TryToMove(Vector3 moveVector,float dt)
{
    // Build a "test vector" that is a little longer than the move vector.
    float moveLength = moveVector.magnitude();
    Vector3 testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.2f);

    // Apply this test vector.
    Vector3 movePosition = playerPosition + testVector;
    Vector3 midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    Vector3 lowerBodyPoint = movePosition + Vector3(0, -1.4f, 0);

    if (!mWorld->SolidAtPointForPlayer(movePosition) && !mWorld->SolidAtPointForPlayer(lowerBodyPoint) && !mWorld->SolidAtPointForPlayer(midBodyPoint))
    {
        playerPosition = playerPosition + moveVector;
        return true;
    }

    //teraz mo¿na robiæ ciekawe rzeczy

    testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.35f);
    movePosition = playerPosition + testVector;
    midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    lowerBodyPoint = movePosition + Vector3(0, -1.4f, 0);

    unsigned char lowerBlock = mWorld->BlockAtPoint(lowerBodyPoint);
    unsigned char midBlock = mWorld->BlockAtPoint(midBodyPoint);
    unsigned char upperBlock = mWorld->BlockAtPoint(movePosition);

    //kolizja z drabin¹ :>
    if (upperBlock == 6 || lowerBlock == 6 || midBlock == 6)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 82 || lowerBlock == 82 || midBlock == 82)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 83 || lowerBlock == 83 || midBlock == 83)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 84 || lowerBlock == 84 || midBlock == 84)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 85 || lowerBlock == 85 || midBlock == 85)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 86 || lowerBlock == 86 || midBlock == 86)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 87 || lowerBlock == 87 || midBlock == 87)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 88 || lowerBlock == 88 || midBlock == 88)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 89 || lowerBlock == 89 || midBlock == 89)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 90 || lowerBlock == 90 || midBlock == 90)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }



    return false;
}

bool StatePlay::keyPressed(int currentKey)
{
    //analog reset
    if(analogUp)
    {
        if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYup)
            analogUp = false;
    }
    if(analogDown)
    {
        if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYdown)
            analogDown = false;
    }
    if(analogLeft)
    {
        if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXleft)
            analogLeft = false;
    }
    if(analogRight)
    {
        if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXright)
            analogRight = false;
    }

    //keys
    if(currentKey == 0)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
    {
        if(!analogUp)
        {
            if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup)
            {
                analogUp = true;
                return true;//analog up
            }
        }
    }
    if(currentKey == 11)//cross
    {
        if(!analogDown)
        {
            if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown)
            {
                analogDown = true;
                return true;//analog down
            }
        }
    }
    if(currentKey == 13)//cross
    {
        if(!analogLeft)
        {
            if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft)
            {
                analogLeft = true;
                return true;//analog left
            }
        }
    }
    if(currentKey == 14)//cross
    {
        if(!analogRight)
        {
            if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright)
            {
                analogRight = true;
                return true;//analog right
            }
        }
    }

    return false;
}

bool StatePlay::keyHold(int currentKey)
{
    if(currentKey == 0)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
        return (mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup);//analog up
    if(currentKey == 11)//cross
        return (mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown);//analog down
    if(currentKey == 13)//cross
        return (mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft);//analog left
    if(currentKey == 14)//cross
        return (mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright);//analog right

    return false;
}


void StatePlay::HungerTime()
{
    if(mWorld->HG != 0)
    {
    if(mWorld->HG > 16)
    {
        if(rand() % 3 == 1)
        {
            mWorld->HG -= 1;
        }
    }
    else
    {
        mWorld->HG -= 1;
    }
    }

}

void StatePlay::HealthTime()
{
    if(mWorld->HG <= 0)
    {
        mWorld->HP -= 1;
        hurt = true;
        hurt_time = 1.0f;
    }

    if(mWorld->HG >= 7 && mWorld->HG <= 16 )
    {
        mWorld->HP += 1;
    }

    if(mWorld->HG >= 17)
    {
        mWorld->HP += 2;
    }

    if(mWorld->HP > 20)
    {
        mWorld->HP = 20;
    }
}

void StatePlay::PutInInventory(int id, int num, bool st)
{
    for(int j = 35; j >= 0; j--)
    {
        if (mWorld->invSt[j]==1)
        {
            if (mWorld->invId[j]== id)
            {
                if(mWorld->invAm[j] + num <= 64)
                {
                    mWorld->invAm[j] += num;
                    chestId = -1;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (mWorld->invId[j]== -1)
        {
            mWorld->invSt[j] = st;
            mWorld->invId[j] = id;
            mWorld->invAm[j] = num;
            break;
        }
    }
}
