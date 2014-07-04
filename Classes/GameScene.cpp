#include "GameScene.h"
#include "json/rapidjson.h"//加载rapidjson库  
#include "json/document.h"
#define COCOS2D_DEBUG 1
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
	//测试start
	//autoLoadDialog();return true;
	//测试end
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);    
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
void loadMission();//根据配置文件加载关卡

bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point beginTouch = touch->getLocation();    
	_startPointX=beginTouch.x;
	_startPointY=beginTouch.y;
	startPoint=beginTouch;
    return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event)
{
	Point touchLocation = touch->getLocation();
	if(ccpDistance(touchLocation,startPoint)>40){
		CCPoint diff = ccpSub(touchLocation, startPoint);
		if ( abs(diff.x) > abs(diff.y) ) {
			if (diff.x > 0) {
				if(towards==1||towards==3){
					prevTowards=towards;
					towards=4;
				}
		
				CCLog("right");
			} else {
				if(towards==1||towards==3){
					prevTowards=towards;
					towards=2;
				}
				CCLog("left");
			}
		} else {
			if (diff.y > 0) {
				if(towards==2||towards==4){
					prevTowards=towards;
					towards=1;
				}
				CCLog("up");
			} else {
				if(towards==2||towards==4){
					prevTowards=towards;
					towards=3;
				}
				CCLog("down");
			}
		}
	}
//recognizer->movePoint(pos.x, pos.y);
}

void GameLayer::autoLoadDialog(){
	std::string filename="level_dialog/level_1_dialog.json"; 
	rapidjson::Document doc;  
	std::string data=FileUtils::getInstance()->getStringFromFile(filename); 
	
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str()); 
	std::string name;
	std::string avatar;
	int delay;
	std::string content;

	for(int i=0;i<doc.Size();i++){
		rapidjson::Value &v=doc[i];
				name=v["name"].GetString();
				avatar=v["avatar"].GetString(); 
				content=v["content"].GetString(); 
				delay=v["delay"].GetInt(); 
				CCLOG("%s",name.c_str());
	}
	
    //判断文件是否存在  
    //if(!FileUtils::getInstance()->isFileExist(filename))  
    //{  
    //    CCLOG("json file is not find [%s]",filename);         
    //}  else{
	//	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str()); 
	//}
}