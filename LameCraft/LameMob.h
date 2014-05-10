#ifndef LAMEMOB_H_
#define LAMEMOB_H_

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>

#include "SoundManager.h"


class LameMob
{
public:
	LameMob(float x, float y , float z);
	 ~LameMob();

	void RenderMob();
	void Jump(float x);
	void Go(float x, float y, float z);
	void Die();

    Vector3 pos;
    Vector3 angle;
    Vector3 collideBox;
    bool jump;
    short path;
    int HP;
private:

    short timer;
    short timerMax;
    float j_y;

};

#endif

