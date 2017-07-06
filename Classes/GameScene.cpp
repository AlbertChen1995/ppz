#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "AI.h"
using namespace CocosDenshion;
USING_NS_CC;

using namespace cocostudio::timeline;

string userName3,dif;
AI MyAI;
Scene* GameScene::createScene(string str)
{
	dif = str[str.length()-1];
	userName3 = str.substr(0,str.length()-1);
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

	addUI();


	addMouseListener();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	touxiang = Sprite::create("touxiang.png");
	touxiang->setPosition(Vec2(origin.x + touxiang->getContentSize().width / 2, origin.y + touxiang->getContentSize().height / 2));
	this->addChild(touxiang, 2);
	robot_touxiang = Sprite::create("touxiang.png");
	robot_touxiang->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width / 2, visibleSize.height - touxiang->getContentSize().height / 2));
	this->addChild(robot_touxiang, 2);
	time = TextField::create("5", "Felt", 50);
	time->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2));
	this->addChild(time, 2);
	schedule(schedule_selector(GameScene::setTime), 1.0f, kRepeatForever, 0);
	create_qicao();
	CreateCard();
	playcard();

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
	if (!can_click) {
		return;
	}
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
				SimpleAudioEngine::getInstance()->playEffect("Click.wav");
				if (i == 1 && qi == 0) {
					break;
				}
				played = true;
				can_click = false;
				setTime(5.0);
				flag = type[i];
				take_action(type[i]);
		}			
	}

}

void GameScene::take_action(int n) {
	robot_type = MyAI.AIplayer(qi, robot_qi,dif);
	//CCLOG("%d", robot_type);
	//CCLOG("%d", robot_type);
	if (robot_type == 1) {
		paly_robot_qi_animation();
		if (robot_qi < 3)
		robot_qi++;
		switch (robot_qi)
		{
		case 3:
			r_qi3->setVisible(true);
		case 2:
			r_qi2->setVisible(true);
		case 1:
			r_qi1->setVisible(true);
		}
	}
	if (robot_type == 2) {
		paly_robot_bo_animation();
		robot_qi--;
		switch (robot_qi)
		{
		case 0:
			r_qi1->setVisible(false);
		case 1:
			r_qi2->setVisible(false);
		case 2:
			r_qi3->setVisible(false);
		}
	}
	if (robot_type == 3) {
		paly_robot_dang_animation();
	}
	ismove = true;
	if (n == 1) {
		paly_qi_animation();
		if (qi < 3)
		qi++;
		switch (qi)
		{
		case 3:
			_qi3->setVisible(true);
		case 2:
			_qi2->setVisible(true);
		case 1:
			_qi1->setVisible(true);
		}
	}
	else if (n == 2) {
		if (qi == 0) {
			ismove = false;
		}
		else {
			paly_bo_animation();
			qi--;
			switch (qi)
			{
			case 0:
				_qi1->setVisible(false);
			case 1:
				_qi2->setVisible(false);
			case 2:
				_qi3->setVisible(false);
			}
		}
		//panduan bo
	}
	else {
		//dang
		paly_dang_animation();
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
		auto fade_out1 = FadeOut::create(1.0f);
		auto fade_out2 = FadeOut::create(1.0f);
		auto move = MoveTo::create(1.0f, play1position);
		auto spwan = Spawn::createWithTwoActions(fade_out1, move);
		auto robot_move = MoveTo::create(1.0f, play2position);
		auto robot_spwan = Spawn::createWithTwoActions(fade_out2, robot_move);
		paibei->runAction(spwan);
		robotpaibei->runAction(robot_spwan);
		vs_robot();
	}
	else {
		log("qi bu zu");
		SimpleAudioEngine::getInstance()->playEffect("cannot.wav");
		played = false;
		can_click = true;
		playcard();
	}
}

void GameScene::vs_robot() {
	scheduleOnce(schedule_selector(GameScene::remove_paibei), 1.0f);
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
		paimian->setPosition(Vec2(visibleSize.width / 2 - 75, visibleSize.height / 2 - paimian->getContentSize().height / 2));
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
		robotpaimian->setPosition(Vec2(visibleSize.width / 2 + 75, visibleSize.height / 2 + robotpaimian->getContentSize().height / 2));
		robotpaimian->setVisible(false);
		this->addChild(robotpaimian, 2);
		if (flag == 1 && robot_type == 2) {
			log("you lose!!!");
			dtime = -1;
			scheduleOnce(schedule_selector(GameScene::lose), 1.5f);
		}
		else if (flag == 2 && robot_type == 1) {
			log("you win!!!");
			dtime = -1;
			scheduleOnce(schedule_selector(GameScene::win), 1.5f);
		}
		else {
			//scheduleOnce(schedule_selector(GameScene::next_play), 1.2f);
			playcard();
		}
	}
}

void GameScene::remove_paibei(float dt) {
	paimian->setVisible(true);
	robotpaimian->setVisible(true);

	SimpleAudioEngine::getInstance()->playEffect("bigboom.wav");

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
	can_click = true;
}

//void GameScene::next_play(float dt) {
//	playcard();
//}


void GameScene::create_qicao() {
	Sprite* qi_cao1 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	qi_cao1->setPosition(Vec2(touxiang->getContentSize().width+qi_cao1->getContentSize().width/2, qi_cao1->getContentSize().height / 2));
	this->addChild(qi_cao1, 2);
	Sprite* qi_cao2 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	qi_cao2->setPosition(Vec2(touxiang->getContentSize().width + qi_cao2->getContentSize().width / 2*3, qi_cao2->getContentSize().height / 2));
	this->addChild(qi_cao2, 2);
	Sprite* qi_cao3 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	qi_cao3->setPosition(Vec2(touxiang->getContentSize().width + qi_cao3->getContentSize().width / 2*5, qi_cao3->getContentSize().height / 2));
	this->addChild(qi_cao3, 2);
	//Sprite* qi_cao2 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	//Sprite* qi_cao3 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	_qi1 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	_qi1->setPosition(Vec2(touxiang->getContentSize().width + qi_cao1->getContentSize().width / 2, qi_cao1->getContentSize().height / 2));
	this->addChild(_qi1, 3);
	_qi1->setVisible(false);
	_qi2 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	_qi2->setPosition(Vec2(touxiang->getContentSize().width + qi_cao1->getContentSize().width / 2*3, qi_cao1->getContentSize().height / 2));
	this->addChild(_qi2, 3);
	_qi2->setVisible(false);
	_qi3 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	_qi3->setPosition(Vec2(touxiang->getContentSize().width + qi_cao1->getContentSize().width / 2*5, qi_cao1->getContentSize().height / 2));
	this->addChild(_qi3, 3);
	_qi3->setVisible(false);

	//robot
	Sprite* r_qi_cao1 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	r_qi_cao1->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi_cao1, 2);
	Sprite* r_qi_cao2 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	r_qi_cao2->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2*3, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi_cao2, 2);
	Sprite* r_qi_cao3 = Sprite::create("qi_cao.jpg", Rect(10, 25, 67, 19));
	r_qi_cao3->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2*5, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi_cao3, 2);
	r_qi1 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	r_qi1->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi1, 3);
	r_qi1->setVisible(false);
	r_qi2 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	r_qi2->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2*3, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi2, 3);
	r_qi2->setVisible(false);
	r_qi3 = Sprite::create("qi_cao.jpg", Rect(10, 2, 59, 13));
	r_qi3->setPosition(Vec2(visibleSize.width - touxiang->getContentSize().width - r_qi_cao1->getContentSize().width / 2*5, visibleSize.height + r_qi_cao1->getContentSize().height / 2 - touxiang->getContentSize().height));
	this->addChild(r_qi3, 3);
	r_qi3->setVisible(false);
}


void GameScene::win(float dt) {
	Sprite* winner = Sprite::create("victory.png");
	winner->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(winner, 2);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("win.mp3");
	SimpleAudioEngine::getInstance()->playEffect("victory.wav");
}

void GameScene::lose(float dt) {
	Sprite* loser = Sprite::create("lose.png");
	loser->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(loser, 2);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("lose.mp3");
	SimpleAudioEngine::getInstance()->playEffect("defeat.wav");
	SimpleAudioEngine::getInstance()->playEffect("dead.wav");
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
	textField->setPosition(ccp(150, 100));
	this->addChild(textField, 2);

}

void GameScene::Back(Ref *pSender, Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		SimpleAudioEngine::getInstance()->playEffect("Click.wav");
		auto scene = HomeScene::createScene(userName3);
		Director::getInstance()->replaceScene(scene);
	}
}

void GameScene::setTime(float dt) {
	if (dtime > 0) {
		dtime--;
		if (dt == 5.0)
			dtime = 5;
		char s[4];
		sprintf(s, "%d", dtime);
		time->setString(s);
	}
	else if (dtime == 0) {
		dtime = 5;
		played = true;
		can_click = false;
		flag = 1;
		take_action(1);
	}
	else return;
}


void GameScene::paly_bo_animation() {
	Sprite* bo_first = Sprite::create("bo_animation/1.png");
	bo_first->setPosition(300,visibleSize.height/2);
	this->addChild(bo_first, 2);
	auto bo_animation = Animation::create();
	for (int i = 2; i < 28; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "bo_animation/%d.png", i);
		bo_animation->addSpriteFrameWithFile(szName);
	}
	bo_animation -> setDelayPerUnit(1.5f/25.0f);
	//bo_animation->setRestoreOriginalFrame(true);

	auto bo = Animate::create(bo_animation);
	bo_first->runAction(bo);
	//this->removeChild(bo_first);
}

void GameScene::paly_robot_bo_animation() {
	Sprite* robot_bo_first = Sprite::create("bo_animation/1.png");
	robot_bo_first->setPosition(700, visibleSize.height / 2);
	this->addChild(robot_bo_first, 2);
	auto robot_bo_animation = Animation::create();
	for (int i = 2; i < 28; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "bo_animation/%d.png", i);
		robot_bo_animation->addSpriteFrameWithFile(szName);
	}
	robot_bo_animation->setDelayPerUnit(1.5f / 25.0f);
	//robot_bo_animation->setRestoreOriginalFrame(true);

	robot_bo_first->setFlipX(true);
	auto robot_bo = Animate::create(robot_bo_animation);
	robot_bo_first->runAction(robot_bo);
	//this->removeChild(robot_bo_first);
}

void GameScene::paly_qi_animation() {
	Sprite* qi_first = Sprite::create("qi_animation.png", Rect(0, 70, 125, 110));
	qi_first->setPosition(300, visibleSize.height / 2);
	this->addChild(qi_first, 2);
	Vector<SpriteFrame*> qi_stack;
	for (int i = 1; i < 19; i++) {
		auto frame = SpriteFrame::create("qi_animation.png", CC_RECT_PIXELS_TO_POINTS(Rect(125*i, 70, 125, 110)));
		qi_stack.pushBack(frame);
	}
	auto qi_animation = Animation::createWithSpriteFrames(qi_stack, 1.5f/18.0f);
	auto qi = Animate::create(qi_animation);
	qi_first->runAction(qi);
	//this->removeChild(qi_first);
}

void GameScene::paly_robot_qi_animation() {
	Sprite* qi_robot_first = Sprite::create("qi_animation.png", Rect(0, 70, 125, 110));
	qi_robot_first->setPosition(700, visibleSize.height / 2);
	this->addChild(qi_robot_first, 2);
	Vector<SpriteFrame*> qi_robot_stack;
	for (int i = 1; i < 19; i++) {
		auto frame = SpriteFrame::create("qi_animation.png", CC_RECT_PIXELS_TO_POINTS(Rect(125 * i, 70, 125, 110)));
		qi_robot_stack.pushBack(frame);
	}
	qi_robot_first->setFlipX(true);
	auto qi_robot_animation = Animation::createWithSpriteFrames(qi_robot_stack, 1.5f / 18.0f);
	auto robot_qi = Animate::create(qi_robot_animation);
	qi_robot_first->runAction(robot_qi);
	//this->removeChild(qi_robot_first);
}

void GameScene::paly_dang_animation() {
	Sprite* dang_first = Sprite::create("dang_animation.png", Rect(0, 80, 125, 140));
	dang_first->setPosition(300, visibleSize.height / 2);
	this->addChild(dang_first, 2);
	Vector<SpriteFrame*> dang_stack;
	for (int i = 1; i < 8; i++) {
		auto frame = SpriteFrame::create("dang_animation.png", CC_RECT_PIXELS_TO_POINTS(Rect(125 * i, 80, 125, 140)));
		dang_stack.pushBack(frame);
	}
	auto dang_animation = Animation::createWithSpriteFrames(dang_stack, 1.5f / 6.0f);
	auto dang = Animate::create(dang_animation);
	dang_first->runAction(dang);
	//this->removeChild(dang_first);
}

void GameScene::paly_robot_dang_animation() {
	Sprite* dang_robot_first = Sprite::create("dang_animation.png", Rect(0, 80, 125, 140));
	dang_robot_first->setPosition(700, visibleSize.height / 2);
	this->addChild(dang_robot_first, 2);
	Vector<SpriteFrame*> dang_robot_stack;
	for (int i = 1; i < 8; i++) {
		auto frame = SpriteFrame::create("dang_animation.png", CC_RECT_PIXELS_TO_POINTS(Rect(125 * i, 80, 125, 140)));
		dang_robot_stack.pushBack(frame);
	}
	dang_robot_first->setFlipX(true);
	auto dang_robot_animation = Animation::createWithSpriteFrames(dang_robot_stack, 1.5f / 6.0f);
	auto robot_dang = Animate::create(dang_robot_animation);
	dang_robot_first->runAction(robot_dang);
	//this->removeChild(dang_robot_first);
}

