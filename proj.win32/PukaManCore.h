#pragma once
//ʧ����Ϣ��
#define FAIL "fail"
//ʧ����Ϣ �¼�¼��
#define NEW_RECORD "newRecord"
#include "cocos2d.h"
#include "RoleVo.h"
USING_NS_CC;
class PukaManCore:public CCObject
{
public:
	PukaManCore(void);
	~PukaManCore(void);
	//��ɫ
	RoleVo* roleVo;
	//���x�ٶ�
	double maxVx;
	//��Сx�ٶ�
	double minVx;
	//�Ƿ�ʧ��
	bool isFail;
	//�ٶ�
	double vx;
	double vy;
	//�������
	float bgWidth;
	//��Ծ����
	int jumpCombo;
	//����
	int score;
	//��߷�
	int highScore;
	//�������� ��Ծһ�����ӵķ���
	int scoreVar;
	//��Ծ
	bool jump();
	//���·���
	void update();
	//��ʼ����Ϸ ���x�ٶȡ���Сx�ٶȡ�y�ٶȡ����ٶȡ����� ��Ծ����� ���·�Χ
	void initGame(double maxVx, double minVx, double vy, float angularSpeed, double g, int jumpDelay, float top, float bottom);
private:
	//���ٶ�
	float angularSpeed;
	//�����ٶ�
	double standbySpeed;
	//����
	double g;
	//�ϲ���Χ����
	float top;
	//�²���Χ����
	float bottom;
	//�Ƿ�����
	bool isJump;
	//��һ������ʱ��
	int prevJumpDelay;
	//��Ծ���
	int jumpDelay;
	//�Ƿ񷭹�
	bool isRoll;
	//վ������
	void standby();
	//�ж���Ծ
	void jumpMotion();
	//����
	void roll();
	//�жϱ������
	void checkBgWidth();
	//��غ�vx��Ħ����
	double f;
	//����ָ��
	double ease;
	//���̬�������
	int maxBgWidth;
	//�����Ҫ���ٵ���
	int widthDis;
	//��С��̬�������
	int minBgWidth;
	//��Ϣ����
	CCNode* nData;
};

