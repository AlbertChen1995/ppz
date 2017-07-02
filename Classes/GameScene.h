#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"
#include <regex>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include <string>
using std::vector;
using std::string;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(string str);

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
	void take_action(int n);
	void animation();
	Vec2 play1position;
	Vec2 play2position;
	void vs_robot();
	int flag = 0;
	Sprite* paibei;
	Sprite* robotpaibei;
	Sprite* paimian;
	Sprite* robotpaimian;
	void remove_paibei(float dt);
	void remove_paimian(float dt);
	int qi = 0;
	int robot_qi = 0;
	bool ismove = true;
	int robot_type = 0;
};

#endif //
