#include "StartPanel.h"
#include "cocos2d.h"
USING_NS_CC;
StartPanel::StartPanel(void)
{
	//����������ɫ
	ccColor4B color4b;
	color4b.r = 141;
	color4b.g = 134;
	color4b.b = 115;
	//������ɫ
	this->bg = CCLayerColor::create(color4b);
	this->addChild(this->bg);

	// ��̨��С
	CCDirector* director = CCDirector::sharedDirector();
	CCSize size = director->getWinSize();

	this->startLabel = CCLabelTTF::create("CLICK TO START", "Helvetica", 20);
	//����������ɫ
	ccColor3B color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	this->startLabel->setColor(color);
	this->startLabel->setPosition(ccp(size.width *.5, size.height *.2));
	this->addChild(this->startLabel);

	//��Ϸ����
	this->nameLabel = CCLabelTTF::create("PUKAMAN", "Arial", 40);
	color.r = 161;
	color.g = 60;
	color.b = 61;
	this->nameLabel->setColor(color);
	this->nameLabel->setPosition(ccp(size.width *.5, size.height *.45));
	this->addChild(this->nameLabel);

	//����
	//sprite ע���Ĭ�������ĵ�
	this->body = CCSprite::create("body.png");
	this->addChild(this->body);
	this->body->setPosition(ccp(size.width * .5, 
								size.height * .5 + 65));
	//�ֱ�
	this->hand = CCSprite::create("hand.png");
	this->addChild(this->hand);
	
	//ê����ݰٷֱȼ��㡣.5Ϊ�߶ȵ�һ��
	this->hand->setAnchorPoint(ccp(0, .5));
	this->hand->setPosition(ccp(this->body->getPosition().x - this->body->getContentSize().width *.5, 
								this->body->getPosition().y - 15));
	//��ӡ�����͵ĸ߶�
	//CCLOG("height %f", this->hand->getContentSize().height * .5);
}

StartPanel::~StartPanel(void)
{
	CCLOG("delete ");
	this->startLabel->removeFromParent();
	this->hand->removeFromParent();
	this->nameLabel->removeFromParent();
	this->body->removeFromParent();
	this->bg->removeFromParent();
}

void StartPanel::changeScene(float t, CCScene* scene)
{
	//�л��������뵭��
	this->nextScene = scene;
	CCTransitionScene* sf = CCTransitionCrossFade::create(t, scene);
	CCDirector::sharedDirector()->replaceScene(sf);
}

void StartPanel::onEnterTransitionDidFinish()
{
	CCLOG("onEnterTransitionDidFinish2");
}

void StartPanel::onExit()
{
	CCLOG("exit");
	this->removeFromParent();
	CCScene::onExit();
}
