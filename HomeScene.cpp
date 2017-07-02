#include "HomeScene.h"
#include "FindRoomScene.h"
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
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using std::to_string;
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;


using namespace cocostudio::timeline;

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

using namespace cocostudio::timeline;

string userName;

Scene* HomeScene::createScene(string userName_)
{
	userName = userName_;
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HomeScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HomeScene::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	textField = TextField::create("Player Name", "Arial", 30);
	textField->setText(userName);
	textField->setPosition(Size(visibleWidth / 8, visibleHeight / 8 * 7));
	this->addChild(textField, 2);

	CCSprite * home = CCSprite::create("home.jpg");
	home->setScale(1.3, 1.3);
	home->setPosition(ccp(400, 325));
	this->addChild(home);

	CCSprite * sprite = CCSprite::create("touxiang.png");
	sprite->setPosition(ccp(100, 500));
	this->addChild(sprite);

	auto btnJoinRoom = Button::create();
	btnJoinRoom->setTitleText("Join Room");
	btnJoinRoom->setTitleFontSize(30);
	btnJoinRoom->setPosition(Size(visibleWidth / 4, visibleHeight * 2 / 3));
	this->addChild(btnJoinRoom, 2);
	btnJoinRoom->addTouchEventListener(CC_CALLBACK_2(HomeScene::JoinRoom, this));

	auto btnCreateRoom = Button::create();
	btnCreateRoom->setTitleText("Create Room");
	btnCreateRoom->setTitleFontSize(30);
	btnCreateRoom->setPosition(Size(visibleWidth / 4, visibleHeight / 3));
	this->addChild(btnCreateRoom, 2);
	btnCreateRoom->addTouchEventListener(CC_CALLBACK_2(HomeScene::CreateRoom, this));

	auto btnSimple = Button::create();
	btnSimple->setTitleText("Simple");
	btnSimple->setTitleFontSize(30);
	btnSimple->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4));
	this->addChild(btnSimple, 2);
	btnSimple->addTouchEventListener(CC_CALLBACK_2(HomeScene::Simple, this));

	auto btnNormal = Button::create();
	btnNormal ->setTitleText("Normal");
	btnNormal->setTitleFontSize(30);
	btnNormal->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4 * 2));
	this->addChild(btnNormal, 2);
	btnNormal->addTouchEventListener(CC_CALLBACK_2(HomeScene::Normal, this));

	auto btnHard = Button::create();
	btnHard->setTitleText("Hard");
	btnHard->setTitleFontSize(30);
	btnHard->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4 * 3));
	this->addChild(btnHard, 2);
	btnHard->addTouchEventListener(CC_CALLBACK_2(HomeScene::Hard, this));
	//	button->addClickEventListener(ui::Widget::ccWidgetClickCallback(LogInScene::login));
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

	//	    auto rootNode = CSLoader::createNode("MainScene.csb");

	//	    addChild(rootNode);

	return true;
}
void HomeScene::JoinRoom(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = FindRoomScene::createScene(userName);
		Director::getInstance()->replaceScene(scene);
	}
}

void HomeScene::CreateRoom(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = RoomScene::createScene(userName);
		Director::getInstance()->replaceScene(scene);
	}
}

void HomeScene::Simple(Ref *pSender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = GameScene::createScene(userName);
		Director::getInstance()->replaceScene(scene);
	}
}

void HomeScene::Normal(Ref *pSender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = GameScene::createScene(userName);
		Director::getInstance()->replaceScene(scene);
	}
}

void HomeScene::Hard(Ref *pSender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = GameScene::createScene(userName);
		Director::getInstance()->replaceScene(scene);
	}
}