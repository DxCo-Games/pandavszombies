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
                   ../../Classes/dxco/CCAdView.cpp \
                   ../../Classes/dxco/AdsAPI.cpp \
                   ../../Classes/dxco/RevMob.cpp \
                   ../../Classes/dxco/RevMobAds_Android.cpp \
                   ../../Classes/dxco/JoystickController.cpp \
                   ../../Classes/dxco/Joystick.cpp \
                   ../../Classes/dxco/MathUtil.cpp \
                   ../../Classes/dxco/TopDownItem.cpp \
                   ../../Classes/dxco/VoiceManager.cpp \
                   ../../Classes/dxco/AssetLoader.cpp \
                   ../../Classes/dxco/SteeringBehaviorItem.cpp \
                   ../../Classes/dxco/admob/AdmobHelper.cpp \
                   ../../Classes/dxco/Language.cpp \
                   ../../Classes/crimson/SoundUtil.cpp \
                   ../../Classes/crimson/ParseConfiguration.cpp \
                   ../../Classes/crimson/JoystickMira.cpp \
                   ../../Classes/crimson/JoystickMovimiento.cpp \
                   ../../Classes/crimson/GameModel.cpp \
                   ../../Classes/crimson/GameProperties.cpp \
                   ../../Classes/crimson/Player.cpp \
                   ../../Classes/crimson/Bullet.cpp \
                   ../../Classes/crimson/enemies/Enemy.cpp \
                   ../../Classes/crimson/enemies/AntEnemy.cpp \
                   ../../Classes/crimson/enemies/BombEnemy.cpp \
                   ../../Classes/crimson/enemies/Boss.cpp \
                   ../../Classes/crimson/enemies/SuperBoss.cpp \
                   ../../Classes/crimson/enemies/Bosszilla.cpp \
                   ../../Classes/crimson/enemies/EnemyFactory.cpp \
                   ../../Classes/crimson/bonus/TimeBonus.cpp \
                   ../../Classes/crimson/bonus/BonusFactory.cpp \
                   ../../Classes/crimson/bonus/NoBonusFactory.cpp \
                   ../../Classes/crimson/bonus/WeaponFirstBonusFactory.cpp \
                   ../../Classes/crimson/bonus/BombBonusFactory.cpp \
                   ../../Classes/crimson/bonus/Bonus.cpp \
                   ../../Classes/crimson/bonus/HealthBonus.cpp \
                   ../../Classes/crimson/bonus/WeaponBonus.cpp \
                   ../../Classes/crimson/bonus/WeaponSpeedBonus.cpp \
                   ../../Classes/crimson/bonus/FreezeBombBonus.cpp \
                   ../../Classes/crimson/Weapon.cpp \
                   ../../Classes/crimson/FireWeapon.cpp \
                   ../../Classes/crimson/SMG.cpp \
                   ../../Classes/crimson/Shotgun.cpp \
                   ../../Classes/crimson/bonus/ExplosionBonus.cpp \
                   ../../Classes/crimson/bonus/MovementSpeedBonus.cpp \
                   ../../Classes/crimson/bonus/PuntosBonus.cpp \
                   ../../Classes/crimson/bonus/ShieldBonus.cpp \
                   ../../Classes/crimson/levels/Level.cpp \
                   ../../Classes/crimson/levels/TimedLevel.cpp \
                   ../../Classes/crimson/levels/KillCountLevel.cpp \
                   ../../Classes/crimson/levels/SurvivalLevel.cpp \
                   ../../Classes/crimson/levels/FrenzyLevel.cpp \
                   ../../Classes/crimson/levels/TutorialLevel.cpp \
                   ../../Classes/crimson/levels/EnemyWave.cpp \
                   ../../Classes/crimson/levels/LevelParser.cpp \
                   ../../Classes/crimson/Mapa.cpp \
                   ../../Classes/crimson/daos/UserDAO.cpp \
                   ../../Classes/crimson/FireBulletWeapon.cpp \
                   ../../Classes/crimson/Bazooka.cpp \
                   ../../Classes/crimson/ChainedKillsManager.cpp \
                   ../../Classes/crimson/BazookaBullet.cpp \
                   ../../Classes/crimson/layers/GameTypeSelectionLayer.cpp \
                   ../../Classes/crimson/layers/LevelSelectionLayer.cpp \
                   ../../Classes/crimson/layers/AbstractMenuLayer.cpp \
                   ../../Classes/crimson/buttons/SurvivalButton.cpp \
                   ../../Classes/crimson/buttons/BuyPowerUpButton.cpp \
                   ../../Classes/crimson/buttons/StoryButton.cpp \
                   ../../Classes/crimson/buttons/LevelButton.cpp \
                   ../../Classes/crimson/buttons/LevelScreenButton.cpp \
                   ../../Classes/crimson/buttons/GameTypeSelectionButton.cpp \
                   ../../Classes/crimson/buttons/EquipPandaButton.cpp \
                   ../../Classes/crimson/buttons/NextLevelButton.cpp \
                   ../../Classes/crimson/buttons/RestartSurvivalButton.cpp \
                   ../../Classes/crimson/buttons/ResumeButton.cpp \
                   ../../Classes/crimson/buttons/ShareButton.cpp \
                   ../../Classes/crimson/layers/LevelFinishedLayer.cpp \
                   ../../Classes/crimson/layers/EquipPandaLayer.cpp \
                   ../../Classes/crimson/layers/EquipPandaItem.cpp \
                   ../../Classes/crimson/layers/PauseLayer.cpp \
                   ../../Classes/crimson/layers/RankingLayer.cpp
                   
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocos_extension_static cocosdenshion_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,extensions)


