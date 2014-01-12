#include "PukaManMain.h"
#include "StartPanel.h"
USING_NS_CC;
bool PukaManMain::init()
{
	CCLOG("init");
	CCDirector* director = CCDirector::sharedDirector();
	//注册点击事件
	director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//游戏舞台
	this->gameStage = new GameStage();
	//开始界面
	this->startPanel = new StartPanel();
	this->addChild(this->startPanel);
	return true;
}

void PukaManMain::onEnter()
{
	CCLOG("onEnter");
	//必须使用USING_NS_CC后才可生效
	CCScene::onEnter();
}

void PukaManMain::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//CCLOG("ccTouchEnded");
}

bool PukaManMain::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if(!this->gameStage->isShowed)
		this->startPanel->changeScene(0.1f, this->gameStage);
	else
		this->gameStage->touch();
	return true;
}


PukaManMain::PukaManMain(void)
{
}

PukaManMain::~PukaManMain(void)
{
}
