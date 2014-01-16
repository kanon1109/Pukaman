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
	//切换场景
	void changeScene(float t, CCScene* scene);
	//当切换场景结束后调用
	void onEnterTransitionDidFinish();
	//游戏主循环	
	virtual void loop(float dt);
	//渲染方法
	void render();
	//点击事件
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);

private:
	//背景
	CCLayerColor* background;
	//地板
	CCLayerColor* floorBg;
	//地板方的线条
	CCLayerColor* floorLineBg;
	//游戏核心类
	PukaManCore* pukaManCore;
	//背景列表
	CCArray* drawBgList;
	//前景列表
	CCArray* frontBgList;
	//角色显示对象
	CCSprite* role;
	CCSprite* hand;
	CCSprite* body;
	//舞台大小
	float stageWidth;
	float stageHeight;
	//开启主循环
	void startLoop();
	//关闭循环
	void stopLoop();
	//创建运动背景
	CCDrawNode* createMotionWall(float x, float y, float bgWidth, float bgHeight, float gapH, ccColor4F color);
	//创建运动前景
	CCDrawNode* createFrontMotionWall(float x, float y, 
									float bgWidth, float bgHeight, 
									int tag);
	//判断跳跃范围是否在墙壁边界内
	bool inWallBoundaries();
	//ui层
	CCLayer* uiLayer;
	//爆炸粒子
	CCParticleSystemQuad* bomb;
	//获取枪口的坐标
	CCPoint getGunPos();
	//UI文本
	CCSprite* uiText;
	//设置连跳跃 UI
	void getNumTexture(CCArray* textureNameList, const char* headStr, int num, const char* tail);
	//设置数字显示
	void updateNumSprite(CCNode* node, CCArray* souceList, int num, float startX, float startY);
	//combo纹理列表
	CCArray* comboList;
	CCArray* scoreList;
	CCArray* highScoreList;
	//删除List
	void removeList(CCArray* list);
	//失败方法回调
	void failCallBackFun(CCObject* data);
	//布局数字列表中的数字
	void layoutScoreNum(CCArray* list, int align);
	//更新连跳显示
	void updateCombo();
	//更新分数显示
	void updateScore();
	//更新最高分数显示
	void updateHighScore();
	//初始化人物
	void initRole(float x, float y);
	//添加分数显示
	CCSprite* addScoreSpt;
	CCArray* addScoreList;
	//新纪录
	CCSprite* newHighScore;
};

