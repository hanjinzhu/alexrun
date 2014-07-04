

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
using namespace cocos2d;
class Snake : public cocos2d::CCLayer
{
private:
    CCTMXTiledMap *_tileMap;
    CCTMXLayer *_background;
	CCTMXLayer *_meta;
	CCSprite *_player;
	CCSprite * _cloud;
	CCPoint startPoint;
	int _startPointX;
	int _startPointY;
	int towards;  //1 up 2 left 3 down 4 right
	int prevTowards;
	float speed;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
	void registerWithTouchDispatcher();

	void MutUpdate(float dt);
 
	void setPlayerPosition(CCPoint position);
 
	bool ccTouchBegan(CCTouch *touch, CCEvent *event);

	void ccTouchMoved(CCTouch *touch, CCEvent *event);

	void ccTouchEnded(CCTouch *touch, CCEvent *event);

	void setRun();

	void setEnemy();

	void initPerson();
	//virtual void update(float delta);
	virtual void update(float dt);



	CCPoint tileCoordForPosition(CCPoint position);
	
    // implement the "static node()" method manually
    CREATE_FUNC(Snake);
};

