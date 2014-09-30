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
#include "crimson/levels/Level.h"

#include "crimson/daos/UserDAO.h"

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
    this->loading = dxco::SpriteUtil::create("loading.png", 0, 0, visibleSize.width, visibleSize.height);
    this->addChild(loading);
    this->porcentajeCargado = dxco::LabelUtil::create("0%", 32, visibleSize.width / 2, visibleSize.height / 2,
    																			dxco::LabelUtil::TOP, dxco::LabelUtil::LEFT);
    this->addChild(porcentajeCargado);

    this->preloaded = false;
    this->angulosCargados = 0;
    this->scheduleUpdate();

    return true;
}

void HelloWorld::realInit() {
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	    float mapWidth = MAP_WIDTH; //visibleSize.width * 1.2;
	    float mapHeight = MAP_HEIGHT; //visibleSize.height * 1.4;
	    float mapCornerX = - (mapWidth - visibleSize.width) / 2;
	    float mapCornerY = - (mapHeight - visibleSize.height) / 2;

	    this->mapa = new dxco::Mapa(mapCornerX, mapCornerY, mapWidth, mapHeight);
	    this->clouds = new dxco::Container(mapCornerX, mapCornerY, mapWidth, mapHeight);
	    this->addChild(this->clouds, 4);

	    if(false) { //TODO select background
			CCSprite* pSprite = dxco::SpriteUtil::create("ciudad_fondo.png", -mapWidth/4, -mapHeight * 0.2, mapWidth*1.5, mapHeight*1.4);
			this->mapa->addChild(pSprite, -10);
			CCSprite* tanque = dxco::SpriteUtil::create("ciudad_tanque.png", -mapWidth/4, -mapHeight  * 0.2, mapWidth*1.5, mapHeight*1.4);
			this->clouds->addChild(tanque);
			CCSprite* rejas = dxco::SpriteUtil::create("ciudad_rejas.png", -mapWidth/4, -mapHeight  * 0.2, mapWidth*1.5, mapHeight*1.4);
			this->clouds->addChild(rejas);
	    } else {
			CCSprite* pSprite = dxco::SpriteUtil::create("campo004_fondo.jpg", -mapWidth/4, -mapHeight * 0.2, mapWidth*1.5, mapHeight*1.4);
			this->mapa->addChild(pSprite, -10);
			CCSprite* tanque = dxco::SpriteUtil::create("campo004_rejas.png", -mapWidth/4, -mapHeight  * 0.2, mapWidth*1.5, mapHeight*1.4);
			this->clouds->addChild(tanque);
	    }

		this->bubble = dxco::SpriteUtil::create("bubble.png", 0, 0, 93, 93);
		this->bubble->setVisible(false);
		this->bubble->setOpacity(128);
		this->clouds->addChild(this->bubble);

	    this->setTouchEnabled(true);

	    this->initFire(visibleSize.width / 2,  visibleSize.height / 2);

	    this->addChild(mapa);

	    dxco::Player* player = this->createPlayer();

	    model = new dxco::GameModel(this, player, true); //true=survival, false=story

	    this->createInterface();
}

void HelloWorld::preloadTextures() {
	if (!this->preloaded) {
		dxco::SpriteUtil::preloadTextureWithFile("sprite_sheets/zombies.plist");
		this->preloaded = true;
		this->realInit();
	}

}

dxco::Player* HelloWorld::createPlayer() {

	dxco::SpriteUtil::preloadTextureWithFile("sprite_sheets/panda.plist");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	this->playerContainer = new dxco::Container(this->mapa->getWidth() / 2,  this->mapa->getHeight() / 2, 80, 80);
    CCSprite* spriteGuy = dxco::SpriteUtil::create("herida1_1_0000.png", 0.45 * this->mapa->getWidth(),  0.45 * this->mapa->getHeight(), 80, 80, true);

    //this->playerContainer->addChild(spriteGuy);
    this->mapa->addChild(spriteGuy, 2);

    std::map<int, dxco::Animation*> animations;

    float frameTime = 0.03;
    int angles = 16;

    for (int i = 0; i < angles; i++) {
    	std::vector<cocos2d::CCSpriteFrame*> texturesStanding;
    	texturesStanding.push_back(dxco::SpriteUtil::createSpriteFrame("herida1_" + dxco::StringUtil::toString(i + 1)  + "_0000.png"));
    	dxco::Animation* standingAnimation = new dxco::Animation(texturesStanding, frameTime);
    	animations[dxco::Player::QUIETO * angles + i] = standingAnimation;

    	std::vector<cocos2d::CCSpriteFrame*> texturesWalking;
    	for (int j = 0; j <= 13; j++) {
    		std::string index = "00" + dxco::StringUtil::toString(j);
    		if (j < 10){
    			index = "0" + index;
    		}
    		texturesWalking.push_back(dxco::SpriteUtil::createSpriteFrame("caminata_" + dxco::StringUtil::toString(i + 1)  +
    				"_" + index + ".png"));
    	}
    	dxco::Animation* walkingAnimation = new dxco::Animation(texturesWalking, frameTime);
    	animations[dxco::Player::CAMINANDO * angles + i] = walkingAnimation;

    	std::vector<cocos2d::CCSpriteFrame*> texturesHerida;
    	for (int j = 0; j < 10; j++){
    		texturesHerida.push_back(dxco::SpriteUtil::createSpriteFrame("herida1_" + dxco::StringUtil::toString(i + 1)  +
					"_000" + dxco::StringUtil::toString(j) +".png"));
		}
    	//mix both sequences as one animation
    	for (int j = 0; j <= 9; j++){
			texturesHerida.push_back(dxco::SpriteUtil::createSpriteFrame("herida2_" + dxco::StringUtil::toString(i + 1)  +
					"_000" + dxco::StringUtil::toString(j) +".png"));
		}
    	dxco::Animation* heridaAnimation = new dxco::Animation(texturesHerida, frameTime);
		animations[dxco::Player::HERIDO * angles + i] = heridaAnimation;
    }

    dxco::Player* player = new dxco::Player(spriteGuy, animations);

    //start looking up
    player->setRotation(-90);
	this->fire->setAngle(-90);

    return player;
}

void HelloWorld::createInterface() {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//joysticks
	CCSprite* joystickFondo2 = dxco::SpriteUtil::create("gameplay/JOYSTICK_arma.png", visibleSize.width *  0.92 - 80, 20, 100, 100);
	this->addChild(joystickFondo2, 10);
	joystickFondo2->setOpacity(128);

	CCSprite* joystickBoton = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.92 - 60,  40, 40, 40);
	joystickBoton->setVisible(false);
	this->addChild(joystickBoton, 12);

	CCSprite* joystickFondo = dxco::SpriteUtil::create("gameplay/JOYSTICK_panda.png", visibleSize.width *  0.05, 20, 100, 100);
	this->addChild(joystickFondo, 12);
	joystickFondo->setOpacity(128);

	CCSprite* joystickBotonMovimiento = dxco::SpriteUtil::create("boton.png", visibleSize.width * 0.05 + 20,  40, 40, 40);
	joystickBotonMovimiento->setVisible(false);
	this->addChild(joystickBotonMovimiento, 12);

	dxco::Joystick* joystick = new dxco::JoystickMira(model, joystickBoton, 65);
	this->joystickController.addJoystick(joystick);

	joystick = new dxco::JoystickMovimiento(model, joystickBotonMovimiento, 65);
	this->joystickController.addJoystick(joystick);

	//Life bar
	CCSprite* lifeBack = dxco::SpriteUtil::create("gameplay/PANDA_energia_fin.png", 5, 0.87 * visibleSize.height, 0.35 * visibleSize.width , 0.11 * visibleSize.height);
	CCSprite* lifeFront = dxco::SpriteUtil::create("gameplay/PANDA_energia.png", 5, 0.87 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	lifeBar = CCProgressTimer::create(lifeFront);
	lifeBar->setPosition(lifeBack->getPosition()); //positions don't match by default
	lifeBar->setScaleX(lifeBack->getScaleX());
	lifeBar->setScaleY(lifeBack->getScaleY());
	lifeBar->setType(kCCProgressTimerTypeBar);
	lifeBar->setMidpoint(ccp(0.16,0)); // the x coord tells the bar to put the 0% after the panda head
	lifeBar->setBarChangeRate(ccp(1,0));
	lifeBar->setPercentage(100);
	this->addChild(lifeBack, 10);
	this->addChild(lifeBar, 11);

	//weapon bar
	CCSprite* weaponBack = dxco::SpriteUtil::create("gameplay/BALAS_barra_fin.png", 5, 0.78 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	weaponBack->setScaleX(lifeBack->getScaleX());
	weaponBack->setScaleY(lifeBack->getScaleY());
	dxco::SpriteUtil::leftAlign(lifeBack, weaponBack);
	CCSprite* weaponFront = dxco::SpriteUtil::create("gameplay/BALAS_barra.png", 5, 0.78 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	weaponBar = CCProgressTimer::create(weaponFront);
	weaponBar->setPosition(weaponBack->getPosition()); //positions don't match by default
	weaponBar->setScaleX(weaponBack->getScaleX());
	weaponBar->setScaleY(weaponBack->getScaleY());
	weaponBar->setType(kCCProgressTimerTypeBar);
	weaponBar->setMidpoint(ccp(0.25,0)); // the x coord tells the bar to put the 0% after the panda head
	weaponBar->setBarChangeRate(ccp(1,0));
	weaponBar->setPercentage(100);
	weaponIcon = dxco::SpriteUtil::create("bonus/PISTOLA.png", 5, 0.78 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	weaponIcon->setScaleX(lifeBack->getScaleX());
	weaponIcon->setScaleY(lifeBack->getScaleY());
	weaponIcon->setPositionY(weaponBack->getPositionY());
	dxco::SpriteUtil::leftAlign(lifeBack, weaponIcon);
	this->addChild(weaponBack, 10);
	this->addChild(weaponBar, 11);
	this->addChild(weaponIcon, 11);

	//bonus icons
	bonus1 = dxco::SpriteUtil::create("bonus/BALAV_activada.png", 5, 0.78 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	bonus1->setScaleX(lifeBack->getScaleX());
	bonus1->setScaleY(lifeBack->getScaleY());
	this->addChild(bonus1, 11);
	bonus1->setOpacity(0);
	bonus2 = dxco::SpriteUtil::create("bonus/BALAV_activada.png", 5, 0.78 * visibleSize.height, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	bonus2->setScaleX(lifeBack->getScaleX());
	bonus2->setScaleY(lifeBack->getScaleY());
	this->addChild(bonus2, 11);
	bonus2->setOpacity(0);
	//spread the bonus icons between the life and weapon bars
	float x0 = weaponBack->getPositionX() + dxco::SpriteUtil::getWidth(weaponBack) / 2;
	float xf = lifeBack->getPositionX() + dxco::SpriteUtil::getWidth(lifeBack) / 2;
	float iconWidth = dxco::SpriteUtil::getWidth(bonus1);
	float padding = (xf - x0 - 2 * iconWidth) / 3;
	bonus1->setPositionX(x0 + padding + iconWidth / 2);
	bonus2->setPositionX(xf - padding - iconWidth / 2);

	//score
	CCSprite* score = dxco::SpriteUtil::create("gameplay/SCORE.png", visibleSize.width / 2, 0, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	score->setScaleX(lifeBack->getScaleX());
	score->setScaleY(lifeBack->getScaleY());
	score->setPositionY(lifeBack->getPositionY());
	//set the right margin equal to the left one
	float sideMargin = lifeBack->getPositionX() - dxco::SpriteUtil::getWidth(lifeBack);
	score->setPositionX(visibleSize.width - sideMargin - dxco::SpriteUtil::getWidth(score));
	this->addChild(score, 10);

	//timer
	CCSprite* timer = dxco::SpriteUtil::create("gameplay/TIMER.png", visibleSize.width / 2, 0, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	timer->setScaleX(lifeBack->getScaleX());
	timer->setScaleY(lifeBack->getScaleY());
	timer->setPositionY(lifeBack->getPositionY());
	//put timer in between score and life
	x0 = lifeBack->getPositionX() + dxco::SpriteUtil::getWidth(lifeBack) / 2;
	xf = score->getPositionX() - dxco::SpriteUtil::getWidth(score) / 2;
	timer->setPositionX(x0 + (xf - x0) / 2);
	this->addChild(timer, 10);

	//zombie bar
	CCSprite* zombie = dxco::SpriteUtil::create("gameplay/ZOMBIE_contador.png", 0, 0, dxco::SpriteUtil::UNDEFINED, dxco::SpriteUtil::UNDEFINED);
	zombie->setScaleX(lifeBack->getScaleX());
	zombie->setScaleY(lifeBack->getScaleY());
	zombie->setPositionY(weaponBack->getPositionY());
	dxco::SpriteUtil::rightAlign(score, zombie);
	this->addChild(zombie, 10);

	this->timerLabel = dxco::LabelUtil::create("00:00", 14, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::LEFT, "fonts/KBStickToThePlan.ttf");
	this->timerLabel->setPositionX(timer->getPositionX() - 0.35 * dxco::SpriteUtil::getWidth(timer));
	this->timerLabel->setPositionY(timer->getPositionY() + 0.22 * dxco::SpriteUtil::getHeight(timer));
	this->addChild(timerLabel, 10);
	this->playerScoreLabel = dxco::LabelUtil::create("0", 14, 10, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	this->playerScoreLabel->setPositionX(score->getPositionX() + 0.32 * dxco::SpriteUtil::getWidth(score));
	this->playerScoreLabel->setPositionY(this->timerLabel->getPositionY());
	this->addChild(playerScoreLabel, 10);

	this->killsLabel = dxco::LabelUtil::create("0", 14, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	this->killsLabel->setPositionX(zombie->getPositionX() + 0.20 * dxco::SpriteUtil::getWidth(zombie));
	this->killsLabel->setPositionY(zombie->getPositionY() + 0.22 * dxco::SpriteUtil::getHeight(zombie));
	this->addChild(killsLabel, 10);

	this->killsChainLabel = dxco::LabelUtil::create("0 kills", 16, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	dxco::LabelUtil::setColor(this->killsChainLabel, dxco::LabelUtil::RED);
	this->killsChainLabel->setPositionX(this->killsLabel->getPositionX());
	this->killsChainLabel->setPositionY(visibleSize.height * 0.79);
	this->addChild(killsChainLabel, 10);
	this->killsChainLabel->setOpacity(0);
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {

	cocos2d::CCSetIterator it = pTouches->begin();
	cocos2d::CCPoint location;
	cocos2d::CCTouch * touch;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	for (int iTouchCount = 0; iTouchCount < pTouches->count(); iTouchCount++) {
		touch = (cocos2d::CCTouch*) (*it);
		location = touch->getLocationInView();
		location = cocos2d::CCDirector::sharedDirector()->convertToGL(location);

		if (location.x > visibleSize.width / 2) {

		} else {

		}
	}
	joystickController.ccTouchesBegan(pTouches, pEvent);
}

void HelloWorld::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	joystickController.ccTouchesEnded(pTouches, pEvent);
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
	joystickController.ccTouchesMoved(pTouches, pEvent);
}

void HelloWorld::update(float dt) {

	if (this->preloaded) {
		this->removeChild(porcentajeCargado);
		this->removeChild(loading);

		this->model->update(dt);

		updateLabels();
	} else {
		this->preloadTextures();
		float angulosCargados = this->angulosCargados;
		float cantAngulos = ENEMY_ANGLE_POSITIONS;

		std::string porcentaje = dxco::StringUtil::toString((angulosCargados / cantAngulos) * 100);
		porcentaje += "%";
		porcentajeCargado->setString(porcentaje.c_str());
	}
}

void HelloWorld::updateLabels() {
	int totalTime = this->model->timer;
	int minutes = ceil(totalTime / 60);
	int seconds = totalTime % 60;

	std::string stringMinutes =  dxco::StringUtil::padLeft(minutes, 2);
	std::string stringSeconds = dxco::StringUtil::padLeft(seconds, 2);
	std::string timerText = stringMinutes + ":" + stringSeconds;
	this->timerLabel->setString(timerText.c_str());

	std::string playerScoreText = dxco::StringUtil::toString(this->model->player->score);
	this->playerScoreLabel->setString(playerScoreText.c_str());

	std::string playerKillsText = dxco::StringUtil::toString(this->model->kills);
	this->killsLabel->setString(playerKillsText.c_str());

	this->lifeBar->setPercentage(this->model->player->life * 100 / PLAYER_LIFE);
}

void HelloWorld::updateBonus(std::string texture, float duration) {
	//decide which one is first
	CCSprite *b1, *b2;
	if (this->bonus1->getPositionX() < this->bonus2->getPositionX()) {
		b1 = this->bonus1;
		b2 = this->bonus2;
	} else {
		b1 = this->bonus2;
		b2 = this->bonus1;
	}

	//swap icons
	CCPoint p1 = b1->getPosition();
	b1->setPosition(b2->getPosition());
	b2->setPosition(p1);

	//set texture and begin fade
	dxco::SpriteUtil::setTexture(b2, texture);
	b2->setOpacity(255);
	dxco::SpriteUtil::fadeOut(b2, duration);
}

void HelloWorld::initFire(float x, float y) {
	this->fire = cocos2d::CCParticleSystemQuad::create("fire.plist");

	/* The position is relative to the map, so emmited particles move with the map
	 * and not the emmiter. */
	fire->setPositionType(cocos2d::kCCPositionTypeRelative);
	fire->setPosition(x, y);
	this->mapa->addChild(fire, 2);
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
