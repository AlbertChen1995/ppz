#include "LogInScene.h"
#include "HomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#include "SimpleAudioEngine.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"
#include <regex>
using std::to_string;
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;
using namespace CocosDenshion;


using namespace cocostudio::timeline;

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

using namespace cocostudio::timeline;

Scene* LogInScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogInScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LogInScene::init()
{
	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	textField = TextField::create("Player Name", "Felt", 50);
	textField->setPosition(Size(visibleWidth / 2, visibleHeight / 2));
	this->addChild(textField, 2);

	CCSprite * Logo = CCSprite::create("Logo.png");
	//Logo->setScale(0.6, 0.6);
	Logo->setPosition(ccp(visibleWidth / 2, visibleHeight / 1.5));
	Logo->setScale(1.2, 1.2);
	this->addChild(Logo, 2);

	auto button = Button::create();
	//button->setTitleText("Login");
	button->setTitleFontName("Felt");
	button->loadTextureNormal("StartGame.png");
	button->setTitleFontSize(30);
	button->setPosition(Size(visibleWidth / 2, visibleHeight / 4));
	this->addChild(button, 2);

	button->addTouchEventListener(CC_CALLBACK_2(LogInScene::login, this));

	CCSprite * LoginScreen = CCSprite::create("LoginScreen.jpg");
	LoginScreen->setScale(0.6, 0.6);
	LoginScreen->setPosition(ccp(400, 330));
	this->addChild(LoginScreen);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("LogIn.mp3"); 
	SimpleAudioEngine::getInstance()->playBackgroundMusic("LogIn.mp3", true);
	SimpleAudioEngine::getInstance()->preloadEffect("Click.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("defeat.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("victory.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("cannot.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("bigboom.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("dead.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("win.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("lose.mp3");


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
	//
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
void LogInScene::login(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = HomeScene::createScene(textField->getString());
		Director::getInstance()->replaceScene(scene);
			/*auto request = new HttpRequest();
			request->setUrl("http://localhost:8080/login");
			request->setRequestType(HttpRequest::Type::POST);
			request->setResponseCallback(CC_CALLBACK_2(LoginScene::onHttpRequestCompleted, this));

			string text = textField->getString();
			string s = "username=" + text;
			log(s.c_str());
			const char* postData = s.c_str();
			request->setRequestData(postData, strlen(postData));
			request->setTag("login");
			HttpClient::getInstance()->send(request);
			request->release();*/
	}
}
