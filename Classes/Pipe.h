#ifndef __PiPe_H__
#define __PiPe_H__

#include "cocos2d.h"

class Pipe 
{
public:
	Pipe();
	void SpawnPipe(cocos2d::Layer *layer);
	
private:
	cocos2d::Size _visibleSize;
	cocos2d::Vec2 _origin;
};

#endif // __PiPe_H__
