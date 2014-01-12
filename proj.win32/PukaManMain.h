#pragma once
#include "cocos2d.h"
#include "StartPanel.h"
#include "GameStage.h"
USING_NS_CC;
class PukaManMain :	public CCScene, public CCTargetedTouchDelegate
{
public:
	PukaManMain(void);
	~PukaManMain(void);
	//������ʼ������
	virtual bool init();
	virtual void onEnter();
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);

	//���ú꣬�᷵��һ��PukaManMain���ʵ���������ù��캯����init����
	CREATE_FUNC(PukaManMain);

private:
	StartPanel* startPanel;
	GameStage* gameStage;
};

