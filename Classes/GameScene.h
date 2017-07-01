#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <vector>
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	std::vector<Sprite*> cards;
	std::vector<int> type; //qi = 1; bo = 2; dang =3;
	void CreateCard();
	Size visibleSize;
	Vec2 origin;
	void playcard();
	void addMouseListener();
	void onMouseDown(Event* event);
	void touchMoved(Event* event);
	bool played = false;
	void take_action(int i);
	void animation();
	Vec2 play1position;
	Vec2 play2position;
	void vs_robot();
	int flag = 0;
	Sprite* paibei;
	Sprite* robotpaibei;
};

#endif //
