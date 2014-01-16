#include "PukaManMain.h"
#include "ui/StartPanel.h"
USING_NS_CC;
bool PukaManMain::init()
{
	CCLOG("init");
	//��ʼ����
	this->startPanel = new StartPanel();
	this->addChild(this->startPanel);
	//��Ϸ��̨
	this->gameStage = new GameStage();
	return true;
}

void PukaManMain::onEnter()
{
	CCLOG("onEnter");
	//ע�����¼�
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//����ʹ��USING_NS_CC��ſ���Ч
	CCScene::onEnter();
}

void PukaManMain::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//CCLOG("ccTouchEnded");
}

bool PukaManMain::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	this->startPanel->changeScene(0.1f, this->gameStage);
	return true;
}


PukaManMain::PukaManMain(void)
{
}

PukaManMain::~PukaManMain(void)
{
}

void PukaManMain::onExit()
{
	CCLOG("onExit");
	CCScene::onExit();
}

void PukaManMain::keyBackClicked()
{
	CCDirector* director = CCDirector::sharedDirector();
	CCSize size = director->getWinSize();
	CCLabelTTF*	startLabel = CCLabelTTF::create("backClick", "Helvetica", 20);
	//����������ɫ
	ccColor3B color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	startLabel->setColor(color);
	startLabel->setPosition(ccp(size.width *.5, size.height *.2));
	this->addChild(startLabel);
}
