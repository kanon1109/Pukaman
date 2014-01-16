#include "PukaManMain.h"
#include "ui/StartPanel.h"
USING_NS_CC;
bool PukaManMain::init()
{
	CCLOG("init");
	MyKeypadDelegate* keypadDelegate = new MyKeypadDelegate();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(keypadDelegate);
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

void MyKeypadDelegate::keyBackClicked()
{
	CCDirector::sharedDirector()->end();  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)  
	exit(0);  
#endif  
}
