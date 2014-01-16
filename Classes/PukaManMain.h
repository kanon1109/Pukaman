#pragma once
#include "cocos2d.h"
#include "ui/StartPanel.h"
#include "ui/GameStage.h"
USING_NS_CC;

class PukaManMain :	public CCScene, public CCTargetedTouchDelegate, public CCKeypadDelegate
{
public:
	PukaManMain(void);
	~PukaManMain(void);
	//创建初始化函数
	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	virtual void keyBackClicked();
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	//调用宏，会返回一个PukaManMain类的实例，并调用构造函数和init函数
	CREATE_FUNC(PukaManMain);

private:
	StartPanel* startPanel;
	GameStage* gameStage;
};

