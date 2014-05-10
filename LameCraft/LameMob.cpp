#include "LameMob.h"

LameMob::LameMob(float x, float y, float z)
{
    collideBox.x = 0.5;
    collideBox.y = 2.1;
    collideBox.z = 0.5;

    pos.x = x;
    pos.y = y;
    pos.z = z;

    angle.y = 1.0;

    HP = 20;

    timer = 0;
    timerMax = 100 + rand() % 190;
    jump = false;
    j_y = 0;
    path = 0;


}

void LameMob::Jump(float x)
{

jump = true;
j_y = pos.y+x;

}

void LameMob::Go(float x, float y, float z)
{

pos.x += x;
pos.y += y;
pos.z += z;

}


void LameMob::RenderMob()
{

    if (jump == true)
    {
        if (pos.y < j_y)
        {
        pos.y += 0.1;
        }
        if (pos.y >= j_y)
        {
            jump = false;
        }
    }

    if (timer < timerMax+5)
    {
        timer += 1;
    }
    if (timer > timerMax)
    {
        timerMax = 100 + rand() % 190;
        timer = 0;
    }


}

LameMob::~LameMob()
{
}
