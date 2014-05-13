#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "dxco/SpriteUtil.h"
#include "dxco/Joystick.h"
#include "crimson/JoystickMira.h"
#include "crimson/JoystickMovimiento.h"
#include "crimson/GameModel.h"
#include "crimson/Player.h"
#include "dxco/Animation.h"
#include <map>

USING_NS_CC;


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite* pSprite = dxco::SpriteUtil::create("grass-texture-2.jpg", 0, 0, visibleSize.width, visibleSize.height);
    this->addChild(pSprite, 0);

    this->scheduleUpdate();
    this->setTouchEnabled(true);

    CCSprite* joystickFondo = dxco::SpriteUtil::create("circulo.png", visibleSize.width *  0.85 - 80, 20, 80, 80);
    this->addChild(joystickFondo);
    joystickFondo->setOpacity(128);

    CCSprite* joystickBoton = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.85 - 60,  40, 40, 40);
    this->addChild(joystickBoton);

    joystickFondo = dxco::SpriteUtil::create("circulo.png", visibleSize.width *  0.15, 20, 80, 80);
    this->addChild(joystickFondo);
    joystickFondo->setOpacity(128);

    CCSprite* joystickBotonMovimiento = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.15 + 20,  40, 40, 40);
    this->addChild(joystickBotonMovimiento);

    CCSprite* spriteGuy = dxco::SpriteUtil::create("citizenplayershotgun.png", visibleSize.width / 2,  visibleSize.height / 2, 40, 40);
    this->addChild(spriteGuy);
    
    std::map<int, dxco::Animation*> animations;

    dxco::Player* player = new dxco::Player(spriteGuy, animations);

    model = new dxco::GameModel(this, player);
    dxco::Joystick* joystick = new dxco::JoystickMira(model, joystickBoton, 50);
    this->joystickController.addJoystick(joystick);

    joystick = new dxco::JoystickMovimiento(model, joystickBotonMovimiento, 50);
    this->joystickController.addJoystick(joystick);
    this->bulletDt = 0;
    return true;
}



void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	joystickController.ccTouchesBegan(pTouches, pEvent);
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	joystickController.ccTouchesEnded(pTouches, pEvent);
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	joystickController.ccTouchesMoved(pTouches, pEvent);
}

void HelloWorld::update(float dt) {
	this->bulletDt += dt;

	if (this->bulletDt > BULLET_DT) {
		this->model->player->disparar();
		this->bulletDt = 0;
	}

	this->enemyDt += dt;
	if (this->enemyDt > ENEMY_DT){
		this->model->addEnemy();
		this->enemyDt = 0;
	}

	this->model->update(dt);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
