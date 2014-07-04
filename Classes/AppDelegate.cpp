#include "AppDelegate.h"
//#include "GameScene.h"
#include "IntroLayer.h"
USING_NS_CC;
static CCSize designResolutionSize = CCSizeMake(480, 320);//设计分辨率
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Alex GOGOGO");
		glview->setFrameSize(1136,640);//win32调试使用 iphone4:setFrameSize(960,640) iphone5:setFrameSize(1136,640) ipad:setFrameSize(1024,768)
        director->setOpenGLView(glview);
    }
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
    auto scene = IntroLayer::createScene();
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
