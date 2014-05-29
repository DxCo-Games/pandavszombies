#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "dxco/SpriteUtil.h"
#include "dxco/Joystick.h"
#include "crimson/JoystickMira.h"
#include "crimson/JoystickMovimiento.h"
#include "crimson/GameModel.h"
#include "crimson/Player.h"
#include "dxco/Animation.h"
#include "dxco/Container.h"
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
    
    this->mapa = new dxco::Mapa(0, 0, visibleSize.width * 2, visibleSize.height * 2);

    CCSprite* pSprite = dxco::SpriteUtil::create("grass-texture-2.jpg", 0, 0, visibleSize.width * 2, visibleSize.height * 2);
    this->mapa->addChild(pSprite, -10);

    this->scheduleUpdate();
    this->setTouchEnabled(true);

    this->damageLayer = CCLayerColor::create(ccc4(100, 10, 10, 180));
    this->damageLayer->setVisible(false);
    this->addChild(this->damageLayer, 4);

    this->clouds = new dxco::Container(0, 0, visibleSize.width * 2, visibleSize.height * 2);
    this->addChild(this->clouds, 4);

    CCSprite* joystickFondo = dxco::SpriteUtil::create("circulo.png", visibleSize.width *  0.85 - 80, 20, 80, 80);
    this->addChild(joystickFondo, 10);
    joystickFondo->setOpacity(128);

    CCSprite* joystickBoton = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.85 - 60,  40, 40, 40);
    this->addChild(joystickBoton, 12);

    joystickFondo = dxco::SpriteUtil::create("circulo.png", visibleSize.width *  0.15, 20, 80, 80);
    this->addChild(joystickFondo, 12);
    joystickFondo->setOpacity(128);

    CCSprite* joystickBotonMovimiento = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.15 + 20,  40, 40, 40);
    this->addChild(joystickBotonMovimiento, 12);

    this->initFire(visibleSize.width / 2,  visibleSize.height / 2);

    this->addChild(mapa);
    CCSprite* spriteGuy = dxco::SpriteUtil::create("citizenplayer_handgun.png", visibleSize.width / 2,  visibleSize.height / 2, 40, 40);
    this->addChild(spriteGuy, 2);
    
    std::map<int, dxco::Animation*> animations;

    dxco::Player* player = new dxco::Player(spriteGuy, animations);

    model = new dxco::GameModel(this, player);
    dxco::Joystick* joystick = new dxco::JoystickMira(model, joystickBoton, 65);
    this->joystickController.addJoystick(joystick);

    joystick = new dxco::JoystickMovimiento(model, joystickBotonMovimiento, 65);
    this->joystickController.addJoystick(joystick);

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
	this->model->update(dt);
	this->damageLayer->setVisible(this->model->damage);
}

void HelloWorld::initFire(float x, float y) {
	this->fire = cocos2d::CCParticleSystemQuad::create("fire.plist");

	/* The position is relative to the map, so emmited particles move with the map
	 * and not the emmiter. */
	fire->setPositionType(cocos2d::kCCPositionTypeRelative);
	fire->setPosition(x, y);
	this->clouds->addChild(fire);
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
