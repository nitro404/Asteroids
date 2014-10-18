#include "AppDelegate.h"
#include "Asteroids.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {

}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("Asteroids");
		director->setOpenGLView(glview);
	}

//	director->setDisplayStats(true);
//	director->setAnimationInterval(1.0 / 60);

	auto scene = Asteroids::createScene();
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
//	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
//	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
