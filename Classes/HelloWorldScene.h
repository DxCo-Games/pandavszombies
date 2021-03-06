#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "dxco/JoystickController.h"
#include "crimson/GameModel.h"
#include "crimson/Mapa.h"
#include "dxco/Container.h"
#include "dxco/Item.h"
#include "crimson/layers/LevelFinishedLayer.h"
#include "crimson/layers/HintLayer.h"
#include "crimson/layers/PauseLayer.h"
#include "dxco/AssetLoader.h"

#include <string>

#define TITLE_DT 2.5

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene(bool survivalMode, bool frenzy, int level = -1);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void update(float dt);
    dxco::Mapa* mapa;
    dxco::Container* clouds;
    cocos2d::CCSprite* bubble;
    cocos2d::CCSprite* shadow;
    cocos2d::CCSprite* weaponIcon;
    cocos2d::CCProgressTimer* weaponBar;
    cocos2d::CCSprite* bonus1;
    cocos2d::CCSprite* bonus2;

    virtual void initFire(float x, float y);
    cocos2d::CCParticleSystemQuad* fire;
    int fireSoundId;
    void showFire();
    void hideFire();

    void updateBonus(std::string texture, float duration);
    void updateLabels();
    void setTimerLabel(int totalSeconds);
    void updateChainedKills();

    cocos2d::CCLabelTTF* playerScoreLabel;
    cocos2d::CCLabelTTF* timerLabel;
    cocos2d::CCSprite* timer;
    cocos2d::CCLabelTTF* killsLabel;
    cocos2d::CCLabelTTF* killsChainLabel;
    bool survivalMode;
    bool frenzyMode;
    int level;

    cocos2d::CCLabelTTF* title1;
    cocos2d::CCLabelTTF* title2;
    bool titleShown;
    float titleDt;
    void setLevelTitle();

    virtual void keyBackClicked();

    bool juegoPausado;
    dxco::Item* loadingItem;

    //0: city, 1: cemetery. cpp enums suck
    void setMap(int map);

    void message(std::string text, int seconds=10, cocos2d::CCSprite* aditionalSprite=NULL);
    cocos2d::CCSprite* panel;
    cocos2d::CCLabelTTF* panelText;

    //FIXME move sound stuff to a different class
    void playEffect(std::string effect);
    void stopMusic();
    void playMusic();

    cocos2d::CCLayerColor* opacityLayer;

    dxco::LevelFinishedLayer* levelFinishedLayer;
    dxco::HintLayer* hintLayer;
    dxco::PauseLayer* pauseLayer;
    dxco::AssetLoader* assetLoader;

    void hideControls();
    void showControls();

    void pauseGame();
    void resumeGame();
private:

    void preloadTextures();
    dxco::Player* createPlayer();
    void createInterface();
    dxco::Container* playerContainer;
    dxco::GameModel* model;
    dxco::JoystickController joystickController;

    bool preloaded;
    void realInit();
    cocos2d::CCProgressTimer* lifeBar;
    cocos2d::CCSprite* backgroundLoading;
    cocos2d::CCLayer* controlsLayer;
    int spriteSheetCargada;
};

#endif // __HELLOWORLD_SCENE_H__
