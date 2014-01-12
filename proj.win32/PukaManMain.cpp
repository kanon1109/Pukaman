#include "PukaManMain.h"
#include "StartPanel.h"
USING_NS_CC;
bool PukaManMain::init()
{
	CCLOG("init");
	CCDirector* director = CCDirector::sharedDirector();
	//ע�����¼�
	director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//��Ϸ��̨
	this->gameStage = new GameStage();
	//��ʼ����
	this->startPanel = new StartPanel();
	this->addChild(this->startPanel);
	return true;
}

void PukaManMain::onEnter()
{
	CCLOG("onEnter");
	//����ʹ��USING_NS_CC��ſ���Ч
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
