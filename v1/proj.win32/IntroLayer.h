#pragma once
#include "cocos2d.h"
using namespace cocos2d;
class IntroLayer : CCLayer
{
private:
	CCSprite * IntroBack;
public:

    IntroLayer();
	~IntroLayer();
    CREATE_FUNC(IntroLayer);
    virtual bool init();
 
	void hideScene(float dt);
    static CCScene* scene();
};

