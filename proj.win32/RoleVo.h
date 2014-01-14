#pragma once
#include "cocos2d.h"
USING_NS_CC;
class RoleVo:public CCObject
{
public:
	RoleVo(void);
	~RoleVo(void);
	//坐标
	float x;
	float y;
	//向量
	float vx;
	float vy;
	//高宽
	float width;
	float height;
	//重力
	float g;
	//手臂的角度
	float handRotation;
	//身体角度
	float bodyRotation;
	//手臂角速度
	float handAngularSpeed;
	//身体角速度
	float bodyAngularSpeed;
};

