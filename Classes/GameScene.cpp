#include "GameScene.h"

USING_NS_CC;
//生成场景，将层添加到场景上
Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();


    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("cover.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(480,320));
	sprite->setAnchorPoint(Point(0.5,0.5));
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


