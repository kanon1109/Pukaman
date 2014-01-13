#include "GameStage.h"
#include "ColorUtil.h"
USING_NS_CC;
GameStage::GameStage(void)
{
	this->stageWidth = CCDirector::sharedDirector()->getVisibleSize().width;
	this->stageHeight = CCDirector::sharedDirector()->getVisibleSize().height;
	//是否被显示
	this->isShowed = false;
	//背景
	ccColor4B color4b;
	color4b.r = 42;
	color4b.g = 43;
	color4b.b = 38;
	color4b.a = 0xFF;
	this->background = CCLayerColor::create(color4b);
	this->addChild(this->background);

	//运动背景
	float bgWidth = 43;
	float bgHeigth = stageHeight - 150;
	float gapH = 10;
	//使这个数组已经是当前类的成员变量，也必须要做一次retain
	this->drawBgList = CCArray::create();
	this->drawBgList->retain();

	ccColor4F color4f = ColorUtil::getColor4F(56, 57, 51, 255);

	CCDrawNode* drawNode = this->createMotionWall(0, 150, bgWidth, bgHeigth, gapH, color4f);
	float posX = drawNode->getContentSize().width;
	this->drawBgList->addObject(drawNode);
	this->addChild(drawNode);

	drawNode = this->createMotionWall(0, 150, bgWidth, bgHeigth, gapH, color4f);
	drawNode->setPositionX(posX);
	this->drawBgList->addObject(drawNode);
	this->addChild(drawNode);

	//地板
	color4b.r = 116;
	color4b.g = 115;
	color4b.b = 98;
	color4b.a = 0xFF;
	this->floorBg = CCLayerColor::create(color4b);

	CCSize size = CCSizeMake(this->stageWidth, 141);
	this->floorBg->setContentSize(size);
	this->addChild(this->floorBg);
	//地板线条
	color4b.r = 72;
	color4b.g = 66;
	color4b.b = 50;
	color4b.a = 0xFF;
	this->floorLineBg = CCLayerColor::create(color4b);
	size = CCSizeMake(this->stageWidth, 10);
	this->floorLineBg->setContentSize(size);
	this->addChild(this->floorLineBg);
	this->floorLineBg->setPositionY(this->floorBg->getContentSize().height);

	//前景
	this->frontBgList = CCArray::create();
	this->frontBgList->retain();

	for (int i = 0; i < 3; i++)
	{
		drawNode = this->createFrontMotionWall(0, 83, this->stageWidth, this->stageHeight - 83, i);
		this->addChild(drawNode);
		drawNode->setPositionX(this->stageWidth * (i - 1));
		this->frontBgList->addObject(drawNode);
	}
	//初始化角色
	this->role = CCSprite::create();
	this->addChild(this->role);
	//身体
	this->body = CCSprite::create("body.png");
	this->role->addChild(this->body);
	this->body->setAnchorPoint(ccp(.5, .5));
	
	//手臂
	this->hand = CCSprite::create("hand.png");
	this->role->addChild(hand);
	this->hand->setAnchorPoint(ccp(0.12, 0.7));
	this->hand->setPosition(ccp(this->body->getPosition().x - this->body->getContentSize().width *.5 + 5, 
								this->body->getPosition().y +
								this->hand->getContentSize().height - 35));

	this->uiLayer = CCLayer::create();
	this->uiText = CCSprite::create("uiText.png");
	this->uiText->setAnchorPoint(ccp(0, 0));
	this->uiText->setPositionY(this->stageHeight - 50);
	this->uiLayer->addChild(this->uiText);
	this->addChild(this->uiLayer);

	this->bomb = NULL;
	//初始化核心类
	this->pukaManCore = new PukaManCore();
	this->pukaManCore->initGame(25, 2, 15, 15, .98, 5, CCDirector::sharedDirector()->getVisibleSize().height - 35, 70);
	
	//设置初始位置
	this->role->setPosition(ccp(this->pukaManCore->roleVo->x, 
								this->pukaManCore->roleVo->y));

	this->comboList = NULL;
	this->scoreList = NULL;
	this->highScoreList = NULL;
	//设置bombo数字
	this->updateCombo();
	this->updateScore();
	//设置最高分数数字
	this->updateHighScore();

	this->addScoreSpt = CCSprite::create();
	this->addScoreList = CCArray::create();
	this->addScoreList->retain();
	this->updateNumSprite(this->addScoreSpt, 
						  this->addScoreList, 
						  this->pukaManCore->scoreVar, 0, 0);
	this->uiLayer->addChild(this->addScoreSpt);
	//加号
	CCSprite* addSpt = CCSprite::create("zAdd.png");
	addSpt->setAnchorPoint(ccp(0, 0));
	addSpt->setPositionX(-addSpt->getContentSize().width * .5);
	this->addScoreSpt->addChild(addSpt);
	this->addScoreList->insertObject(addSpt, 0);

	this->layoutScoreNum(this->addScoreList, 0);
	//父sprite执行颜色变化的时候，子sprite也可以执行到这个变化
	this->addScoreSpt->setCascadeOpacityEnabled(true);
	this->addScoreSpt->setVisible(false);

	this->newHighScore = CCSprite::create("newHighScore.png");
	this->newHighScore->setAnchorPoint(ccp(0.5, 0.5));
	this->newHighScore->setPosition(ccp(this->stageWidth * .5, this->stageHeight * .5));
	this->newHighScore->setScale(0.0f);
	this->uiLayer->addChild(this->newHighScore);
}

GameStage::~GameStage(void)
{
	this->background->removeFromParent();
	this->floorBg->removeFromParent();
	this->floorLineBg->removeFromParent();
	this->hand->removeFromParent();
	this->body->removeFromParent();
	this->uiText->removeFromParent();
	this->uiLayer->removeFromParent();

	CC_SAFE_RELEASE(this->uiText);
	CC_SAFE_RELEASE(this->uiLayer);
	CC_SAFE_RELEASE(this->body);
	CC_SAFE_RELEASE(this->hand);
	CC_SAFE_RELEASE(this->background);
	CC_SAFE_RELEASE(this->floorBg);
	CC_SAFE_RELEASE(this->floorLineBg);

	if(this->bomb)
	{
		this->bomb->removeFromParent();
		this->bomb->stopSystem();
	}
	CC_SAFE_RELEASE(this->bomb);

	//删除数组
	this->removeList(this->comboList);
	this->removeList(this->scoreList);
	this->removeList(this->highScoreList);
	this->removeList(this->addScoreList);
	this->addScoreSpt->stopAllActions();
	this->newHighScore->stopAllActions();
	this->addScoreSpt->removeFromParent();
	this->newHighScore->removeFromParent();
	CC_SAFE_RELEASE(this->addScoreSpt);
	CC_SAFE_RELEASE(this->newHighScore);

	int length = this->drawBgList->count();
	CCDrawNode* dn;
	for (int i = length -1 ; i >= 0; i-=1)
	{
		dn = static_cast<CCDrawNode *>(this->drawBgList->objectAtIndex(i));
		dn->removeFromParent();
		this->drawBgList->removeObject(dn);
	}
	CC_SAFE_RELEASE(this->drawBgList);

	length = this->frontBgList->count();
	for (int i = length -1 ; i >= 0; i-=1)
	{
		dn = static_cast<CCDrawNode *>(this->frontBgList->objectAtIndex(i));
		dn->removeFromParent();
		this->frontBgList->removeObject(dn);
	}
	CC_SAFE_RELEASE(this->frontBgList);
}

/*主循环*/
void GameStage::loop(float dt)
{
	this->pukaManCore->update();
	this->render();
}

/*渲染*/
void GameStage::render()
{
	//人物移动和设置手臂和身体的角度
	this->hand->setRotation(this->pukaManCore->roleVo->handRotation);
	this->role->setRotation(this->pukaManCore->roleVo->bodyRotation);
	this->role->setPosition(ccp(this->pukaManCore->roleVo->x, 
								this->pukaManCore->roleVo->y));
	//运动背景移动
	CCDrawNode* drawNode;
	float dis;
	int length = this->drawBgList->count();
	for (int i = 0; i < length; i+=1)
	{
		drawNode = static_cast<CCDrawNode *>(this->drawBgList->objectAtIndex(i));
		if (drawNode->getPositionX() < -drawNode->getContentSize().width)
		{
			//计算移到出边界后的误差，并取绝对值。 重新设置背景的位置并减轻误差。
			dis = (float) abs(drawNode->getPositionX()) - drawNode->getContentSize().width;
			drawNode->setPositionX(drawNode->getContentSize().width - dis);
		}
		drawNode->setPositionX(drawNode->getPositionX() - this->pukaManCore->vx *.5);
	}
	//前景
	length = this->frontBgList->count();
	CCDrawNode* lastDrawNode;
	CCDrawNode* prevDrawNode;
	for (int i = length - 1; i >= 0; i-=1)
	{
		drawNode = static_cast<CCDrawNode *>(this->frontBgList->objectAtIndex(i));
		if (drawNode->getPositionX() <-drawNode->getContentSize().width - this->stageWidth)
		{
			//计算移到出边界后的误差，并取绝对值。 重新设置背景的位置并减轻误差。
			dis = (float) abs(drawNode->getPositionX()) - (drawNode->getContentSize().width + this->stageWidth);
			lastDrawNode = static_cast<CCDrawNode *>(this->frontBgList->objectAtIndex(length - 1));
			drawNode->setPositionX(lastDrawNode->getPositionX() + this->stageWidth - dis);
			this->frontBgList->removeObjectAtIndex(i);
			this->frontBgList->addObject(drawNode);
		}

		if(i > 0)
		{
			prevDrawNode = static_cast<CCDrawNode *>(this->frontBgList->objectAtIndex(i - 1));
			drawNode->setPositionX(prevDrawNode->getPositionX() + this->stageWidth);
		}

		float scale = this->pukaManCore->bgWidth / this->stageWidth;
		drawNode->setContentSize(CCSizeMake(this->pukaManCore->bgWidth, 
											drawNode->getContentSize().height));
		drawNode->setScaleX(scale);
		drawNode->setPositionX(drawNode->getPositionX() - this->pukaManCore->vx);
	}
}

void GameStage::changeScene(float t, CCScene* scene)
{
	CCTransitionScene* sf = CCTransitionJumpZoom::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(sf);
}

void GameStage::onEnterTransitionDidFinish()
{
	CCLOG("onEnterTransitionDidFinish");
	this->isShowed = true;
	this->startLoop();
}

void GameStage::onEnter()
{
	CCLOG("gamestage onEnter");
	//监听失败消息
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(GameStage::failCallBackFun),  // 处理的消息的回调函数
		FAIL,  // 感兴趣的消息名称
		NULL);   
	//必须覆盖onEnter才能执行 loop监听
	CCScene::onEnter();
}

void GameStage::onExit()
{
	//销毁监听
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, FAIL); 
	CCScene::onExit();
}


/*开启主循环*/
void GameStage::startLoop()
{
	this->schedule(schedule_selector(GameStage::loop));
}

void GameStage::stopLoop()
{
	this->unschedule(schedule_selector(GameStage::loop));
}

/*点击*/
void GameStage::touch()
{
	if(this->inWallBoundaries())
	{
		if(this->pukaManCore->jump())
		{
			this->bomb = CCParticleSystemQuad::create("Bombo.plist");
			//播放完后自动销毁
			this->bomb->setAutoRemoveOnFinish(true);
			this->addChild(this->bomb);
			this->bomb->setPosition(this->getGunPos());

			this->updateCombo();
			this->updateScore();
			this->layoutScoreNum(this->scoreList, 1);

			this->addScoreSpt->setPosition(ccp(this->role->getPositionX() - 20, 
											   this->role->getPositionY() + 
											   this->role->getContentSize().height + 50));
			
			this->addScoreSpt->setVisible(true);
			this->addScoreSpt->stopAllActions();
			//移动动作
			CCActionInterval* moveTo = CCMoveTo::create(0.5f, ccp(this->addScoreSpt->getPositionX(), 
													 this->addScoreSpt->getPositionY() + 40));
			//淡出动作
			CCActionInterval* fadeout = CCFadeOut::create(0.5f);
			//并列动作
			CCSpawn* spawn = CCSpawn::create(moveTo, fadeout, NULL);
			this->addScoreSpt->runAction(spawn);
		}
	}
}
/*判断跳跃范围，只有在有背景的范围下才能跳跃*/
bool GameStage::inWallBoundaries()
{
	CCDrawNode* drawNode;
	int length = this->frontBgList->count();
	float left;
	float right;
	for (int i = length - 1; i >= 0; i-=1)
	{
		drawNode = static_cast<CCDrawNode *>(this->frontBgList->objectAtIndex(i));
		left = drawNode->getPositionX();
		right = left + drawNode->getContentSize().width;
		if(this->role->getPositionX() >= left && 
			this->role->getPositionX() <= right)
			return true;
	}
	return false;
}

/*创建运动背景*/
CCDrawNode* GameStage::createMotionWall(float x, float y, 
									  float bgWidth, float bgHeight, 
									  float gapH, ccColor4F color)
{
	int num = (int)(this->stageWidth / (bgWidth + gapH));
	CCDrawNode* drawNode = CCDrawNode::create();
	for (int i = 0; i < num; i+=1)
	{
		int startX = i * (bgWidth + gapH) + x;
		CCPoint points[] = {CCPoint(startX, y), 
							CCPoint(startX, bgHeight + y), 
							CCPoint(startX + bgWidth, bgHeight + y), 
							CCPoint(startX + bgWidth, y)};
		//顶点列表，顶点数量，颜色
		drawNode->drawPolygon(points, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));
	}
	//如果不设置宽高则 始终为0，即使内部有复杂的绘图。
	drawNode->setContentSize(CCSizeMake(num * (bgWidth + gapH), bgHeight));
	return drawNode;
}

/*创建运动前景*/
CCDrawNode* GameStage::createFrontMotionWall(float x, float y, 
											 float bgWidth, float bgHeight, 
											 int tag)
{
	//前景列表
	CCDrawNode* drawNode = CCDrawNode::create();
	ccColor4F color = ColorUtil::getColor4F(141, 143, 129, 255);
	CCPoint points[] = {CCPoint(x, y), 
						CCPoint(x,  bgHeight + y), 
						CCPoint(x + bgWidth, bgHeight + y), 
						CCPoint(x + bgWidth, y)};
	//顶点列表，顶点数量，颜色
	drawNode->drawPolygon(points, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));

	//前景中段
	float my = y + 97;
	float mHeight = 93;
	color = ColorUtil::getColor4F(103, 107, 82, 255);
	CCPoint points2[] = {CCPoint(x, my), 
						 CCPoint(x,  mHeight + my), 
						 CCPoint(x + bgWidth, mHeight + my), 
						 CCPoint(x + bgWidth, my)};
	drawNode->drawPolygon(points2, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));
	
	mHeight = 3;
	my = my - mHeight;
	color = ColorUtil::getColor4F(86, 90, 67, 255);
	CCPoint points3[] = {CCPoint(x, my), 
						 CCPoint(x,  mHeight + my), 
						 CCPoint(x + bgWidth, mHeight + my), 
						 CCPoint(x + bgWidth, my)};
	drawNode->drawPolygon(points3, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));
	
	mHeight = 2;
	my = my - mHeight;
	color = ColorUtil::getColor4F(100, 103, 82, 255);
	CCPoint points4[] = {CCPoint(x, my), 
						 CCPoint(x,  mHeight + my), 
						 CCPoint(x + bgWidth, mHeight + my), 
						 CCPoint(x + bgWidth, my)};
	drawNode->drawPolygon(points4, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));

	mHeight = 1;
	my = my - mHeight;
	color = ColorUtil::getColor4F(113, 116, 99, 255);
	CCPoint points5[] = {CCPoint(x, my), 
		CCPoint(x,  mHeight + my), 
		CCPoint(x + bgWidth, mHeight + my), 
		CCPoint(x + bgWidth, my)};
	drawNode->drawPolygon(points5, 4, color, 0, ColorUtil::getColor4F(0, 0, 0, 0));
	drawNode->setAnchorPoint(ccp(0, 0));
	drawNode->setContentSize(CCSizeMake(bgWidth, bgHeight));

	//创建阴影 设置注册点在top和center
	CCSprite* shadow = CCSprite::create("shadow.png");
	shadow->setTag(tag);
	shadow->setAnchorPoint(ccp(.5, 1));
	shadow->setPosition(ccp(shadow->getContentSize().width *.5, y));
	drawNode->setTag(tag);
	drawNode->addChild(shadow);
	return drawNode;
}
//获取枪口的坐标
cocos2d::CCPoint GameStage::getGunPos()
{
	float dis = this->hand->getContentSize().width;
	float radian = CC_DEGREES_TO_RADIANS(this->hand->getRotation() + 90);
	double x = sin(radian) * dis - 43;
	double y = cos(radian) * dis + 50;
	CCPoint pos = this->body->convertToWorldSpaceAR(ccp(x, y));
	if(pos.y > this->stageHeight - 50) pos.y = this->stageHeight - 50;
	return pos;
}

//获取数字纹理 char *背后的含义是：给我个字符串，我要修改它。const char *背后的含义是：给我个字符串，我只要读取它。
void GameStage::getNumTexture(CCArray* textureNameList, const char* headStr, int num, const char* tail)
{
	//最多11位char数组
	char numStr[12] = "0";
	//将int转换为字符串numStr
	sprintf(numStr, "%i", num);
	int length = strlen(numStr);
	CCSprite* numSpt;
	for (int i = 0; i < length; i++)
	{
		//创建numChar指针
		char numChar[2] = { numStr[i] };
		//创建一个长度为6的name char指针。
		char name[7] = "";
		//将字符串headStr合并入name
		strcat(name, headStr);
		strcat(name, numChar);
		strcat(name, tail);
		numSpt = CCSprite::create(name);
		numSpt->setAnchorPoint(ccp(0, 0));
		textureNameList->addObject(numSpt);
	}
}

void GameStage::updateNumSprite(CCNode* node, CCArray* souceList, int num, 
								float startX, float startY)
{
	this->getNumTexture(souceList, "z", num, ".png");
	CCSprite* numSpt;
	int length = souceList->count();
	float gapH = -5;
	for (int i = 0; i < length; i++)
	{
		numSpt = static_cast<CCSprite *>(souceList->objectAtIndex(i));
		numSpt->setPosition(ccp(startX + (numSpt->getContentSize().width + gapH) * i, startY));
		node->addChild(numSpt);
	}
}

//销毁连击列表中的内容
void GameStage::removeList(CCArray* list)
{
	if(list)
	{
		int length = list->count();
		CCSprite* spt;
		for (int i = length -1 ; i >= 0; i-=1)
		{
			spt = static_cast<CCSprite *>(list->objectAtIndex(i));
			spt->removeFromParent();
			list->removeObject(spt);
		}
	}
	CC_SAFE_RELEASE(list);
}

//失败回调
void GameStage::failCallBackFun(CCObject* data)
{
	this->updateCombo();
	this->updateScore();
	this->updateHighScore();
	this->layoutScoreNum(this->highScoreList, 2);
	//this->newHighScore->stopAllActions();
	CCNode* nNode = (CCNode*) data;
	CCString* str = (CCString*)nNode->getUserData();
	//判断2个字符串相等
	if(str->isEqual(&CCString(NEW_RECORD)))
	{
		this->newHighScore->stopAllActions();
		this->newHighScore->setScale(0.0f);
		CCActionInterval* scaleTo1 = CCScaleTo::create(0.5f, 1.0f);
		CCDelayTime* delayTime = CCDelayTime::create(1.0f);
		CCActionInterval* scaleTo2 = CCScaleTo::create(0.5f, 0.0f);
		CCSequence* sequence = CCSequence::create(scaleTo1, delayTime, scaleTo2, NULL);
		this->newHighScore->runAction(sequence);
	}
}

void GameStage::layoutScoreNum(CCArray* list, int align)
{
	if(list)
	{
		int length = list->count();
		if(length == 1) return;
		if(align < 0) align = 0;
		else if(align > 2) align = 2;
		float var;
		if(align == 0) var = 0; //左对齐
		else if (align == 1) var = .5;//居中
		else if (align == 2) var = 1;//有对齐

		CCSprite* lastSpt = static_cast<CCSprite *>(list->objectAtIndex(length - 1));
		CCSprite* firstSpt = static_cast<CCSprite *>(list->objectAtIndex(0));
		float width = lastSpt->getPositionX() - firstSpt->getPositionX();
		CCSprite* spt;
		for (int i = length -1 ; i >= 0; i-=1)
		{
			spt = static_cast<CCSprite *>(list->objectAtIndex(i));
			spt->setPositionX(spt->getPositionX() - width * var);
		}
	}
}

void GameStage::updateCombo()
{
	this->removeList(this->comboList);
	this->comboList = CCArray::create();
	this->comboList->retain();
	this->updateNumSprite(this->uiLayer, this->comboList, 
						  this->pukaManCore->jumpCombo, 18, 
						  this->stageHeight - 33);
}

void GameStage::updateScore()
{
	this->removeList(this->scoreList);
	this->scoreList = CCArray::create();
	this->scoreList->retain();
	this->updateNumSprite(this->uiLayer, this->scoreList, 
						 this->pukaManCore->score, 
						 this->stageWidth * .5 - 28, 
						 this->stageHeight - 33);
}

void GameStage::updateHighScore()
{
	this->removeList(this->highScoreList);
	this->highScoreList = CCArray::create();
	this->highScoreList->retain();
	this->updateNumSprite(this->uiLayer, this->highScoreList, 
					 	 this->pukaManCore->highScore, 
						 this->stageWidth - 18, 
						 this->stageHeight - 33);
}
