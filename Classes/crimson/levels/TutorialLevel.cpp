#include "TutorialLevel.h"
#include "../GameModel.h"
#include "../../HelloWorldScene.h"
#include "../GameProperties.h"

namespace dxco {

TutorialLevel::TutorialLevel(GameModel* model): Level(model, *new std::vector<EnemyWave*>) {
	this->currentStep = 0;
	this->movementDt = 0;
	this->rotationDt = 0;
	this->totalEnemies = 4;
	this->messageDisplayed = false;

	//step 0 message
	model->vista->message("Hold and move the left pad to move around");
	this->model->prop->set("enemy.level",  0);
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
			model->bonuses.clear(); //in case one was already created
			Bonus* bonus = model->bonusFactory->createWeaponBonus(this->model,
					this->model->enemies[0]->getLocation());
			bonus->dt = -500; //make sure it won't disappear
			model->bonusFactory->addToMap(this->model, bonus);

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
		if (this->model->kills == 4 && !this->messageDisplayed) {
			model->vista->message("You'll earn coins every 1000 points, use them to equip your panda.");
			this->messageDisplayed = true;
		}
		if (this->model->enemies.size() == 0) {
			//note this waits for the blood splat to disappear.
			this->currentStep++;
		}
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
