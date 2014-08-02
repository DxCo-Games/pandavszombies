#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "dxco/SpriteUtil.h"
#include "dxco/Joystick.h"
#include "dxco/Animation.h"
#include "crimson/JoystickMira.h"
#include "crimson/JoystickMovimiento.h"
#include "crimson/GameModel.h"
#include "crimson/Player.h"
#include "dxco/Animation.h"
#include "dxco/Container.h"
#include "dxco/StringUtil.h"
#include "dxco/LabelUtil.h"
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
    float mapWidth = visibleSize.width * 1.5;
    float mapHeight = visibleSize.height * 1.5;
    float mapCornerX = - (mapWidth - visibleSize.width) / 2;
    float mapCornerY = - (mapHeight - visibleSize.height) / 2;

    this->mapa = new dxco::Mapa(mapCornerX, mapCornerY, mapWidth, mapHeight);

    CCSprite* pSprite = dxco::SpriteUtil::create("grass-texture-2.jpg", 0, 0, mapWidth, mapHeight);
    this->mapa->addChild(pSprite, -10);

    this->scheduleUpdate();
    this->setTouchEnabled(true);

    this->damageLayer = CCLayerColor::create(ccc4(100, 10, 10, 180));
    this->damageLayer->setVisible(false);
    this->addChild(this->damageLayer, 4);

    this->clouds = new dxco::Container(mapCornerX, mapCornerY, mapWidth, mapHeight);
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

    dxco::Player* player = this->createPlayer();

    model = new dxco::GameModel(this, player);
    dxco::Joystick* joystick = new dxco::JoystickMira(model, joystickBoton, 65);
    this->joystickController.addJoystick(joystick);

    joystick = new dxco::JoystickMovimiento(model, joystickBotonMovimiento, 65);
    this->joystickController.addJoystick(joystick);

    this->playerHPLabel = dxco::LabelUtil::create("HP: " +  dxco::StringUtil::toString(player->life),
			18, 10, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::LEFT);

    this->addChild(playerHPLabel);

    return true;
}

dxco::Player* HelloWorld::createPlayer() {

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite* spriteGuy = dxco::SpriteUtil::create("panda/herida1_1_0000.png", this->mapa->getWidth() / 2,  this->mapa->getHeight() / 2, 70, 70);
    this->mapa->addChild(spriteGuy, 2);

    std::map<int, dxco::Animation*> animations;

    float frameTime = 0.02;
    float hurtFrameTime = 0.04;
    int angles = 8;

    for (int i = 0; i < angles; i++) {
    	std::vector<cocos2d::CCTexture2D*> texturesStanding;
    	texturesStanding.push_back(dxco::SpriteUtil::createTexture("panda/herida1_" + dxco::StringUtil::toString(i + 1)  + "_0000.png"));
    	dxco::Animation* standingAnimation = new dxco::Animation(texturesStanding, frameTime);
    	animations[dxco::Player::QUIETO * angles + i] = standingAnimation;

    	std::vector<cocos2d::CCTexture2D*> texturesWalking;
    	for (int j = 0; j < 20; j++){
    		std::string index = "00" + dxco::StringUtil::toString(j);
    		if (j < 10){
    			index = "0" + index;
    		}
    		texturesWalking.push_back(dxco::SpriteUtil::createTexture("panda/caminata_" + dxco::StringUtil::toString(i + 1)  +
    				"_" + index + ".png"));
    	}
    	dxco::Animation* walkingAnimation = new dxco::Animation(texturesWalking, frameTime);
    	animations[dxco::Player::CAMINANDO * angles + i] = walkingAnimation;

    	std::vector<cocos2d::CCTexture2D*> texturesHerida1;
    	for (int j = 0; j < 10; j++){
    		texturesHerida1.push_back(dxco::SpriteUtil::createTexture("panda/herida1_" + dxco::StringUtil::toString(i + 1)  +
					"_000" + dxco::StringUtil::toString(j) +".png"));
		}
    	//duplicate first frame
    	texturesHerida1.push_back(dxco::SpriteUtil::createTexture("panda/herida1_" + dxco::StringUtil::toString(i + 1)  +
    						"_0000.png"));
    	dxco::Animation* herida1Animation = new dxco::Animation(texturesHerida1, hurtFrameTime);
		animations[dxco::Player::HERIDO1 * angles + i] = herida1Animation;

    	std::vector<cocos2d::CCTexture2D*> texturesHerida2;
    	for (int j = 0; j < 10; j++){
			texturesHerida2.push_back(dxco::SpriteUtil::createTexture("panda/herida2_" + dxco::StringUtil::toString(i + 1)  +
					"_000" + dxco::StringUtil::toString(j) +".png"));
		}
    	//duplicate first frame
    	texturesHerida2.push_back(dxco::SpriteUtil::createTexture("panda/herida2_" + dxco::StringUtil::toString(i + 1)  +
    						"_0000.png"));
		dxco::Animation* herida2Animation = new dxco::Animation(texturesHerida2, hurtFrameTime);
		animations[dxco::Player::HERIDO2 * angles + i] = herida2Animation;
    }

    dxco::Player* player = new dxco::Player(spriteGuy, animations);

    //start looking up
    player->setRotation(-90);
	this->fire->setAngle(-90);

    return player;
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

	updatePlayerLifeLabel();
}

void HelloWorld::updatePlayerLifeLabel() {
	std::string playerLife = "HP: " + dxco::StringUtil::toString((float)round(this->model->player->life));

	this->playerHPLabel->setString(playerLife.c_str());
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
