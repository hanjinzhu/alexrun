#include "SnakeScene.h"
using namespace cocos2d;

CCScene* Snake::scene()
{
  // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
 
    // 'layer' is an autorelease object
    Snake *layer = Snake::create();
 
    // add layer as a child to scene
    scene->addChild(layer);
 	
    // return the scene
    return scene;
    
}

// on "init" you need to initialize your instance
bool Snake::init()
{
	towards=4;
	//speed=1.0f;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if ( !CCLayer::init() )
    {
        return false;
    }
    this->setTouchEnabled(true);

    _tileMap = new CCTMXTiledMap();
    _tileMap->initWithTMXFile("snake.tmx");
    _background = _tileMap->layerNamed("sprite");
 
    this->addChild(_tileMap);
	_meta = _tileMap->layerNamed("meta");
	_meta->setVisible(false);

	CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("object");
	if(objectGroup == NULL){
		CCLog("tile map has no objects object layer");
		return false;
	}
 
	CCDictionary *spawnPoint = objectGroup->objectNamed("SpawnPoint");
	int x = ((CCString)*spawnPoint->valueForKey("x")).intValue();
	int y = ((CCString)*spawnPoint->valueForKey("y")).intValue();
	_player=CCSprite::create("run1.png");
		
	_player->setPosition(ccp(x,y));
	this->addChild(_player);
	this->setRun();

	_cloud = CCSprite::create("cloud.png");
	_cloud->setPosition(ccp(-300,winSize.height-200));
	CCActionInterval *monstersMove = CCMoveTo::create(100,ccp(winSize.width+300,winSize.height-200));
	_cloud->runAction(monstersMove);
	this->addChild(_cloud);
	this->scheduleUpdate();
	//this->schedule(schedule_selector(Snake::MutUpdate), 0.8f);
    return true;
}


 
void Snake::setPlayerPosition(CCPoint position) {
	CCPoint tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->tileGIDAt(tileCoord);
    if (tileGid) {
        CCDictionary *properties = _tileMap->propertiesForGID(tileGid);
        if (properties) {
            CCString *collision = new CCString();
            *collision = *properties->valueForKey("Collidable");  //判断地图的碰撞
            if (collision) {
				CCLog("shit!");
                return;
            }
        }
    }
    _player->setPosition(position);
}

CCPoint Snake::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}

 void Snake::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
 
bool Snake::ccTouchBegan(CCTouch *touch, CCEvent *event)
{
	CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	_startPointX=touchLocation.x;
	_startPointY=touchLocation.y;
	startPoint=touchLocation;
    return true;
}
void Snake::ccTouchMoved(CCTouch *touch, CCEvent *event)
{
	CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	//ccpDistance(touchLocation,startPoint);
	
	if(ccpDistance(touchLocation,startPoint)>40){
		CCPoint diff = ccpSub(touchLocation, startPoint);
		if ( abs(diff.x) > abs(diff.y) ) {
			if (diff.x > 0) {
				if(towards==1||towards==3){
					prevTowards=towards;
					towards=4;
				}
				_player->setFlipX(false);
				//CCLog("right");
			} else {
				if(towards==1||towards==3){
					prevTowards=towards;
					towards=2;
				}
				_player->setFlipX(true);
				//CCLog("left");
			}
		} else {
			if (diff.y > 0) {
				if(towards==2||towards==4){
					prevTowards=towards;
					towards=1;
				}
				//CCLog("up");
			} else {
				if(towards==2||towards==4){
					prevTowards=towards;
					towards=3;
				}
				//CCLog("down");
			}
		}
	}


}
void Snake::ccTouchEnded(CCTouch *touch, CCEvent *event)
{

    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	//char p[10] ;
	//itoa(touchLocation.x, p, 10); 
	//CCLog(p);

}

void Snake::setRun(){
	CCAnimation * boomAni = CCAnimation::create();
    boomAni -> addSpriteFrameWithFileName("run1.png");
    boomAni -> addSpriteFrameWithFileName("run2.png");
    boomAni -> addSpriteFrameWithFileName("run3.png");
    boomAni -> setDelayPerUnit(0.1f);
    boomAni -> setRestoreOriginalFrame(true);
	_player->runAction(CCRepeatForever::create(CCAnimate::create(boomAni))); 
}

void Snake::update(float dt){
	CCPoint playerPos = _player->getPosition();
	int playPosX=playerPos.x;
	int playPosY=playerPos.y;
	int mapWidth=_tileMap->getTileSize().width;
	int mapHeight=_tileMap->getTileSize().height;
	switch(towards){
	   case 1:  //up
		  if(prevTowards==4){
			  if(playPosX%16!=0||playPosX%32==0){//向右剩余动作
				  playerPos.x += 2;
				  break;
			  }
		  }
		  if(prevTowards==2){
			  if(playPosX%16!=0||playPosX%32==0){//向左剩余动作
				  playerPos.x -= 2;
				  break;
			  }
		  }
		  playerPos.y += 2;
		  break;
	   case 2:  //left
		  if(prevTowards==1){
			  if(playPosY%16!=0||playPosY%32==0){//向上剩余动作
				  playerPos.y += 2;
				  break;
			  }
		  }
		  if(prevTowards==3){
			  if(playPosY%16!=0||playPosY%32==0){//向下剩余动作
				  playerPos.y -= 2;
				  break;
			  }
		  }
		  playerPos.x -= 2;
		  break;
	   case 3:  //down
		  if(prevTowards==4){
			  if(playPosX%16!=0||playPosX%32==0){//向右剩余动作
				  playerPos.x +=2;
				  char p[10] ;
				  itoa(playPosX, p, 10); 
				  CCLog(p);
				  break;
			  }
		  }
		  	//char p[10] ;
			//itoa(touchLocation.x, p, 10); 
			//CCLog(p);
		  if(prevTowards==2){
			  if(playPosX%16!=0||playPosX%32==0){//向左剩余动作
				  playerPos.x -= 2;
				  break;
			  }
		  }
		  playerPos.y -= 2;
		  break;
	   case 4:   //right
		  if(prevTowards==1){
			  if(playPosY%16!=0||playPosY%32==0){//向上剩余动作
				  playerPos.y += 2;
				  break;
			  }
		  }
		  if(prevTowards==3){
			  if(playPosY%16!=0||playPosY%32==0){//向下剩余动作
				  playerPos.y -= 2;
				  break;
			  }
		  }
		  playerPos.x += 2;
		  break;
	   default:
		  break;
	}
	this->setPlayerPosition(playerPos);

}

void Snake::MutUpdate(float dt){
	CCPoint playerPos = _player->getPosition();

	switch(towards){
	   case 1:
		  playerPos.y += _tileMap->getTileSize().height;
		  break;
	   case 2:
		  playerPos.x -= _tileMap->getTileSize().width;
		  break;
	   case 3:
		  playerPos.y -= _tileMap->getTileSize().width;
		  break;
	   case 4:
		  playerPos.x += _tileMap->getTileSize().width;
		  break;
	   default:
		  break;
	}
	this->setPlayerPosition(playerPos);
}