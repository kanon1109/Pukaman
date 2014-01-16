#include "PukaManMain.h"
#include "ui/StartPanel.h"
USING_NS_CC;
bool PukaManMain::init()
{
	CCLOG("init");
	MyKeypadDelegate* keypadDelegate = new MyKeypadDelegate();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(keypadDelegate);
	//开始界面
	this->startPanel = new StartPanel();
	this->addChild(this->startPanel);
	//游戏舞台
	this->gameStage = new GameStage();
	return true;
}

void PukaManMain::onEnter()
{
	CCLOG("onEnter");
	//注册点击事件
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	//必须使用USING_NS_CC后才可生效
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
