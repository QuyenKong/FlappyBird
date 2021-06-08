#include "Bird.h"
#include "Definitions.h"


USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer)
{
	_visibleSize = Director::getInstance()->getVisibleSize();
	_origin = Director::getInstance()->getVisibleOrigin();

	flappyBird = Sprite::create("ipadhd/Ball.png");
	flappyBird->setPosition(Point(_visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));

	auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2 );
	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);
		flappyBird->setPhysicsBody(flappyBody);

	layer->addChild(flappyBird, 100);

	isFalling = true;
}

void Bird::fall() {
	if (true == isFalling) {
		flappyBird->setPositionX(_visibleSize.width / 2 + _origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * _visibleSize.height));
	}
	else
	{
		flappyBird->setPositionX(_visibleSize.width / 2 + _origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + (BIRD_FALLING_SPEED * _visibleSize.height));
	}
}