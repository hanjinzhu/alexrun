#pragma once
#include "cocos2d.h"
USING_NS_CC;
class IntroLayer : public Layer
{
private:
	Sprite * IntroBack;
public:
    CREATE_FUNC(IntroLayer);
    virtual bool init();
 
	void hideScene(float dt);
    //static CCScene* scene();
    static Scene* createScene();
};
