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
	//����
	CCLayerColor* bg;
	//��ʼ
	CCLabelTTF* startLabel;
	//��Ϸ����
	CCLabelTTF* nameLabel;
	//��
	CCSprite* hand;
	//����
	CCSprite* body;
	//��һ������
	CCScene* nextScene;
};




