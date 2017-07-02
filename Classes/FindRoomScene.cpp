#include "FindRoomScene.h"
#include "RoomScene.h"
#include "HomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"
#include <regex>
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

using namespace cocostudio::timeline;

string userName1;
Scene* FindRoomScene::createScene(string Name)
{
	userName1 = Name;
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = FindRoomScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool FindRoomScene::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	textField = TextField::create("Player Name", "Felt", 30);
	textField->setText("Room List");
	textField->setPosition(Size(visibleWidth / 4, visibleHeight / 8 * 7));
	this->addChild(textField, 2);

	auto btnJoinRoom = Button::create();
	btnJoinRoom->setTitleText("Join Room");
	btnJoinRoom->setTitleFontName("Felt");
	btnJoinRoom->setTitleFontSize(30);
	btnJoinRoom->loadTextureNormal("button1.png");
	btnJoinRoom->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 8 * 3));
	this->addChild(btnJoinRoom, 2);
	btnJoinRoom->addTouchEventListener(CC_CALLBACK_2(FindRoomScene::JoinRoom, this));

	auto btnCreateRoom = Button::create();
	btnCreateRoom->setTitleText("Create Room");
	btnCreateRoom->setTitleFontName("Felt");
	btnCreateRoom->setTitleFontSize(30);
	btnCreateRoom->loadTextureNormal("button1.png");
	btnCreateRoom->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 8 * 2));
	this->addChild(btnCreateRoom, 2);
	btnCreateRoom->addTouchEventListener(CC_CALLBACK_2(FindRoomScene::CreateRoom, this));

	auto btnBack = Button::create();
	btnBack->setTitleText("Back");
	btnBack->setTitleFontName("Felt");
	btnBack->setTitleFontSize(30);
	btnBack->loadTextureNormal("button1.png");
	btnBack->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 8));
	this->addChild(btnBack, 2);
	btnBack->addTouchEventListener(CC_CALLBACK_2(FindRoomScene::Back, this));

	CCSprite * RoomListScene = CCSprite::create("RoomListScene.jpg");
	//RoomListScene->setScale(1.1, 1.1);
	RoomListScene->setPosition(ccp(480, 350));
	this->addChild(RoomListScene);

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

void FindRoomScene::JoinRoom(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = RoomScene::createScene(userName1);
		Director::getInstance()->replaceScene(scene);
	}
}

void FindRoomScene::CreateRoom(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = RoomScene::createScene(userName1);
		Director::getInstance()->replaceScene(scene);
	}
}

void FindRoomScene::Back(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = HomeScene::createScene(userName1);
		Director::getInstance()->replaceScene(scene);
	}
}
