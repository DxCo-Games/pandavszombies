#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"

#include "dxco/SpriteUtil.h"
#include "dxco/Joystick.h"
#include "dxco/Animation.h"
#include "crimson/JoystickMira.h"
#include "crimson/JoystickMovimiento.h"
#include "crimson/GameModel.h"
#include "crimson/GameProperties.h"
#include "crimson/Player.h"
#include "dxco/Animation.h"
#include "crimson/SoundUtil.h"
#include "dxco/Container.h"
#include "dxco/StringUtil.h"
#include "dxco/LabelUtil.h"
#include "crimson/levels/Level.h"
#include "crimson/daos/UserDAO.h"
#include "crimson/layers/GameTypeSelectionLayer.h"
#include "dxco/RevMob.h"
#include <map>

USING_NS_CC;


CCScene* HelloWorld::scene(bool survivalMode, bool frenzyMode, int level)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    HelloWorld* layer = HelloWorld::create();
    layer->survivalMode = survivalMode;
    layer->frenzyMode = frenzyMode;
    layer->level = level;

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

    this->assetLoader = new dxco::AssetLoader();

	this->assetLoader->addAsset("sprite_sheets/basquet.plist");
	this->assetLoader->addAsset("sprite_sheets/campesino.plist");
	this->assetLoader->addAsset("sprite_sheets/cirujano.plist");
	this->assetLoader->addAsset("sprite_sheets/cura.plist");
	this->assetLoader->addAsset("sprite_sheets/elvis.plist");
	this->assetLoader->addAsset("sprite_sheets/oficinista.plist");
	this->assetLoader->addAsset("sprite_sheets/sangre.plist");
	this->assetLoader->addAsset("sprite_sheets/panda1.plist");
	this->assetLoader->addAsset("sprite_sheets/panda2.plist");
	this->assetLoader->addAsset("sprite_sheets/panda3.plist");

	// dont add any music, only sound effects
	this->assetLoader->addAsset("sounds/bazooka.ogg", true);
	this->assetLoader->addAsset("sounds/bomb.ogg", true);
	this->assetLoader->addAsset("sounds/bonus.ogg", true);
	this->assetLoader->addAsset("sounds/cannon.ogg", true);
	this->assetLoader->addAsset("sounds/flame2.ogg", true);
	this->assetLoader->addAsset("sounds/gun1.ogg", true);
	this->assetLoader->addAsset("sounds/loadgun.ogg", true);
	this->assetLoader->addAsset("sounds/shotgun2.ogg", true);
	this->assetLoader->addAsset("sounds/toasty.ogg", true);

	this->assetLoader->addAsset("voices/cake.ogg", true);
	this->assetLoader->addAsset("voices/dead.ogg", true);
	this->assetLoader->addAsset("voices/friend.ogg", true);
	this->assetLoader->addAsset("voices/groovy.ogg", true);
	this->assetLoader->addAsset("voices/king.ogg", true);
	this->assetLoader->addAsset("voices/rock.ogg", true);
	this->assetLoader->addAsset("voices/talkin.ogg", true);

	revmob::RevMob::SharedInstance()->LoadFullscreen();

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

    this->backgroundLoading = dxco::SpriteUtil::create("fondo_ciudad.jpg", 0, 0, visibleSize.width, visibleSize.height);
    this->addChild(backgroundLoading);

    CCSprite* loadingSprite = dxco::SpriteUtil::create("LOADING-1.png", visibleSize.width * 0.25, visibleSize.height / 2 - visibleSize.width * 0.075, visibleSize.width * 0.5, visibleSize.width * 0.15);
    this->addChild(loadingSprite);

    std::vector<cocos2d::CCTexture2D*> texturesLoading;

    texturesLoading.push_back(dxco::SpriteUtil::createTexture("LOADING-1.png"));
    texturesLoading.push_back(dxco::SpriteUtil::createTexture("LOADING-2.png"));
    texturesLoading.push_back(dxco::SpriteUtil::createTexture("LOADING-3.png"));

    dxco::Animation* animationLoading = new dxco::Animation(texturesLoading, 0.25);

    std::map<int, dxco::Animation*> animationLoadingMap;
    animationLoadingMap[0] = animationLoading;
    this->loadingItem = new dxco::Item(loadingSprite, animationLoadingMap);
    spriteSheetCargada = 0;

    this->preloaded = false;
    this->scheduleUpdate();

    this->juegoPausado = false;
    this->setKeypadEnabled(true);

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

		this->bubble = dxco::SpriteUtil::create("bubble.png", 0, 0, 93, 93);
		this->bubble->setVisible(false);
		this->bubble->setOpacity(128);
		this->clouds->addChild(this->bubble);

	    this->setTouchEnabled(true);

	    this->initFire(visibleSize.width / 2,  visibleSize.height / 2);

	    this->addChild(mapa);

	    dxco::Player* player = this->createPlayer();

	    model = new dxco::GameModel(this, player);
	    this->levelFinishedLayer = new dxco::LevelFinishedLayer(this->model, 0, 0, visibleSize.width, visibleSize.height, this->survivalMode || this->frenzyMode, this->level);
	    this->addChild(levelFinishedLayer, 50);

	    this->createInterface();
	    this->pauseLayer = new dxco::PauseLayer(this->model, 0, 0, visibleSize.width, visibleSize.height, this->weaponIcon);
	    this->addChild(pauseLayer, 50);

	    model->loadLevel(this->survivalMode, this->frenzyMode, this->level);
	    this->setLevelTitle();
}

void HelloWorld::preloadTextures() {
	this->assetLoader->loadNext();
}

void HelloWorld::setMap(int map) {
	if(map == 0) {
		CCSprite* pSprite = dxco::SpriteUtil::create("ciudad_fondo.png", -MAP_WIDTH/4, -MAP_HEIGHT * 0.2, MAP_WIDTH*1.5, MAP_HEIGHT*1.4);
		this->mapa->addChild(pSprite, -10);
		CCSprite* tanque = dxco::SpriteUtil::create("ciudad_tanque.png", -MAP_WIDTH/4, -MAP_HEIGHT  * 0.2, MAP_WIDTH*1.5, MAP_HEIGHT*1.4);
		this->clouds->addChild(tanque);
		CCSprite* rejas = dxco::SpriteUtil::create("ciudad_rejas.png", -MAP_WIDTH/4, -MAP_HEIGHT  * 0.2, MAP_WIDTH*1.5, MAP_HEIGHT*1.4);
		this->clouds->addChild(rejas);
	} else {
		CCSprite* pSprite = dxco::SpriteUtil::create("campo004_fondo.jpg", -MAP_WIDTH/4, -MAP_HEIGHT * 0.2, MAP_WIDTH*1.5, MAP_HEIGHT*1.4);
		this->mapa->addChild(pSprite, -10);
		CCSprite* tanque = dxco::SpriteUtil::create("campo004_rejas.png", -MAP_WIDTH/4, -MAP_HEIGHT  * 0.2, MAP_WIDTH*1.5, MAP_HEIGHT*1.4);
		this->clouds->addChild(tanque);
	}
}

dxco::Player* HelloWorld::createPlayer() {

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	this->playerContainer = new dxco::Container(this->mapa->getWidth() / 2,  this->mapa->getHeight() / 2, 80, 80);
    CCSprite* spriteGuy = dxco::SpriteUtil::create("herida1_5_0000.png", 0.45 * this->mapa->getWidth(),  0.4 * this->mapa->getHeight(), 75, 75, true);

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
    	std::vector<cocos2d::CCSpriteFrame*> texturesWalkingInverted;

    	for (int j = 0; j <= 13; j++) {
    		std::string index = "00" + dxco::StringUtil::toString(j);

    		if (j < 10) {
    			index = "0" + index;
    		}

    		texturesWalking.push_back(dxco::SpriteUtil::createSpriteFrame("caminata_" + dxco::StringUtil::toString(i + 1)  +
    				"_" + index + ".png"));
    	}

    	dxco::Animation* walkingAnimation = new dxco::Animation(texturesWalking, frameTime);
    	animations[dxco::Player::CAMINANDO * angles + i] = walkingAnimation;

    	for (int j = 13; j >= 0; j--) {
    		std::string index = "00" + dxco::StringUtil::toString(j);

    		if (j < 10) {
    			index = "0" + index;
    		}

    		texturesWalkingInverted.push_back(dxco::SpriteUtil::createSpriteFrame("caminata_" + dxco::StringUtil::toString(i + 1)  +
    				"_" + index + ".png"));
    	}

    	dxco::Animation* walkingAnimationInverted = new dxco::Animation(texturesWalkingInverted, frameTime);
    	animations[dxco::Player::CAMINANDO_INVERTIDO * angles + i] = walkingAnimationInverted;

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

	this->controlsLayer = cocos2d::CCLayer::create();
	this->addChild(controlsLayer, 10);

	//joysticks
	CCSprite* joystickFondo2 = dxco::SpriteUtil::create("gameplay/JOYSTICK_base_blanco.png", visibleSize.width *  0.92 - 90, 25, 80, 80);
	this->controlsLayer->addChild(joystickFondo2, 10);
	joystickFondo2->setOpacity(128);

	CCSprite* joystickBoton = dxco::SpriteUtil::create("gameplay/JOYSTICK_derecho.png", visibleSize.width * 0.92 - 90,  25, 80, 80);
	this->controlsLayer->addChild(joystickBoton, 12);

	CCSprite* joystickFondo = dxco::SpriteUtil::create("gameplay/JOYSTICK_base_blanco.png", visibleSize.width *  0.05 + 10, 25, 80, 80);
	this->controlsLayer->addChild(joystickFondo, 12);
	joystickFondo->setOpacity(128);

	CCSprite* joystickBotonMovimiento = dxco::SpriteUtil::create("gameplay/JOYSTICK_izquierdo.png", visibleSize.width * 0.05 + 10, 25, 80, 80);
	this->controlsLayer->addChild(joystickBotonMovimiento, 12);

	dxco::Joystick* joystick = new dxco::JoystickMira(model, joystickBoton, 40);
	this->joystickController.addJoystick(joystick);

	joystick = new dxco::JoystickMovimiento(model, joystickBotonMovimiento, 40);
	this->joystickController.addJoystick(joystick);

	//Life bar
	CCSprite* lifeBack = dxco::SpriteUtil::create("gameplay/PANDA_energia_fin.png", 5, 0.87 * visibleSize.height, 0.35 * visibleSize.width , 0.102 * visibleSize.height);
	CCSprite* lifeFront = dxco::SpriteUtil::create("gameplay/PANDA_energia.png", 5, 0.87 * visibleSize.height, lifeBack);
	lifeBar = CCProgressTimer::create(lifeFront);
	lifeBar->setScaleX(lifeBack->getScaleX());
	lifeBar->setScaleY(lifeBack->getScaleY());
	lifeBar->setPosition(lifeBack->getPosition()); //positions don't match by default
	lifeBar->setType(kCCProgressTimerTypeBar);
	lifeBar->setMidpoint(ccp(0.16,0)); // the x coord tells the bar to put the 0% after the panda head
	lifeBar->setBarChangeRate(ccp(1,0));
	lifeBar->setPercentage(100);
	this->controlsLayer->addChild(lifeBack, 10);
	this->controlsLayer->addChild(lifeBar, 11);

	//weapon bar
	CCSprite* weaponBack = dxco::SpriteUtil::create("gameplay/BALAS_barra_fin.png", 5, 0.78 * visibleSize.height, lifeBack);
	dxco::SpriteUtil::leftAlign(lifeBack, weaponBack);

	CCSprite* weaponFront = dxco::SpriteUtil::create("gameplay/BALAS_barra.png", 5, 0.78 * visibleSize.height, lifeBack);
	weaponBar = CCProgressTimer::create(weaponFront);
	weaponBar->setScaleX(lifeBack->getScaleX());
	weaponBar->setScaleY(lifeBack->getScaleY());
	weaponBar->setPosition(weaponBack->getPosition()); //positions don't match by default
	weaponBar->setType(kCCProgressTimerTypeBar);
	weaponBar->setMidpoint(ccp(0.25,0)); // the x coord tells the bar to put the 0% after the panda head
	weaponBar->setBarChangeRate(ccp(1,0));
	weaponBar->setPercentage(100);
	weaponIcon = dxco::SpriteUtil::create("bonus/PISTOLA.png", 5, 0.78 * visibleSize.height, lifeBack);
	weaponIcon->setPositionY(weaponBack->getPositionY());
	dxco::SpriteUtil::leftAlign(lifeBack, weaponIcon);
	this->controlsLayer->addChild(weaponBack, 10);
	this->controlsLayer->addChild(weaponBar, 11);
	this->controlsLayer->addChild(weaponIcon, 11);

	//bonus icons
	bonus1 = dxco::SpriteUtil::create("bonus/BALAV_activada.png", 5, 0.78 * visibleSize.height, lifeBack);
	this->addChild(bonus1, 11);
	bonus1->setOpacity(0);
	bonus2 = dxco::SpriteUtil::create("bonus/BALAV_activada.png", 5, 0.78 * visibleSize.height, lifeBack);
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
	CCSprite* score = dxco::SpriteUtil::create("gameplay/SCORE.png", visibleSize.width / 2, 0, lifeBack);
	score->setPositionY(lifeBack->getPositionY());
	//set the right margin equal to the left one
	float sideMargin = lifeBack->getPositionX() - dxco::SpriteUtil::getWidth(lifeBack);
	score->setPositionX(visibleSize.width - sideMargin - dxco::SpriteUtil::getWidth(score));
	this->controlsLayer->addChild(score, 10);

	//timer
	this->timer;
	if (this->survivalMode || this->frenzyMode) {
		this->timer = dxco::SpriteUtil::create("gameplay/TIMER.png", visibleSize.width / 2, 0, lifeBack);
		this->timerLabel = dxco::LabelUtil::create("00:00", 14, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::LEFT, "fonts/KBStickToThePlan.ttf");
	} else {
		this->timer = dxco::SpriteUtil::create("gameplay/LEVEL.png", visibleSize.width / 2, 0, lifeBack);

		std::string levelText = "LEVEL " + dxco::StringUtil::toString(this->level);

		if (this->level < 10) {
			levelText = " " + levelText;
		}

		this->timerLabel = dxco::LabelUtil::create(levelText, 13, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::LEFT, "fonts/KBStickToThePlan.ttf");
	}
	this->timer->setPositionY(lifeBack->getPositionY());
	//put timer in between score and life
	x0 = lifeBack->getPositionX() + dxco::SpriteUtil::getWidth(lifeBack) / 2;
	xf = score->getPositionX() - dxco::SpriteUtil::getWidth(score) / 2;
	this->timer->setPositionX(x0 + (xf - x0) / 2);
	this->controlsLayer->addChild(this->timer, 10);

	this->timerLabel->setPositionX(this->timer->getPositionX() - 0.35 * dxco::SpriteUtil::getWidth(this->timer));
	this->timerLabel->setPositionY(this->timer->getPositionY() + 0.22 * dxco::SpriteUtil::getHeight(this->timer));
	this->controlsLayer->addChild(timerLabel, 10);

	//zombie bar
	CCSprite* zombie = dxco::SpriteUtil::create("gameplay/ZOMBIE_contador.png", 0, 0, lifeBack);
	zombie->setPositionY(weaponBack->getPositionY());
	dxco::SpriteUtil::rightAlign(score, zombie);
	this->controlsLayer->addChild(zombie, 10);

	this->playerScoreLabel = dxco::LabelUtil::create("0", 14, 10, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	this->playerScoreLabel->setPositionX(score->getPositionX() + 0.32 * dxco::SpriteUtil::getWidth(score));
	this->playerScoreLabel->setPositionY(this->timerLabel->getPositionY());
	this->controlsLayer->addChild(playerScoreLabel, 10);

	this->killsLabel = dxco::LabelUtil::create("0", 10, visibleSize.width / 2, 10, dxco::LabelUtil::TOP, dxco::LabelUtil::RIGHT, "fonts/KBStickToThePlan.ttf");
	this->killsLabel->setPositionX(zombie->getPositionX() + 0.20 * dxco::SpriteUtil::getWidth(zombie));
	this->killsLabel->setPositionY(zombie->getPositionY() + 0.22 * dxco::SpriteUtil::getHeight(zombie));
	this->controlsLayer->addChild(killsLabel, 10);

	this->killsChainLabel = CCLabelTTF::create("0 kills", "fonts/KBStickToThePlan.ttf", 18);
	dxco::LabelUtil::setColor(this->killsChainLabel, dxco::LabelUtil::RED);
	this->killsChainLabel->enableStroke(cocos2d::ccc3(220, 0, 0), 2, true);
	this->killsChainLabel->setPositionX(timer->getPositionX());
	this->killsChainLabel->setPositionY(zombie->getPositionY());
	this->controlsLayer->addChild(killsChainLabel, 10);
	this->killsChainLabel->setOpacity(0);

	if (this->level != -1) {
		std::string levelstring = "LEVEL " + dxco::StringUtil::toString(level);
		this->title1 = CCLabelTTF::create(levelstring.c_str(), "fonts/KBStickToThePlan.ttf", 18);
		this->title1->setPositionX(timer->getPositionX());
		this->title1->setPositionY(zombie->getPositionY());
		this->title1->enableStroke(cocos2d::ccc3(220, 0, 0), 2, true);
		dxco::LabelUtil::setColor(title1, dxco::LabelUtil::RED);
		this->addChild(this->title1);

		this->title2 = CCLabelTTF::create("NONAME", "fonts/KBStickToThePlan.ttf", 22, CCSize(350,0), kCCTextAlignmentCenter);
		this->title2->setPositionX(timer->getPositionX());
		this->title2->setPositionY(zombie->getPositionY() - dxco::SpriteUtil::getHeight(zombie) * 1.5);
		this->title2->enableStroke(cocos2d::ccc3(220, 0, 0), 2, true);
		dxco::LabelUtil::setColor(title2, dxco::LabelUtil::RED);
		this->title2->setVisible(false);
		this->addChild(this->title2);
	}

	//text messages
	this->panel = dxco::SpriteUtil::create("gameplay/PLACA_texto.png", 0, 0, lifeBack);
	this->panel->setPositionX(joystickBotonMovimiento->getPositionX() + (joystickBoton->getPositionX()-joystickBotonMovimiento->getPositionX())/2);
	this->panel->setPositionY(joystickBoton->getPositionY());
	this->controlsLayer->addChild(this->panel, 10);
	this->panelText = CCLabelTTF::create("", "fonts/KBStickToThePlan.ttf", 12, CCSize(155,0), kCCTextAlignmentCenter);
	this->panelText->setColor(cocos2d::ccc3(255, 255, 255));
	this->panelText->setPositionX(this->panel->getPositionX());
	this->panelText->setPositionY(this->panel->getPositionY());
	this->controlsLayer->addChild(this->panelText, 10);
	this->panel->setOpacity(0);
	this->panelText->setOpacity(0);

	this->opacityLayer = CCLayerColor::create(ccc4(20, 20, 20, 200));
	this->addChild(this->opacityLayer, 4);

	this->opacityLayer->setVisible(false);
}

void HelloWorld::setLevelTitle() {
	std::string title = this->model->level->title;
	if (this->level > 0 && title != "") {
		std::string levelstring = "LEVEL " + dxco::StringUtil::toString(level) + ":";
		this->title1->setString(levelstring.c_str());
		this->title2->setString(title.c_str());
		this->title2->setVisible(true);
	}
}

void HelloWorld::message(std::string text, int seconds) {
	this->panelText->stopAllActions();
	this->panel->stopAllActions();

	this->panelText->setString(text.c_str());

	CCSequence *seq;
	if (this->panel->getOpacity() != 0) {
		this->panelText->setOpacity(255);
		this->panel->setOpacity(255);
		seq = CCSequence::create(CCDelayTime::create(seconds), CCFadeOut::create(0.25), NULL);
	} else {
		seq = CCSequence::create(CCFadeIn::create(0.25), CCDelayTime::create(seconds), CCFadeOut::create(0.25), NULL);
	}

	this->panel->runAction((CCSequence *)seq->copy());
	this->panelText->runAction(seq);
}

void HelloWorld::hideControls() {
	this->controlsLayer->setVisible(false);
}

void HelloWorld::showControls() {
	this->controlsLayer->setVisible(true);
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
		this->removeChild(backgroundLoading);
		this->removeChild(loadingItem->getSprite());

		this->titleDt += dt;

		if (this->titleDt > TITLE_DT - 0.5 && this->level != -1 && !this->title1->numberOfRunningActions()) {
			this->title1->runAction(CCFadeOut::create(0.5));
			this->title2->runAction(CCFadeOut::create(0.5));
		}

		if (this->titleDt > TITLE_DT || this->level == -1) {
			if (!this->juegoPausado) {
				this->model->update(dt);
				updateLabels();
			}

			if (!this->titleShown && this->level != -1) {
				this->titleShown = true;
				this->title1->setVisible(false);
				this->title2->setVisible(false);
				this->showControls();
			}
		}
		this->model->updateAds(dt);
	} else {
		this->loadingItem->update(dt);
		this->preloadTextures();

		if (dxco::SoundUtil::isMusicOn()) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
		} else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
		}

		if (!dxco::SoundUtil::isSoundEffectsOn()) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
		}

		if (!this->assetLoader->hasNext()) {
			this->preloaded = true;
			this->realInit();
			this->playMusic();
			this->model->timer = 0;
			if(this->level != -1) {
				this->hideControls();
			}
		}
	}
}

void HelloWorld::keyBackClicked() {

	if (this->levelFinishedLayer->isVisible()) { // Game over
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->replaceScene(dxco::GameTypeSelectionLayer::scene());

		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}

	if (true) { // TODO: Chaco pls!
		if (this->juegoPausado) {
			cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
			//pDirector->runWithScene(dxco::MenuParallax::scene());
			// TODO go to menu
		}

		this->juegoPausado = !this->juegoPausado;

		if (this->juegoPausado) {
			this->pauseGame();
		} else {
			this->resumeGame();
		}
	} else {
		this->stopMusic();
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		//pDirector->runWithScene(dxco::MenuParallax::scene());
		// TODO go to menu
	}
}

void HelloWorld::pauseGame() {
	this->stopMusic();
	this->pauseLayer->show();
	this->hideControls();
	this->opacityLayer->setVisible(true);
}

void HelloWorld::resumeGame() {
	this->juegoPausado = false;

	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->pauseLayer->hide();
	this->showControls();
	this->opacityLayer->setVisible(false);
}

void HelloWorld::playMusic() {

	if (dxco::SoundUtil::isMusicOn()) {
		if (random() % 2) {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bg1.mp3", true);
		} else {
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bg2.mp3", true);
		}
	}
}

void HelloWorld::stopMusic() {
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void HelloWorld::setTimerLabel(int totalSeconds) {
	int minutes = ceil(totalSeconds / 60);
	int seconds = totalSeconds % 60;

	std::string stringMinutes =  dxco::StringUtil::padLeft(minutes, 2);
	std::string stringSeconds = dxco::StringUtil::padLeft(seconds, 2);
	std::string timerText = stringMinutes + ":" + stringSeconds;
	this->timerLabel->setString(timerText.c_str());
}

void HelloWorld::updateLabels() {
	//WARNING the level specific labels are set in Level::updateInterface
	std::string playerScoreText = dxco::StringUtil::toString(this->model->player->score);
	this->playerScoreLabel->setString(playerScoreText.c_str());

	float playerLife = this->model->prop->get("player.life");
	this->lifeBar->setPercentage(this->model->player->life * 100 / playerLife);
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
	this->fireSoundId = -1;
	this->fire = cocos2d::CCParticleSystemQuad::create("fire.plist");

	/* The position is relative to the map, so emmited particles move with the map
	 * and not the emmiter. */
	fire->setPositionType(cocos2d::kCCPositionTypeRelative);
	fire->setPosition(x, y);
	this->mapa->addChild(fire, 2);
}

void HelloWorld::showFire() {
	if (this->fireSoundId != -1) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(this->fireSoundId);
	}
	this->fire->setVisible(true);

	if (dxco::SoundUtil::isSoundEffectsOn()) {
		this->fireSoundId = CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sounds/flame2.ogg", true);
	}
}

void HelloWorld::hideFire() {
	if (this->fireSoundId != -1) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopEffect(this->fireSoundId);
	}
	this->fire->setVisible(false);
}

void HelloWorld::playEffect(std::string effect) {
	if (dxco::SoundUtil::isSoundEffectsOn()) {
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effect.c_str());
	}
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
