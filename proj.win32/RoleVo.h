#pragma once
#include "cocos2d.h"
USING_NS_CC;
class RoleVo:public CCObject
{
public:
	RoleVo(void);
	~RoleVo(void);
	//����
	float x;
	float y;
	//����
	float vx;
	float vy;
	//�߿�
	float width;
	float height;
	//����
	float g;
	//�ֱ۵ĽǶ�
	float handRotation;
	//����Ƕ�
	float bodyRotation;
	//�ֱ۽��ٶ�
	float handAngularSpeed;
	//������ٶ�
	float bodyAngularSpeed;
};

