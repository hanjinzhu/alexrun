#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class GameLayer : public Layer
{
private:
	CCPoint startPoint;
	int _startPointX;
	int _startPointY;
	int towards;  //1 up 2 left 3 down 4 right
	int prevTowards;//1 up 2 left 3 down 4 right
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
	void autoLoadDialog();   ////////////////////这是测试函数
	void loadMission();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);//触摸事件监听回调函数
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
};

#endif // __GAME_SCENE_H__
