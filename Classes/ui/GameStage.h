#pragma once
#include "cocos2d.h"
#include "PukaManCore.h"
USING_NS_CC;
class GameStage:public CCScene, public CCTargetedTouchDelegate
{
public:
	GameStage(void);
	~GameStage(void);
	virtual void onEnter();
	virtual void onExit();
	//�л�����
	void changeScene(float t, CCScene* scene);
	//���л��������������
	void onEnterTransitionDidFinish();
	//��Ϸ��ѭ��	
	virtual void loop(float dt);
	//��Ⱦ����
	void render();
	//����¼�
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);

private:
	//����
	CCLayerColor* background;
	//�ذ�
	CCLayerColor* floorBg;
	//�ذ巽������
	CCLayerColor* floorLineBg;
	//��Ϸ������
	PukaManCore* pukaManCore;
	//�����б�
	CCArray* drawBgList;
	//ǰ���б�
	CCArray* frontBgList;
	//��ɫ��ʾ����
	CCSprite* role;
	CCSprite* hand;
	CCSprite* body;
	//��̨��С
	float stageWidth;
	float stageHeight;
	//������ѭ��
	void startLoop();
	//�ر�ѭ��
	void stopLoop();
	//�����˶�����
	CCDrawNode* createMotionWall(float x, float y, float bgWidth, float bgHeight, float gapH, ccColor4F color);
	//�����˶�ǰ��
	CCDrawNode* createFrontMotionWall(float x, float y, 
									float bgWidth, float bgHeight, 
									int tag);
	//�ж���Ծ��Χ�Ƿ���ǽ�ڱ߽���
	bool inWallBoundaries();
	//ui��
	CCLayer* uiLayer;
	//��ը����
	CCParticleSystemQuad* bomb;
	//��ȡǹ�ڵ�����
	CCPoint getGunPos();
	//UI�ı�
	CCSprite* uiText;
	//��������Ծ UI
	void getNumTexture(CCArray* textureNameList, const char* headStr, int num, const char* tail);
	//����������ʾ
	void updateNumSprite(CCNode* node, CCArray* souceList, int num, float startX, float startY);
	//combo�����б�
	CCArray* comboList;
	CCArray* scoreList;
	CCArray* highScoreList;
	//ɾ��List
	void removeList(CCArray* list);
	//ʧ�ܷ����ص�
	void failCallBackFun(CCObject* data);
	//���������б��е�����
	void layoutScoreNum(CCArray* list, int align);
	//����������ʾ
	void updateCombo();
	//���·�����ʾ
	void updateScore();
	//������߷�����ʾ
	void updateHighScore();
	//��ʼ������
	void initRole(float x, float y);
	//��ӷ�����ʾ
	CCSprite* addScoreSpt;
	CCArray* addScoreList;
	//�¼�¼
	CCSprite* newHighScore;
};

