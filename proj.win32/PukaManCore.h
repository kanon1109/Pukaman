#pragma once
//失败消息宏
#define FAIL "fail"
//失败消息 新纪录宏
#define NEW_RECORD "newRecord"
#include "cocos2d.h"
#include "RoleVo.h"
USING_NS_CC;
class PukaManCore:public CCObject
{
public:
	PukaManCore(void);
	~PukaManCore(void);
	//角色
	RoleVo* roleVo;
	//最大x速度
	double maxVx;
	//最小x速度
	double minVx;
	//是否失败
	bool isFail;
	//速度
	double vx;
	double vy;
	//背景宽度
	float bgWidth;
	//跳跃次数
	int jumpCombo;
	//分数
	int score;
	//最高分
	int highScore;
	//分数增量 跳跃一次增加的分数
	int scoreVar;
	//跳跃
	bool jump();
	//更新方法
	void update();
	//初始化游戏 最大x速度、最小x速度、y速度、角速度、重力 跳跃间隔、 上下范围
	void initGame(double maxVx, double minVx, double vy, float angularSpeed, double g, int jumpDelay, float top, float bottom);
private:
	//角速度
	float angularSpeed;
	//待机速度
	double standbySpeed;
	//中文
	double g;
	//上部范围坐标
	float top;
	//下部范围坐标
	float bottom;
	//是否起跳
	bool isJump;
	//上一次起跳时间
	int prevJumpDelay;
	//跳跃间隔
	int jumpDelay;
	//是否翻滚
	bool isRoll;
	//站立待机
	void standby();
	//判断跳跃
	void jumpMotion();
	//滚动
	void roll();
	//判断背景宽度
	void checkBgWidth();
	//落地后vx的摩擦力
	double f;
	//缓动指数
	double ease;
	//最大动态背景宽度
	int maxBgWidth;
	//宽度需要减少的量
	int widthDis;
	//最小动态背景宽度
	int minBgWidth;
	//消息参数
	CCNode* nData;
};

