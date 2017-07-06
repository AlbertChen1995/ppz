#pragma once
#ifndef __AI_H__
#define __AI_H__

#include "cocos2d.h"
#include "stdlib.h"
#include "time.h"
#include <string>
using std::string;
class AI {
public:
	int AIplayer(int qi, int robot_qi, string dif);
private:
	int AIAnType = 1;
	int rand0[2] = { 2,3 };
	int rand1[2] = { 1,3 };
	int rand2[3] = { 1,2,3 };
	int rand3[2] = { 1,2 };
};




#endif // __HELLOWORLD_SCENE_H__
