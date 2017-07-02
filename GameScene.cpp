#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "AI.h"

USING_NS_CC;

using namespace cocostudio::timeline;


string userName3;
Scene* GameScene::createScene(string name)
{

	userName3 = name;
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
	return true;

	auto btnBack = Button::create();
	btnBack->setTitleText("Back");
	btnBack->setTitleFontSize(30);
	btnBack->setPosition(Size(100,500));
	this->addChild(btnBack, 3);
	btnBack->addTouchEventListener(CC_CALLBACK_2(GameScene::Back, this));
}

void GameScene::CreateCard() {
	Sprite* card1 = Sprite::create("qi1.png");//qi
	card1->setPosition(Vec2(origin.x + visibleSize.width/2 - card1->getContentSize().width,origin.y + card1->getContentSize().height/2));
	Sprite* card2 = Sprite::create("bo1.png");//bo
	card2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + card2->getContentSize().height/2));
	Sprite* card3 = Sprite::create("dang1.png");//dang
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
		played = !played;
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
		if ((mouseposition.x > cards[i]->getPosition().x - cards[i]->getContentSize().width / 2) && (mouseposition.x < cards[i]->getPosition().x + cards[i]->getContentSize().width / 2)
			&& (visibleSize.height - mouseposition.y > cards[i]->getPosition().y - cards[i]->getContentSize().height / 2) && (visibleSize.height - mouseposition.y < cards[i]->getPosition().y + cards[i]->getContentSize().height / 2)
			&& (!played)) 
		{
			played = !played;
			flag = type[i];
			take_action(type[i]);
		}			
	}

}

void GameScene::take_action(int i) {
	if (i = 1) {
		//jiqi
	}
	else if (i = 2) {
		//panduan bo
	}
	else {
		//dang
	}
	animation();
}

void GameScene::animation() {
	paibei = Sprite::create("paibei.png");
	robotpaibei = Sprite::create("paibei.png");
	paibei->setPosition(Vec2(origin.x + visibleSize.width / 2 + 2*paibei->getContentSize().width, origin.y + paibei->getContentSize().height));
	this->addChild(paibei, 2);
	robotpaibei->setPosition(Vec2(origin.x + visibleSize.width / 2 - 2 * paibei->getContentSize().width, visibleSize.height - robotpaibei->getContentSize().height / 2));
	this->addChild(robotpaibei, 2);
	play1position.x = visibleSize.width / 2;
	play1position.y = visibleSize.height / 2 - paibei->getContentSize().height/2;
	play2position.x = visibleSize.width / 2;
	play2position.y = visibleSize.height / 2 + robotpaibei->getContentSize().height / 2;
	//log("%f,%f", play1position.x, play1position.y);
	auto move = MoveTo::create(1, play1position);
	auto robot_move = MoveTo::create(1, play2position);
	paibei->runAction(move);
	robotpaibei->runAction(robot_move);
	vs_robot();
}

void GameScene::vs_robot() {
	int robot = normal();
	//this->removeChild(paibei);
	//this->removeChild(robotpaibei);
	if (flag == 0) {
		return;
	}
	else {
		if (flag == 1 && robot == 2)
			log("you lose!!!");
		else if (flag == 2 && robot == 1)
			log("you win!!!");
		else playcard();
	}
}

void GameScene::Back(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = HomeScene::createScene(userName3);
		Director::getInstance()->replaceScene(scene);
	}
}