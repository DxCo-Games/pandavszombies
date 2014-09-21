LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/dxco/Action.cpp \
                   ../../Classes/dxco/LabelUtil.cpp \
                   ../../Classes/dxco/SpriteUtil.cpp \
                   ../../Classes/dxco/Item.cpp \
                   ../../Classes/dxco/Animation.cpp \
                   ../../Classes/dxco/Parallax.cpp \
                   ../../Classes/dxco/Touchable.cpp \
                   ../../Classes/dxco/MenuParallaxItem.cpp \
                   ../../Classes/dxco/Button.cpp \
                   ../../Classes/dxco/DB.cpp \
                   ../../Classes/dxco/ParallaxLayer.cpp \
                   ../../Classes/dxco/JsonParser.cpp \
                   ../../Classes/dxco/StringUtil.cpp \
                   ../../Classes/dxco/FileUtil.cpp \
                   ../../Classes/dxco/Container.cpp \
                   ../../Classes/dxco/facebook/FacebookAPI.cpp \
                   ../../Classes/dxco/SmartHttpClient.cpp \
                   ../../Classes/dxco/ImageUrlLoader.cpp \
                   ../../Classes/dxco/ViewList.cpp \
                   ../../Classes/dxco/ViewListElement.cpp \
                   ../../Classes/dxco/ImageFileURLLoader.cpp \
                   ../../Classes/dxco/Sha1.cpp \
                   ../../Classes/dxco/SoundUtil.cpp \
                   ../../Classes/dxco/CCAdView.cpp \
                   ../../Classes/dxco/AdsAPI.cpp \
                   ../../Classes/dxco/RevMob.cpp \
                   ../../Classes/dxco/RevMobAds_Android.cpp \
                   ../../Classes/dxco/JoystickController.cpp \
                   ../../Classes/dxco/Joystick.cpp \
                   ../../Classes/dxco/MathUtil.cpp \
                   ../../Classes/dxco/TopDownItem.cpp \
                   ../../Classes/dxco/SteeringBehaviorItem.cpp \
                   ../../Classes/crimson/JoystickMira.cpp \
                   ../../Classes/crimson/JoystickMovimiento.cpp \
                   ../../Classes/crimson/GameModel.cpp \
                   ../../Classes/crimson/Player.cpp \
                   ../../Classes/crimson/Bullet.cpp \
                   ../../Classes/crimson/bonus/TimeBonus.cpp \
                   ../../Classes/crimson/Enemy.cpp \
                   ../../Classes/crimson/Boss.cpp \
                   ../../Classes/crimson/bonus/BonusFactory.cpp \
                   ../../Classes/crimson/bonus/Bonus.cpp \
                   ../../Classes/crimson/bonus/HealthBonus.cpp \
                   ../../Classes/crimson/bonus/WeaponBonus.cpp \
                   ../../Classes/crimson/Weapon.cpp \
                   ../../Classes/crimson/FireWeapon.cpp \
                   ../../Classes/crimson/SMG.cpp \
                   ../../Classes/crimson/Shotgun.cpp \
                   ../../Classes/crimson/EnemyFactory.cpp \
                   ../../Classes/crimson/bonus/ExplosionBonus.cpp \
                   ../../Classes/crimson/bonus/MovementSpeedBonus.cpp \
                   ../../Classes/crimson/bonus/PuntosBonus.cpp \
                   ../../Classes/crimson/Mapa.cpp \
                   ../../Classes/crimson/daos/UserDAO.cpp \
                   ../../Classes/crimson/NativeMethods.cpp
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos_extension_static cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)

