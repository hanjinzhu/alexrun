#include "IntroLayer.h"
#include "GameScene.h"

Scene* IntroLayer::createScene()
{
	Size winSize = Director::getInstance()->getWinSize();
    auto scene = Scene::create();
	auto bgColorLayer = LayerColor::create(ccc4(0xff, 0xcc, 0x00, 255),winSize.width, winSize.height); 
	bgColorLayer->ignoreAnchorPointForPosition(false);  
	bgColorLayer->setPosition(Point(winSize.width/2,winSize.height/2)); 
	scene->addChild(bgColorLayer);  //±³¾°Æ½ÆÌ

    auto layer = IntroLayer::create();
    scene->addChild(layer);
    return scene;
}


bool IntroLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
    if ( !Layer::init() )
    {
        return false;
    }
	
	IntroBack = Sprite::create("sohu_cover.png");
	IntroBack->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(IntroBack);
	this->scheduleOnce(schedule_selector(IntroLayer::hideScene),3.0f); 
    return true;
}



void IntroLayer::hideScene(float dt){
	auto pScene = GameLayer::createScene();
    auto transitionScene = TransitionFade::create(2.0f, pScene,ccBLACK);
    Director::getInstance()->replaceScene(transitionScene);
}