#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include <string>
#include <vector>
using std::vector;
using std::string;
using namespace cocos2d::ui;
using namespace cocos2d::network;

class RoomScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene(string userName);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(RoomScene);

	void RoomScene::Ready(Ref *pSender, Widget::TouchEventType type);
	void RoomScene::Back(Ref *pSender, Widget::TouchEventType type);

private:
	float visibleHeight;
	float visibleWidth;
	TextField * textField;
	TextField * textBox;
	Button * btnReady;
};

#endif
