#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "dxco/JoystickController.h"
#include "crimson/GameModel.h"
#include "crimson/Mapa.h"
#include "dxco/Container.h"
#include "dxco/Item.h"
#include <string>

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene(bool survivalMode);
    
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
    void updateChainedKills();

    cocos2d::CCLabelTTF* playerScoreLabel;
    cocos2d::CCLabelTTF* timerLabel;
    cocos2d::CCLabelTTF* killsLabel;
    cocos2d::CCLabelTTF* killsChainLabel;
    bool survivalMode;
    void playEffect(std::string effect, int probability=100);

    virtual void keyBackClicked();
    void stopMusic();
    void playMusic();
    bool juegoPausado;
    dxco::Item* loadingItem;

private:

    void preloadTextures();
    dxco::Player* createPlayer();
    void createInterface();
    dxco::Container* playerContainer;
    dxco::GameModel* model;
    dxco::JoystickController joystickController;

    //FIXME limpiar cosas del preload que no sirven mas
    bool preloaded;
    void realInit();
    int angulosCargados;
    cocos2d::CCLabelTTF* porcentajeCargado;
    cocos2d::CCProgressTimer* lifeBar;
    cocos2d::CCSprite* loading;
    cocos2d::CCSprite* joystickBotonIzq;
    cocos2d::CCSprite* joystickBotonDrc;
    int spriteSheetCargada;
};

#endif // __HELLOWORLD_SCENE_H__
