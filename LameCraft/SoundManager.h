#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

extern "C"
{
	#include "sound_utils/oslib.h"
}

#include <stdlib.h>
#include <time.h>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static SoundManager m_SoundManager;
	static SoundManager* Instance();

	void Init();

	void PlayMenuSound();
	void PlayPlopSound();
	void PlayWalkSound(int type);
	void TNTSound();
	void doorSound();
	void PlayCaveSound();

	int PlayRandomAmbient();


	bool playerSounds;
	bool ambientSoundsEnabled;

	int lastAmbientSound;
	int currentAmbientSound;

private:

	int currentWalkSound;
	int lastWalkSound;

	//sounds
	OSL_SOUND *buttonSound;

	//plop sound
	OSL_SOUND *plopSound;
	//cave sounds
    OSL_SOUND *caveSounds[6];
	//grass sounds
	OSL_SOUND *grassSounds[4];
	OSL_SOUND *grawelSounds[4];
	OSL_SOUND *stoneSounds[4];
	OSL_SOUND *woodSounds[4];
    OSL_SOUND *ambientSounds[6];

	//TNT
	OSL_SOUND *tnt;

	OSL_SOUND *door;




};

#endif

