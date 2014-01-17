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

/*初始化游戏*/
void PukaManCore::initGame( double maxVx, double minVx, 
							double vy, float angularSpeed, 
							double g, int jumpDelay, 
							float top, float bottom)
{
	//初始化数据
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

/*跳跃*/
bool PukaManCore::jump()
{
	if(this->isRoll || this->isFail) return false;
	if(this->prevJumpDelay == -1 || this->prevJumpDelay>=this->jumpDelay)
	{
		this->roleVo->vy = this->vy;
		this->roleVo->handAngularSpeed = this->angularSpeed;
		//跳起时间计数归零
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

/*站立待机*/
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

/*判断跳跃*/
void PukaManCore::jumpMotion()
{
	if(!this->isJump) return;
	if(!this->isFail)
	{
		if(this->prevJumpDelay!=-1) this->prevJumpDelay++;
		//人物跳起
		if(this->roleVo->vy!=0)
		{
			//人物跳起后受到重力影响
			this->roleVo->vy -= this->roleVo->g;
			//设置角速度的重力
			this->roleVo->handAngularSpeed -= this->roleVo->g;
			this->roleVo->bodyAngularSpeed -= this->roleVo->g;
		}
		//手臂角度
		this->roleVo->handRotation+=this->roleVo->handAngularSpeed;
		//跳跃时身体倾斜角度
		this->roleVo->bodyRotation -=this->roleVo->bodyAngularSpeed;
		this->roleVo->y += this->roleVo->vy;
		if(this->roleVo->bodyRotation>20)
		{
			this->roleVo->bodyAngularSpeed = 0;
			this->roleVo->bodyRotation = 20;
		}
		//手臂角度跳起后移动范围
		if(this->roleVo->handRotation > 150)
			this->roleVo->handRotation = 150;
		if(this->roleVo->y < this->bottom + 100 && 
			this->roleVo->y > this->bottom)
		{
			if(this->roleVo->handRotation < 100)
				this->roleVo->handRotation = 100;
		}
		//人物跳起后移动范围
		if(this->roleVo->y > this->top)
		{
			this->roleVo->y = this->top;
			this->roleVo->vy = -(float) abs(this->roleVo->vy) * 0.0001;
		}
		//下落到地面
		if(this->roleVo->y < this->bottom)
		{
			//失败
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
			//发送失败事件
			if(str)	this->nData->setUserData(str);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(FAIL, (CCObject*)this->nData);
			
		}
	}
	else
	{
		//失败下落翻滚
		this->isRoll = true;
	}
	
}
/*滚动*/
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
		//背景变宽缓动
		if(this->bgWidth < this->maxBgWidth)
			this->bgWidth += (this->maxBgWidth - this->bgWidth) * this->ease;
	}
}


