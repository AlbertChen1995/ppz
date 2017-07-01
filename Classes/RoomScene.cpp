#include "FindRoomScene.h"
#include "HomeScene.h"
#include "RoomScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"
#include <regex>

using namespace cocostudio::timeline;

string userName2;
Scene* RoomScene::createScene(string Name)
{
	userName2 = Name;
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = RoomScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool RoomScene::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	textField = TextField::create("", "Arial", 30);
	textField->setText("waiting...");
	textField->setPosition(Size(visibleWidth / 2, visibleHeight / 4 * 3));
	this->addChild(textField, 2);

	textField = TextField::create("", "Arial", 30);
	textField->setText("VS");
	textField->setFontSize(50);
	textField->setPosition(Size(visibleWidth / 2, visibleHeight / 2));
	this->addChild(textField, 2);

	textField = TextField::create("Player Name", "Arial", 30);
	textField->setText(userName2);
	textField->setPosition(Size(visibleWidth / 2, visibleHeight / 4));
	this->addChild(textField, 2);

	CCSprite * sprite = CCSprite::create("touxiang.png");
	sprite->setPosition(ccp(490, 220));
	this->addChild(sprite);

	btnReady = Button::create();
	btnReady->setTitleText("Ready");
	btnReady->setTitleFontSize(30);
	btnReady->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 8 * 2));
	this->addChild(btnReady, 2);
	btnReady->addTouchEventListener(CC_CALLBACK_2(RoomScene::Ready, this));

	auto btnBack = Button::create();
	btnBack->setTitleText("Back");
	btnBack->setTitleFontSize(30);
	btnBack->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 8));
	this->addChild(btnBack, 2);
	btnBack->addTouchEventListener(CC_CALLBACK_2(RoomScene::Back, this));

	CCSprite * RoomScene = CCSprite::create("RoomScene.jpg");
	RoomScene->setScale(1.1, 1.1);
	RoomScene->setPosition(ccp(480, 310));
	this->addChild(RoomScene, 1);
	/**  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if ( !Layer::init() )
	{
	return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	**/

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//	auto rootNode = CSLoader::createNode("MainScene.csb");

	//	addChild(rootNode);

	return true;
}



void RoomScene::Back(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		auto scene = FindRoomScene::createScene(userName2);
		Director::getInstance()->replaceScene(scene);
	}
}

void RoomScene::Ready(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		if (btnReady->getTitleText() == "Ready")
			btnReady->setTitleText("Cancel");
		else btnReady->setTitleText("Ready");
	}
}
