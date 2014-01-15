#pragma once
#include "cocos2d.h"
USING_NS_CC;
class StartPanel:public CCScene
{
public:
	StartPanel(void);
	~StartPanel(void);
	void changeScene(float t, CCScene* scene);
	void onEnterTransitionDidFinish();
	virtual void onExit();
private:
	//背景
	CCLayerColor* bg;
	//开始
	CCLabelTTF* startLabel;
	//游戏名字
	CCLabelTTF* nameLabel;
	//手
	CCSprite* hand;
	//身体
	CCSprite* body;
	//下一个场景
	CCScene* nextScene;
};




