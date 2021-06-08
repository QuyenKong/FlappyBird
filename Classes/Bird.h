#ifndef __BIRD_H__
#define __BIRD_H__
#include <cocos/audio/include/SimpleAudioEngine.h>
#include "cocos2d.h"

class Bird 
{
public:
	Bird(cocos2d::Layer *layer);
	void fall();
	void fly() { CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Wing.mp3") ;
	isFalling = false; };
	void stopFlying() { isFalling = true;}

private:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;

	cocos2d::Sprite* flappyBird;

	bool isFalling;


};

#endif // __BIRD_H__
