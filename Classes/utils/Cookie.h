#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Cookie
{
public:
	Cookie(void);
	~Cookie(void);
	//�Ƿ񱣴�����ش洢
	static bool isSaved();
	//��ȡ�û��洢ָ��
	static CCUserDefault* getShareUserData();
};

