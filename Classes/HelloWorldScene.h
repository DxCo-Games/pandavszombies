#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "dxco/JoystickController.h"
#include "crimson/GameModel.h"
#include "crimson/Mapa.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
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

    virtual void initFire(float x, float y);
    cocos2d::CCParticleSystemQuad* fire;

    void updatePlayerLifeLabel();
private:
    dxco::Player* createPlayer();
    dxco::GameModel* model;
    dxco::JoystickController joystickController;
    cocos2d::CCLayerColor* damageLayer;

    cocos2d::CCLabelTTF* playerHPLabel;
};

#endif // __HELLOWORLD_SCENE_H__
