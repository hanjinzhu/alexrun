#include "IntroLayer.h"
#include "SnakeScene.h"

IntroLayer::IntroLayer(void)
{
}


IntroLayer::~IntroLayer(void)
{
}
CCScene* IntroLayer::scene()
{
    CCScene *scene = CCScene::create();
    IntroLayer *layer = IntroLayer::create();
    scene->addChild(layer);
    return scene;
}
bool IntroLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	IntroBack = CCSprite::create("cover.png");
	IntroBack->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(IntroBack);
	this->scheduleOnce(schedule_selector(IntroLayer::hideScene),3.0f); 
    return true;
}



void IntroLayer::hideScene(float dt){
	CCScene *pScene = Snake::scene();
    CCTransitionFade* transitionScene = CCTransitionFade::create(2.0f, pScene,ccBLACK);
    CCDirector::sharedDirector()->replaceScene(transitionScene);
}