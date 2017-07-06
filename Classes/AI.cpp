#include "AI.h"



int  AI::AIplayer(int qi, int robot_qi, string dif) {
	string easy,normal,hard;
	easy += '0';
	normal += '1';
	hard += '2';
	if (dif == easy) {
		if (robot_qi == 0)
			return 1;
		return AIAnType++ % 3 + 1;
	}
	else if (dif == normal) {
		if (robot_qi == 0 && qi == 0)
			return 1;
		srand(time(0));
		if (robot_qi = 3)
			return rand0[rand() % 2];
		if (robot_qi == 0)
			return rand1[rand() % 2];
		return rand2[rand() % 3];	
	}
	else if(dif == hard){
		if (robot_qi == 0 && qi == 0)
			return 1;
		srand(time(0));
		if (robot_qi == 0)
			return rand1[rand() % 2];
		if (robot_qi >= 1 && qi == 0)
			return rand3[rand() % 2];
		if (robot_qi < 3 && robot_qi > qi)
			return rand2[rand() % 3];
		if (robot_qi = 3)
			return rand0[rand() % 2];
		return 1;
	}
}