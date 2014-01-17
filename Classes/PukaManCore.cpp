#include "PukaManCore.h"
USING_NS_CC;
PukaManCore::PukaManCore(void)
{
	this->nData = new CCNode();
}

PukaManCore::~PukaManCore(void)
{
}

void PukaManCore::update()
{
	this->standby();
	this->jumpMotion();
	this->roll();
	this->checkBgWidth();
}

/*��ʼ����Ϸ*/
void PukaManCore::initGame( double maxVx, double minVx, 
							double vy, float angularSpeed, 
							double g, int jumpDelay, 
							float top, float bottom)
{
	//��ʼ������
	this->prevJumpDelay = -1;
	this->angularSpeed = angularSpeed;
	this->jumpDelay = jumpDelay;
	this->jumpCombo = 0;

	this->isJump = false;
	this->isFail = false;
	this->isRoll = false;

	this->maxVx = maxVx;
	this->minVx = minVx;
	this->vx = minVx;
	this->vy = vy;
	this->f = .94;
	this->ease = .09;
	this->standbySpeed = .2;
	this->top = top;
	this->bottom = bottom;
	this->g = g;

	this->roleVo = new RoleVo();
	this->roleVo->g = g;
	this->roleVo->x = 180;
	this->roleVo->y = this->bottom;
	this->roleVo->width = 45;
	this->roleVo->height = 64;
	this->maxBgWidth = 640;
	this->minBgWidth = 100;
	this->bgWidth = this->maxBgWidth;

	this->score = 0;
	this->highScore = 0;
	this->scoreVar = 100;
}

/*��Ծ*/
bool PukaManCore::jump()
{
	if(this->isRoll || this->isFail) return false;
	if(this->prevJumpDelay == -1 || this->prevJumpDelay>=this->jumpDelay)
	{
		this->roleVo->vy = this->vy;
		this->roleVo->handAngularSpeed = this->angularSpeed;
		//����ʱ���������
		this->prevJumpDelay = 0;
		this->jumpCombo++;
		this->score+=this->scoreVar;
		this->vx += 4;
		if(this->vx > this->maxVx) this->vx = this->maxVx;
		this->isJump = true;
		return true;
	}
	return false;
}

/*վ������*/
void PukaManCore::standby()
{
	if(!this->isJump && !this->isRoll && !this->isFail)
	{
		this->roleVo->vy = this->standbySpeed;
		this->roleVo->y += this->roleVo->vy;
		if(this->roleVo->y > this->bottom + 2)
			this->standbySpeed *= -1;
		else if(this->roleVo->y < this->bottom - 2)
			this->standbySpeed *= -1;
	}
}

/*�ж���Ծ*/
void PukaManCore::jumpMotion()
{
	if(!this->isJump) return;
	if(!this->isFail)
	{
		if(this->prevJumpDelay!=-1) this->prevJumpDelay++;
		//��������
		if(this->roleVo->vy!=0)
		{
			//����������ܵ�����Ӱ��
			this->roleVo->vy -= this->roleVo->g;
			//���ý��ٶȵ�����
			this->roleVo->handAngularSpeed -= this->roleVo->g;
			this->roleVo->bodyAngularSpeed -= this->roleVo->g;
		}
		//�ֱ۽Ƕ�
		this->roleVo->handRotation+=this->roleVo->handAngularSpeed;
		//��Ծʱ������б�Ƕ�
		this->roleVo->bodyRotation -=this->roleVo->bodyAngularSpeed;
		this->roleVo->y += this->roleVo->vy;
		if(this->roleVo->bodyRotation>20)
		{
			this->roleVo->bodyAngularSpeed = 0;
			this->roleVo->bodyRotation = 20;
		}
		//�ֱ۽Ƕ�������ƶ���Χ
		if(this->roleVo->handRotation > 150)
			this->roleVo->handRotation = 150;
		if(this->roleVo->y < this->bottom + 100 && 
			this->roleVo->y > this->bottom)
		{
			if(this->roleVo->handRotation < 100)
				this->roleVo->handRotation = 100;
		}
		//����������ƶ���Χ
		if(this->roleVo->y > this->top)
		{
			this->roleVo->y = this->top;
			this->roleVo->vy = -(float) abs(this->roleVo->vy) * 0.0001;
		}
		//���䵽����
		if(this->roleVo->y < this->bottom)
		{
			//ʧ��
			this->roleVo->handRotation = 0;
			this->isFail = true;
			CCLOG("fail");
			this->roleVo->y = this->bottom;
			this->roleVo->vy = 0;
			this->roleVo->handAngularSpeed = 0;
			this->prevJumpDelay = -1;
			this->jumpCombo = 0;
			CCString* str = CCString::create("");
			if(this->score > this->highScore)
			{
				this->highScore = this->score;
				str = CCString::create(NEW_RECORD); 
			}
			this->score = 0;
			//����ʧ���¼�
			if(str)	this->nData->setUserData(str);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(FAIL, (CCObject*)this->nData);
			
		}
	}
	else
	{
		//ʧ�����䷭��
		this->isRoll = true;
	}
	
}
/*����*/
void PukaManCore::roll()
{
	if(this->isRoll)
	{
		if(this->roleVo->bodyRotation >= 360)
		{
			this->roleVo->bodyAngularSpeed = 0;
			this->roleVo->bodyRotation = 360;
			this->standbySpeed = .2;
		}
		else
		{
			this->roleVo->bodyAngularSpeed = this->angularSpeed;
			this->roleVo->bodyRotation+=this->roleVo->bodyAngularSpeed;
		}
		this->vx *= this->f;
		if(this->vx < this->minVx && this->roleVo->bodyRotation == 360)
		{
			this->roleVo->bodyRotation = 0;
			this->isFail = false;
			this->isJump = false;
			this->isRoll = false;
			this->vx = this->minVx;
		}
	}
}

void PukaManCore::checkBgWidth()
{
	if(this->isJump)
	{
		if(this->jumpCombo <= 5)
			this->widthDis = this->maxBgWidth - 100 * this->jumpCombo;
		if(this->bgWidth > this->widthDis)
			this->bgWidth -= 1;
		if(this->bgWidth < this->minBgWidth) this->bgWidth = this->minBgWidth;
	}
	else
	{
		//���������
		if(this->bgWidth < this->maxBgWidth)
			this->bgWidth += (this->maxBgWidth - this->bgWidth) * this->ease;
	}
}


