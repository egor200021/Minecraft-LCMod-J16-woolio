#include "StateMenu.h"
#include "StateOptions.h"
#include "StatePlay.h"
#include "LoadingScreen.h"
#include "InputHelper.h"
#include "TextureHelper.h"

#include <Aurora/System/NetworkManager.h>

#include <zlib.h>
#include <dirent.h>
#include <fcntl.h>


StateMenu::StateMenu()
{

}

StateMenu::~StateMenu()
{

}

void StateMenu::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();

    logoSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Logo),0,0,256,64);
    logoSprite->Scale(1.5f,1.5f);
    logoSprite->SetPosition(240,50);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,22,200,20);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,62,200,20);
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,42,200,20);
    nbuttonSprite->SetPosition(240,150);

    backSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Dirt),0,0,16,16);
    backSprite->Scale(2,2);

    selectSaveSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Glass),0,0,64,64);
    selectSaveSprite->Scale(7,0.6f);

    lamecraftSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::lameCraft),0,0,256,64);
    lamecraftSprite->Scale(1.5f,1.5f);
    lamecraftSprite->SetPosition(240,50);

    screen1Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen1));
    screen1Sprite->SetPosition(260,136);

    screen2Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen2));
    screen2Sprite->SetPosition(260,136);

    screen3Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen3));
    screen3Sprite->SetPosition(260,136);

    screen4Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::screen4));
    screen4Sprite->SetPosition(260,136);

    selectPos = 0;

    //load save info
    ScanSaveFiles("Save/");

    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    aboutPos = 0;
    newWorldName = "NewWorld";
    //for map generation
    terrainType = 0;
    makeFlat = false;
    makeTrees = true;
    makeWater = true;
    makeCaves = true;
    makePumpkins = true;
    makeClouds = true;
    makeTypes = true;
    makeIron = true;
    makeCoal = true;
    makeGold = true;
    makeRedStone = true;
    makeDiamond = true;
    makeDirt = true;
    makeCanes = true;
    generateSelectPose = 0;

    saveSubmenu = false;
    saveSubMenuSelect = 2;
    seed_1 = 0;
    seed_length = 0;
    newWorldNamestr = newWorldName.c_str();
    currentVersion = 30;

    //input helper
    InputHelper::Instance()->Init();
    InputHelper::Instance()->Load();

	animationscreen = 1;
	timex = 2400;
}

void StateMenu::Enter()
{
    mRender->SetOrtho(0,0,0,0,0,0);
    selectPos = 0;
}

void StateMenu::CleanUp()
{
delete screen1Sprite;
delete screen2Sprite;
delete screen3Sprite;
delete screen4Sprite;



}

void StateMenu::Pause()
{

}

void StateMenu::Resume()
{
    menuState = 0;
    loadSelectPos = 0;
    loadSavePos = 0;
    mRender->SetOrtho(0,0,0,0,0,0);
}

void StateMenu::HandleEvents(StateManager* sManager)
{
    //update input
    mSystemMgr->InputUpdate();

    switch(menuState)
    {
    case 0://main menu
    {
        //if triangle button pressed the exit
        if(mSystemMgr->KeyPressed(PSP_CTRL_START))
        {
            //running = false;
            sManager->Quit();
        }

        //up, down
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

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(selectPos == 0)//play state
            {
            generateSelectPose = 0;
            menuState = 7;
            }

            if(selectPos == 1)
            {
                //w teori opcje
                StateOptions *stateOptions = new StateOptions();
                stateOptions->Init();
                sManager->PushState(stateOptions);
            }
            if(selectPos == 2)
            {
                //about
                menuState = 3;
                aboutPos = 1;
            }
        }
    }
    break;
    case 1://load
    {
        if(saveSubmenu)
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                saveSubMenuSelect--;
                if(saveSubMenuSelect < 1)
                    saveSubMenuSelect = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                saveSubMenuSelect++;
                if(saveSubMenuSelect > 2)
                    saveSubMenuSelect = 1;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(saveSubMenuSelect == 1)//remove file
                {
                    //remove file
                    if(saveFilesList.size() > 0)
                    {
                        if(saveFilesList[loadSavePos].compression)
                        {
                            //remove normal file
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                            //remove compressed one
                            saveFilesList[loadSavePos].fileName += "c";
                            remove(saveFilesList[loadSavePos].fileName.c_str());

                        }
                        else
                        {
                            remove(saveFilesList[loadSavePos].fileName.c_str());
                        }

                        ScanSaveFiles("Save/");

                        loadSelectPos = 0;
                        loadSavePos = 0;
                        loadSaveStart = 0;
                        loadSaveEnd = saveFilesList.size();
                        loadSaveMax = 4;
                        if(loadSaveMax > loadSaveEnd)
                            loadSaveMax = loadSaveEnd;

                        saveSubmenu = false;
                        saveSubMenuSelect = 2;
                    }
                }
                if(saveSubMenuSelect == 2)//return
                {
                    saveSubMenuSelect = 2;
                    saveSubmenu = false;
                }
            }


        }
        else
        {
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                loadSelectPos--;
                if(loadSelectPos < 0)
                    loadSelectPos = 2;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                loadSelectPos++;
                if(loadSelectPos > 2)
                    loadSelectPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                loadSavePos--;
                if(loadSaveEnd > 4)
                {
                    loadSaveStart--;
                    loadSaveMax--;

                    if(loadSaveMax < 4)
                    {
                        loadSaveStart = 0;
                        loadSaveMax = 4;
                    }
                }

                if(loadSavePos < 0)
                {
                    loadSavePos = saveFilesList.size() - 1;
                    loadSaveMax = loadSaveEnd;
                    loadSaveStart = loadSaveEnd - 4;
                    if(loadSaveStart < 0)
                        loadSaveStart = 0;
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                loadSavePos++;
                if(loadSavePos == loadSaveMax)
                {
                    loadSaveStart++;
                    loadSaveMax++;
                    if(loadSaveMax > loadSaveEnd)
                    {
                        loadSaveStart = loadSaveEnd - 4;
                        if(loadSaveStart < 0)
                            loadSaveStart = 0;
                        loadSaveMax = loadSaveEnd;
                    }
                }
                if(loadSavePos >= saveFilesList.size())
                {
                    loadSavePos = 0;
                    loadSaveStart = 0;
                    loadSaveMax = 4;
                    if(loadSaveMax > loadSaveEnd)
                        loadSaveMax = loadSaveEnd;
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 7;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(loadSelectPos == 0)//play state
                {
						//load map
                    if(saveFilesList.size() > 0)
                    {
                        StatePlay *statePlay = new StatePlay();
                        LoadingScreen *loading = new LoadingScreen();
                        statePlay->LoadMap(saveFilesList[loadSavePos].fileName,saveFilesList[loadSavePos].compression);
                        statePlay->InitCamera();
                        loading->KillLoadingScreen();
                        delete loading;
                        sManager->PushState(statePlay);
                    }

                }
                if(loadSelectPos == 1)//daelete save
                {
                    if(saveFilesList.size() > 0)
                    {
                        saveSubmenu = true;
                        saveSubMenuSelect = 2;
                    }
                }
                if(loadSelectPos == 2)
                {
                    menuState = 7;

                }
            }
        }
    }
    break;
    case 3://about
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            aboutPos--;
            if(aboutPos < 0)
                aboutPos = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            aboutPos++;
            if(aboutPos > 1)
                aboutPos = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(aboutPos == 1)
            {
                menuState = 0;
            }
            if(aboutPos == 0)
            {
                //checking for new update
                NetworkManager::Instance()->Init();
                //initialize connection
                if(NetworkManager::Instance()->InitializeConnection())
                {
                    //show network dialog and connect to ap
                    if(SystemManager::Instance()->ShowNetworkDialog())
                    {
                        //download update info
                        if(NetworkManager::Instance()->GetFile("http://drakon.ixan.net/psp/version.txt","version.txt"))
                        {
                            //check what version is inside
                            int fileVersion = 0;
                            FILE * pFile;
                            pFile = fopen("version.txt","r");
                            if (pFile!=NULL)
                            {
                                char buffer[3];
                                fread(buffer,1,3,pFile);
                                fileVersion = atoi(buffer);
                                fclose (pFile);

                                if(fileVersion > currentVersion)
                                {
                                    SystemManager::Instance()->ShowMessage("There is new version available");

                                    //ask question if user want to download updater
                                    if(SystemManager::Instance()->ShowMessageYesNo("Do you want to dowload LameCraft updater?") == 1)
                                    {
                                        //make new directory
                                        mkdir("ms0:/PSP/GAME/LameUpdater",777);
                                        //download updater there
                                        NetworkManager::Instance()->GetFile("http://drakon.ixan.net/psp/updater/EBOOT.PBP","ms0:/PSP/GAME/LameUpdater/EBOOT.PBP");
                                        //
                                        SystemManager::Instance()->ShowMessage("LameUpdater was installed.");
                                    }
                                }
                                else
                                {
                                    SystemManager::Instance()->ShowMessage("You have latest version.");
                                }
                            }
                            else
                            {
                                SystemManager::Instance()->ShowMessage("Can't open version.txt .");
                            }
                        }
                        else
                        {
                            SystemManager::Instance()->ShowMessage("Can't download update information.");
                        }
                    }
                    else
                    {
                        SystemManager::Instance()->ShowMessage("You must connect to an access point.");
                    }
                }
                else
                {
                    SystemManager::Instance()->ShowMessage("Can't initialize network.");
                }

                //turn off connection
                NetworkManager::Instance()->ShutDownConnection();
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            menuState = 0;
        }
    }
    break;
    case 4://chooose to generate randomly or marametric
    {




        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 2;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 2)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 7;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0)
            {
                int testseed = rand() % 10000;
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
                    StatePlay *statePlay = new StatePlay();
                    LoadingScreen *loading = new LoadingScreen();
                    statePlay->InitParametric(terrainType,makeFlat,makeTrees,makeWater,makeCaves,makePumpkins,makeTypes,makeIron,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,testseed);
                    loading->KillLoadingScreen();
                    delete loading;
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);

                }
            }

            if(generateSelectPose == 1)
            {
                generateSelectPose = 0;
                menuState = 5;

                terrainType = 0;
                makeFlat = false;
                makeTrees = true;
                makeWater = true;
                makeCaves = true;
                makePumpkins = true;
                makeClouds = true;
                makeTypes = true;
                makeIron = true;
                makeCoal = true;
                makeGold = true;
                makeRedStone = true;
                makeDiamond = true;
                makeDirt = true;
                makeCanes = true;
            }
            if(generateSelectPose == 2)
            {
                generateSelectPose = 0;
                menuState = 7;
            }
        }
    }
    break;
    case 5://parametric terrain
    {


        if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 6;

            mSoundMgr->PlayMenuSound();
        }



        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 6)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 7;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0)
            {

                newWorldName = "";

                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];

                        if(32 <= c && c <= 127) // print ascii only
                            newWorldName += c;
                    }


                }
                newWorldNamestr = newWorldName.c_str();

                }

                if(generateSelectPose == 1)
                {
                {
                seed_1 = 0;
                seed_length = 0;
                for(int h =0;h<36;h++)
                {
                seed_2[h] = '0';
                }
                unsigned short test[128];
                unsigned short opis[10] = {'W','o','r','l','d',' ','s','e','e','d'};
                if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                {

                    for(int j = 0; test[j]; j++)
                    {
                        unsigned c = test[j];


                        if (j < 36)
                        {
                            if(48 <= c && c <= 57)
                            {
                                seed_2[j] = test[j];
                            }
                        }

                    }

                    for(int m = 0; m <= 35; m++)
                    {
                        if (seed_2[m] == '0')
                        {
                            seed_length = m;
                        }
                    }

                    for(int j = 0; j < 35; j++)
                    {
                        if (j > seed_length)
                        {
                            continue;
                        }

                            switch(seed_2[j])
                            {
                                case 48: break;
                                case 49: j != seed_length ? seed_1 += 1*(10^(seed_length-j)) : seed_1 + 1; break;
                                case 50: j != seed_length ? seed_1 += 2*(10^(seed_length-j)) : seed_1 + 2; break;
                                case 51: j != seed_length ? seed_1 += 3*(10^(seed_length-j)) : seed_1 + 3; break;
                                case 52: j != seed_length ? seed_1 += 4*(10^(seed_length-j)) : seed_1 + 4; break;
                                case 53: j != seed_length ? seed_1 += 5*(10^(seed_length-j)) : seed_1 + 5; break;
                                case 54: j != seed_length ? seed_1 += 6*(10^(seed_length-j)) : seed_1 + 6; break;
                                case 55: j != seed_length ? seed_1 += 7*(10^(seed_length-j)) : seed_1 + 7; break;
                                case 56: j != seed_length ? seed_1 += 8*(10^(seed_length-j)) : seed_1 + 8; break;
                                case 57: j != seed_length ? seed_1 += 9*(10^(seed_length-j)) : seed_1 + 9; break;
                                }
                            }
                        }

                }

                }




            if(generateSelectPose == 2)
            {
                makeFlat = !makeFlat;

                if(makeFlat)
                {
                    makeWater = false;
                }
            }

            if(generateSelectPose == 3)
            {
                makeTrees = !makeTrees;
            }

            if(generateSelectPose == 4)
            {
                //generate parametric terrain
                makeWater = !makeWater;

                //don't make water type terrain without hills
                if(makeWater)
                {
                    makeFlat = false;
                }
            }

            if(generateSelectPose == 5)
            {
                makeCaves = !makeCaves;
            }

            if(generateSelectPose == 6)
            {
                StatePlay *statePlay = new StatePlay();
                LoadingScreen *loading = new LoadingScreen();
                statePlay->InitParametric(terrainType,makeFlat,makeTrees,makeWater,makeCaves,makePumpkins,makeTypes,makeIron,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,seed_1);
                loading->KillLoadingScreen();
                delete loading;
                statePlay->InitCamera();
                statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                sManager->PushState(statePlay);
            }
    }


    }
    break;
    case 6://check new version menu
    {

    }
    break;
    case 7://load or new map
    {
         if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 1)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0) //new game
            {
                generateSelectPose = 0;
                menuState = 5;

                terrainType = 0;
                makeFlat = false;
                makeTrees = true;
                makeWater = true;
                makeCaves = true;
                makePumpkins = true;
                makeClouds = true;
                makeTypes = true;
                makeIron = true;
                makeCoal = true;
                makeGold = true;
                makeRedStone = true;
                makeDiamond = true;
                makeDirt = true;
                makeCanes = true;

            }

            if(generateSelectPose == 1) //load game
            {
                ScanSaveFiles("Save/");

                menuState = 1;
                loadSelectPos = 0;
                loadSavePos = 0;
                loadSaveStart = 0;
                loadSaveEnd = saveFilesList.size();
                loadSaveMax = 4;
                if(loadSaveMax > loadSaveEnd)
                loadSaveMax = loadSaveEnd;
            }
        }
    }
    break;
     case 8://survival or creative
    {
         if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
        {
            generateSelectPose--;
            if(generateSelectPose < 0)
                generateSelectPose = 1;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
        {
            generateSelectPose++;
            if(generateSelectPose > 1)
                generateSelectPose = 0;

            mSoundMgr->PlayMenuSound();
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            generateSelectPose = 0;
            menuState = 0;
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if(generateSelectPose == 0) //survival
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
                    StatePlay *statePlay = new StatePlay();
                    LoadingScreen *loading = new LoadingScreen();
                    statePlay->InitParametric(terrainType,makeFlat,makeTrees,makeWater,makeCaves,makePumpkins,makeTypes,makeIron,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,0);
                    loading->KillLoadingScreen();
                    delete loading;
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);

                }
            }

            if(generateSelectPose == 1) //creative
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
                    StatePlay *statePlay = new StatePlay();
                    LoadingScreen *loading = new LoadingScreen();
                    statePlay->InitParametric(terrainType,makeFlat,makeTrees,makeWater,makeCaves,makePumpkins,makeTypes,makeIron,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,0);
                    loading->KillLoadingScreen();
                    delete loading;
                    statePlay->InitCamera();
                    statePlay->SetWorldAndSaveName(newWorldName,nextSaveFileName);
                    sManager->PushState(statePlay);

                }
            }
        }
    }
    break;
    }

}

void StateMenu::Update(StateManager* sManager)
{


        if (animationscreen == 1)
        {
            if(timex < 19200)
            {
                timex++;
            }
            if (timex > 19100)
            {
                animationscreen = 2;
            }
        }
        else
        {
            if(timex > 0)
            {
                timex--;
            }
            if (timex < 100)
            {
                animationscreen = 1;
            }
        }




}

void StateMenu::Draw(StateManager* sManager)
{
    //start rendering
    mRender->StartFrame();

    switch(menuState)
    {
    case 0://main menu
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));


        screen1Sprite->SetPosition(-480+(-920 + (timex/10)),136);
        screen1Sprite->Draw();
        screen2Sprite->SetPosition(0+(-920 + (timex/10)),136);
        screen2Sprite->Draw();
        screen3Sprite->SetPosition(480+(-920 + (timex/10)),136);
        screen3Sprite->Draw();
        screen4Sprite->SetPosition(960+(-920 + (timex/10)),136);
        screen4Sprite->Draw();







        //logo
        lamecraftSprite->Draw();

        //singlePlayer
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //about
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //options
        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(selectPos * 40) + 120);
        sbuttonSprite->Draw();


        //mRender->DebugPrint(240,50,"Time: %f", time_s);
        if(menuState == 0)
        {
            if (animationscreen == 1)
            {
                timex < 16400 ? timex++ : animationscreen = 2;
            }
            else
            {
                timex > 2450 ? timex-- : animationscreen = 1;
            }
        }



        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        mRender->DebugPrint(240,125,"SinglePlayer");
        mRender->DebugPrint(240,165,"Options");
        mRender->DebugPrint(240,205,"About");
		mRender->DebugPrint(60,265,"v1.6 Alpha");

		//Text
        float time_s = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
        //mRender->DebugPrint(240,50,"Time: %f", time_s);
        float fontsize = (time_s < 0.5f) ? time_s*511 : (1.0f-time_s)*511;
        //mRender->DebugPrint(240,25,"Size: %f", (fontsize/500));

        int SplashNumber = 0;
        char *SplashText;

        //Randomly generate the text number - because is in "while" not working yet
        //SplashNumber = rand() % 2; // 0-2

        switch (SplashNumber)
        {
        case 0:
            SplashText = "Woo, minecraft!";
            break;
        case 1:
            SplashText = "Casual Gaming";
            break;
        case 2:
            SplashText = "Fan fiction";
            break;
        case 3:
            SplashText = "Teetsuuuuoooo";
            break;
        case 4:
            SplashText = "Gasp! ";
            break;
        case 5:
            SplashText = "Autonomous! ";
            break;
        case 6:
            SplashText = "V-synched! ";
            break;
        }

        mRender->SetFontStyle( (fontsize/500+0.5) ,0xFF00FFFF,0xFF000000,0x00000200);
        mRender->DebugPrint(400,80,SplashText);

        //Reset de original font for next menu items
        mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);
		}
		break;
    case 1://load menu
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //select sprite
        if(saveFilesList.size() > 0)
        {
            selectSaveSprite->SetPosition(240,50 + (loadSavePos * 40) - (loadSaveStart * 40));
            selectSaveSprite->Draw();
        }

        //save files
        for(int i = loadSaveStart; i <loadSaveMax; i++)
        {
            if(loadSavePos == i)
            {
                mRender->SetFontStyle(1.0f,0xFF000000,0xFFFFFFFF,0x00000000);
                mRender->DebugPrint(30,50 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].worldName);

                mRender->SetFontStyle(0.7f,0xFF7F7F7F,0xFF000000,0x00000000);
                mRender->DebugPrint(40,65 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].fileName.c_str());
            }
            else
            {
                mRender->SetFontStyle(0.8f,0xFFFFFFFF,0xFF000000,0x00000000);
                mRender->DebugPrint(30,50 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].worldName);

                mRender->SetFontStyle(0.5f,0xFF7F7F7F,0xFF000000,0x00000000);
                mRender->DebugPrint(40,60 + (i * 40) - (loadSaveStart * 40),"%s",saveFilesList[i].fileName.c_str());
            }

        }

        //play
        buttonSprite->SetPosition(240,210);
        buttonSprite->Draw();

        //delete
        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();

        //back
        buttonSprite->SetPosition(240,260);
        buttonSprite->Draw();

        //selected button



        mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);
        //draw subtitles on buttons
        mRender->DebugPrint(240,20,"LOAD WORLD");

        if(saveSubmenu)
        {
            sbuttonSprite->SetPosition(240,(saveSubMenuSelect * 25) + 210);
        }
        else
        {
            sbuttonSprite->SetPosition(240,(loadSelectPos * 25) + 210);
        }
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        if(saveSubmenu)
        {
            mRender->DebugPrint(240,215,"Are you sure?");
            mRender->DebugPrint(240,240,"Yes");
            mRender->DebugPrint(240,265,"No");
        }
        else
        {
            mRender->DebugPrint(240,215,"Play");
            mRender->DebugPrint(240,240,"Delete");
            mRender->DebugPrint(240,265,"Back");
        }
    }
    break;
    case 3://about
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //check for update
        buttonSprite->SetPosition(240,235);
        buttonSprite->Draw();

        buttonSprite->SetPosition(240,260);
        buttonSprite->Draw();

        //back
        sbuttonSprite->SetPosition(240,(aboutPos * 25) + 235);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //about text
        mRender->SetFontStyle(0.7f,0xFFFFFFFF,0xFF000000,0x00000000);
        mRender->DebugPrint(40,100,"Original Code:  Drakon");
        mRender->DebugPrint(40,120,"Mod by:        Woolio & Joel16");
        mRender->DebugPrint(40,140,"Version:        1.6");

        //button text
        mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);
        mRender->DebugPrint(240,240,"Check for update");
        mRender->DebugPrint(240,265,"Back");
    }
    break;
    case 4://choose generation type
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //logo
        lamecraftSprite->Draw();

        //Randomly
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //Parametric
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //back
        buttonSprite->SetPosition(240,200);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(generateSelectPose * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        mRender->DebugPrint(240,125,"Random Terrain");
        mRender->DebugPrint(240,165,"Parametric Terrain");
        mRender->DebugPrint(240,205,"Back");
    }
    break;
    case 5://paramateric view
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //logo

        //name
        nbuttonSprite->SetPosition(240,70);
        nbuttonSprite->Draw();
        //seed
        nbuttonSprite->SetPosition(240,95);
        nbuttonSprite->Draw();
        //trees
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();
        //
        buttonSprite->SetPosition(240,145);
        buttonSprite->Draw();

        //Structures
        buttonSprite->SetPosition(240,170);
        buttonSprite->Draw();

        //water
        buttonSprite->SetPosition(240,195);
        buttonSprite->Draw();


        buttonSprite->SetPosition(240,220);
        buttonSprite->Draw();

        sbuttonSprite->SetPosition(240,(generateSelectPose * 25) + 70);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons
        mRender->DebugPrint(370,75,"Name");
        mRender->DebugPrint(370,100,"Seed");







        makeFlat == true ?  mRender->DebugPrint(240,125,"Flat terrain"):mRender->DebugPrint(240,125,"Terrain with hills");
        makeTrees == true ? mRender->DebugPrint(240,150,"Trees : ON"):mRender->DebugPrint(240,150,"Trees : OFF");
        makeWater == true ? mRender->DebugPrint(240,175,"Water : ON"):mRender->DebugPrint(240,175,"Water : OFF");
        makeCaves == true ? mRender->DebugPrint(240,200,"Caves : ON"):mRender->DebugPrint(240,200,"Caves : OFF");
        mRender->DebugPrint(240,225,"Generate");
        mRender->DebugPrint(240,75,"%s",newWorldName.c_str());
        mRender->DebugPrint(240,100,"%i buggy",seed_1);



    }
    break;
    case 7://New or load map
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //logo
        lamecraftSprite->Draw();

        //Randomly
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //Parametric
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(generateSelectPose * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        mRender->DebugPrint(240,125,"New world");
        mRender->DebugPrint(240,165,"Load world");
    }
    break;
    case 8://survival or creative
    {


        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));

        for(int x = 0; x < 16; x++)
        {
            for(int y = 0; y < 9; y++)
            {
                backSprite->SetPosition(x*32,y*32);
                backSprite->Draw();
            }
        }

        //logo
        lamecraftSprite->Draw();

        //Randomly
        buttonSprite->SetPosition(240,120);
        buttonSprite->Draw();

        //Parametric
        buttonSprite->SetPosition(240,160);
        buttonSprite->Draw();

        //selected button
        sbuttonSprite->SetPosition(240,(generateSelectPose * 40) + 120);
        sbuttonSprite->Draw();

        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

        //draw subtitles on buttons

        mRender->DebugPrint(240,125,"Survival");
        mRender->DebugPrint(240,165,"Creative");
    }
    break;
    }

    //draw debug text at the end
    /*mRender->DebugPrint(40,30,"cpu: %d%%",mRender->GetCpuUsage());
    mRender->DebugPrint(40,40,"gpu: %d%%",mRender->GetGpuUsage());
    mRender->DebugPrint(40,50,"saves: %d",saveFilesList.size());*/

    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000400);
    //mRender->DebugPrint(475,15,"CraftSite.pl Edition");
    //mRender->SetFontStyle(0.5f,0xFFFFFFFF,0xFF000000,0x00000200);

    //end frame
    mRender->EndFrame();
}

//additional functions
void StateMenu::ScanSaveFiles(const char* dirName)
{
    //clear list with save files
    saveFilesList.clear();

    DIR *Dir;
    struct dirent *DirEntry;
    Dir = opendir(dirName);

    while((DirEntry = readdir(Dir)) != NULL)
    {
        if ( DirEntry->d_stat.st_attr & FIO_SO_IFREG)
        {
            SaveFile newSaveFile;
            std::string plik = dirName;
            plik += DirEntry->d_name;
            //dont load lmsc files
            size_t found = plik.find(".lmsc");
            size_t found2 = plik.find(".LMSc");
            if(found==std::string::npos && found2==std::string::npos)//nie znaleziono
            {
                newSaveFile.fileName = plik;
                saveFilesList.push_back(newSaveFile);
            }
        }
    }

    closedir(Dir);

    /*//// this was causeing some problems
    int dfd;
    dfd = sceIoDopen(dirName);
    if(dfd > 0)
    {
    	SceIoDirent dir;

    	while(sceIoDread(dfd, &dir) > 0)
    	{
    		if(dir.d_stat.st_attr & FIO_SO_IFREG)//regular file
    		{
    			SaveFile newSaveFile;
    			std::string plik = dirName;
    			plik += dir.d_name;
    			//dont load lmsc files
    			size_t found = plik.find(".lmsc");
    			if(found==string::npos)//nie znaleziono
    			{
    				newSaveFile.fileName = plik;
    				saveFilesList.push_back(newSaveFile);
    			}
    		}
    	}

    	//close folder
    	sceIoClose(dfd);
    }*/

    //now update all info in save files
    for(unsigned int i = 0; i < saveFilesList.size(); i++)
    {
        FILE * pFile;
        pFile = fopen(saveFilesList[i].fileName.c_str(),"rb");

        if(pFile != NULL)
        {
            //version
            fread(&saveFilesList[i].saveVersion,sizeof(int),1,pFile);

            //name
            fread(saveFilesList[i].worldName,sizeof(char),50,pFile);

            if(saveFilesList[i].saveVersion >= 2)
                saveFilesList[i].compression = true;
            else
                saveFilesList[i].compression = false;

            fclose(pFile);
        }
    }

    //set next save name and numer
    nextSaveFileNumber = saveFilesList.size() + 1;
    {
        //ride thru all saves and check if i can use new name
        char liczba[3];
        sprintf(liczba,"%d",nextSaveFileNumber);
        nextSaveFileName = "Save/world";
        nextSaveFileName += liczba;
        nextSaveFileName += ".lms";

        for(unsigned int i = 0; i < saveFilesList.size(); i++)
        {
            if(nextSaveFileName.compare(saveFilesList[i].fileName) == 0)
            {
                nextSaveFileNumber+=1;
                char liczba[3];
                sprintf(liczba,"%d",nextSaveFileNumber);
                nextSaveFileName = "Save/world";
                nextSaveFileName += liczba;
                nextSaveFileName += ".lms";
            }
        }
    }
}
