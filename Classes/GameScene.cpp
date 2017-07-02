#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "AI.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "GameScene.h"
#include <regex>
#include "SimpleAudioEngine.h"
#include "HomeScene.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocostudio::timeline;

string userName3;
Scene* GameScene::createScene(string str)
{

	userName3 = str;
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	addMouseListener();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	CreateCard();
	playcard();

	addUI();

	return true;
}

void GameScene::CreateCard() {
	Sprite* card1 = Sprite::create("qi.png");
	card1->setPosition(Vec2(origin.x + visibleSize.width/2 - card1->getContentSize().width,origin.y + card1->getContentSize().height/2));
	Sprite* card2 = Sprite::create("bo.png");
	card2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + card2->getContentSize().height/2));
	Sprite* card3 = Sprite::create("dang.png");
	card3->setPosition(Vec2(origin.x + visibleSize.width / 2 + card3->getContentSize().width, origin.y + card3->getContentSize().height/2));
	Sprite* robotCard1 = Sprite::create("paibei.png");
	robotCard1->setPosition(Vec2(visibleSize.width / 2 - robotCard1->getContentSize().width, visibleSize.height - robotCard1->getContentSize().height / 2));
	Sprite* robotCard2 = Sprite::create("paibei.png");
	robotCard2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - robotCard1->getContentSize().height / 2));
	Sprite* robotCard3 = Sprite::create("paibei.png");
	robotCard3->setPosition(Vec2(visibleSize.width / 2 + robotCard3->getContentSize().width, visibleSize.height - robotCard3->getContentSize().height / 2));
	this->addChild(card1, 2);
	this->addChild(card2, 2);
	this->addChild(card3, 2);
	cards.push_back(card1);
	cards.push_back(card2);
	cards.push_back(card3);
	type.push_back(1);
	type.push_back(2);
	type.push_back(3);
	this->addChild(robotCard1, 2);
	this->addChild(robotCard2, 2);
	this->addChild(robotCard3, 2);
}

void GameScene::playcard() {
	if (flag != 0) {
		flag = 0;
	}
	addMouseListener();
}

void GameScene::addMouseListener() {
	

	auto MouseListener = EventListenerMouse::create();

	MouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

	MouseListener->onMouseMove = NULL;//CC_CALLBACK_1(Home::onMouseMove, this);

	MouseListener->onMouseUp = NULL;//CC_CALLBACK_1(fishing::onMouseUp, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);

}

void GameScene::onMouseDown(Event* event) {
	EventMouse* mouse = (EventMouse*)event;
	Point mouseposition = mouse->getLocation();
	//float x1 = cards[2]->getPosition().x;
	//float y1 = cards[2]->getPosition().y;
	//log("%f,%f", mouseposition.x, mouseposition.y);
	//log("%f,%f", x1, y1);
	//log("%f,%f", cards[2]->getPosition().x, cards[2]->getPosition().y);
	//log("%f,%f", cards[3]->getPosition().x, cards[3]->getPosition().y);
	int cards_size = cards.size();
	for (int i = 0; i < cards_size; i++) {
		if ((!played) &&(mouseposition.x > cards[i]->getPosition().x - cards[i]->getContentSize().width / 2) && (mouseposition.x < cards[i]->getPosition().x + cards[i]->getContentSize().width / 2)
			&& (visibleSize.height - mouseposition.y > cards[i]->getPosition().y - cards[i]->getContentSize().height / 2) && (visibleSize.height - mouseposition.y < cards[i]->getPosition().y + cards[i]->getContentSize().height / 2)) 
		{
				played = true;
				flag = type[i];
				take_action(type[i]);
		}			
	}

}

void GameScene::take_action(int n) {
	robot_type = normal(qi, robot_qi);
	//CCLOG("%d", robot_type);
	//CCLOG("%d", robot_type);
	if (robot_type == 1) {
		robot_qi++;
	}
	if (robot_type == 2) {
		robot_qi--;
	}
	ismove = true;
	if (n == 1) {
		qi++;
	}
	else if (n == 2) {
		if (qi == 0) {
			ismove = false;
		}
		else {
			qi--;
		}
		//panduan bo
	}
	else {
		//dang
	}
	animation();
}

void GameScene::animation() {
	if (ismove) {
		paibei = Sprite::create("paibei.png");
		robotpaibei = Sprite::create("paibei.png");
		paibei->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2 * paibei->getContentSize().width, origin.y + paibei->getContentSize().height));
		this->addChild(paibei, 2);
		robotpaibei->setPosition(Vec2(origin.x + visibleSize.width / 2 - 2 * paibei->getContentSize().width, visibleSize.height - robotpaibei->getContentSize().height / 2));
		this->addChild(robotpaibei, 2);
		play1position.x = visibleSize.width / 2;
		play1position.y = visibleSize.height / 2 - paibei->getContentSize().height / 2;
		play2position.x = visibleSize.width / 2;
		play2position.y = visibleSize.height / 2 + robotpaibei->getContentSize().height / 2;
		//log("%f,%f", play1position.x, play1position.y);
		auto move = MoveTo::create(1, play1position);
		auto robot_move = MoveTo::create(1, play2position);
		paibei->runAction(move);
		robotpaibei->runAction(robot_move);
		vs_robot();
	}
	else {
		log("qi bu zu");
		played = false;
		playcard();
	}
}

void GameScene::vs_robot() {
	scheduleOnce(schedule_selector(GameScene::remove_paibei), 1.5f);
	//this->removeChild(paibei);
	//this->removeChild(robotpaibei);
	if (flag == 0) {
		//log("you lose!!hsfdkjhsdhkjhsdh!");
		//return;
	}
	else {
		if (flag == 1) {
			paimian = Sprite::create("qi.png");
		}
		if (flag == 2) {
			paimian = Sprite::create("bo.png");
		}
		if (flag == 3) {
			paimian = Sprite::create("dang.png");
		}
		paimian->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - paimian->getContentSize().height / 2));
		paimian->setVisible(false);
		this->addChild(paimian, 2);
		if (robot_type == 1) {
			robotpaimian = Sprite::create("qi.png");
		}
		if (robot_type == 2) {
			robotpaimian = Sprite::create("bo.png");
		}
		if (robot_type == 3) {
			robotpaimian = Sprite::create("dang.png");
		}
		robotpaimian->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + robotpaimian->getContentSize().height / 2));
		robotpaimian->setVisible(false);
		this->addChild(robotpaimian, 2);
		if (flag == 1 && robot_type == 2)
			log("you lose!!!");
		else if (flag == 2 && robot_type == 1)
			log("you win!!!");
		else playcard();
	}
}

void GameScene::remove_paibei(float dt) {
	paimian->setVisible(true);
	robotpaimian->setVisible(true);
	//paimian->setPosition(paibei->getPosition());
	this->removeChild(paibei);
	//this->addChild(paimian,2);
	//robotpaimian->setPosition(robotpaibei->getPosition());
	this->removeChild(robotpaibei);
	//this->addChild(robotpaimian, 2);
	scheduleOnce(schedule_selector(GameScene::remove_paimian), 0.5f);

	if (flag == 3 || flag == 0)
	played = false;
}

void GameScene::remove_paimian(float dt) {
	this->removeChild(paimian);
	this->removeChild(robotpaimian);
}

void GameScene::addUI() {
	CCSprite * RoomScene = CCSprite::create("RoomScene.jpg");
	RoomScene->setScale(1.1, 1.1);
	RoomScene->setPosition(ccp(480, 310));
	this->addChild(RoomScene, 1);

	auto btnBack = Button::create();
	btnBack->setTitleText("Back");
	btnBack->setTitleFontName("Felt");
	btnBack->setTitleFontSize(30);
	btnBack->loadTextureNormal("button1.png");
	btnBack->setPosition(ccp(850, 70));
	this->addChild(btnBack, 2);
	btnBack->addTouchEventListener(CC_CALLBACK_2(GameScene::Back, this));

	auto textField = TextField::create("Player Name", "Felt", 30);
	textField->setText(userName3);
	textField->setPosition(ccp(150, 150));
	this->addChild(textField, 2);

	CCSprite * sprite = CCSprite::create("touxiang.png");
	sprite->setPosition(ccp(150, 200));
	this->addChild(sprite, 2);
}

void GameScene::Back(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = HomeScene::createScene(userName3);
		Director::getInstance()->replaceScene(scene);
	}
}
