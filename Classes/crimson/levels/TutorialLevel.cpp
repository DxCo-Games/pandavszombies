#include "TutorialLevel.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"
#include "../GameProperties.h"
#include "../Player.h"
#include "../../dxco/StringUtil.h"
#include "../layers/GameTypeSelectionLayer.h"
#include "SimpleAudioEngine.h"
#include "../daos/UserDAO.h"

namespace dxco {

TutorialLevel::TutorialLevel(GameModel* model): Level(model, *new std::vector<EnemyWave*>, "Tutorial") {
	this->currentStep = 0;
	this->movementDt = 0;
	this->rotationDt = 0;
	this->totalEnemies = 4;
	this->messageDisplayed = false;

	//step 0 message
	model->vista->message("Hold and move the left pad to move around");
	this->model->prop->set("enemy.level",  1);
}

bool TutorialLevel::isFinished() {
	return this->currentStep >= 6;
}

void TutorialLevel::update(float dt) {
	switch (this->currentStep) {

	case 0: { //USE MOVEMENT JOYSTICK
		if (this->model->player->moving) {
			this->movementDt += dt;
		}
		//move for total 5s to finish step
		if (this->movementDt > 5) {
			this->movementDt = 0;
			this->currentStep++;
			//step 1 message
			model->vista->message("Now hold and move the right pad to change the shoot direction");
		}
		break;
	}

	case 1: { //USE ROTATION JOYSTICK
		if (this->model->player->rotating) {
			this->rotationDt += dt;
		}
		//rotate for total 3s to finish step
		if (this->rotationDt > 3) {
			this->rotationDt = 0;
			this->currentStep++;
			//step 2 message
			model->vista->message("Good! Now try using both pads together");
		}
		break;
	}

	case 2: { //USE BOTH JOYSTICKS
		if (this->model->player->moving) {
			this->movementDt += dt;
		}
		if (this->model->player->rotating) {
			this->rotationDt += dt;
		}
		//rotate and move for total 3s to finish step
		if (this->movementDt > 3 && this->rotationDt > 3) {
			this->currentStep++;
			model->vista->message("There's a zombie around, kill him!");

			//create one zombie
			this->model->enemyFactory->createEnemy(this->model);
		}
		break;
	}

	case 3: {
		//finish when all zombies killed
		if (this->model->kills == 1) {
			model->vista->message("Pick up the bonus to improve your weapon");
			this->currentStep++;

			//plant a bonus
			if (model->bonuses.size()) {
				model->bonuses[0]->dt = -500; //make sure it won't disappear
			}
		}
		break;
	}
	case 4: {
		//finish when bonus picked up
		if(model->player->weaponType != Player::PISTOL) {
			this->currentStep++;
			model->vista->message("Watch out! Another zombie wave!");
			this->model->enemyFactory->createEnemy(this->model);
			this->model->enemyFactory->createEnemy(this->model);
			this->model->enemyFactory->createEnemy(this->model);
		}
		break;
	}
	case 5: {
		int equipPanda = GameProperties::get("push.equip");

		if (this->model->kills == 4 && !this->messageDisplayed) {

			if (equipPanda == 0) {
				model->vista->message("Good job! here are 250 coins, use them to equip your panda");
			} else {
				model->vista->message("Good job!");
			}

			this->messageDisplayed = true;
		}

		if (this->model->enemies.size() == 0) {
			//note this waits for the blood splat to disappear.

			if (equipPanda == 0) {
				GameProperties::set("push.equip", 1);
				UserDAO::addCoins(250);

				cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
				pDirector->replaceScene(GameTypeSelectionLayer::scene());

				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
				CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
			}
			this->currentStep++;
		}
		break;
	}
	}

	this->updateInterface();
}

//FIXME good job not displayed

void TutorialLevel::restartLevel() {
	this->currentStep = 0;
	this->movementDt = 0;
	this->rotationDt = 0;
}

} /* namespace dxco */
