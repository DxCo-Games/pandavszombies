#include "Hints.h"
#include "../dxco/DB.h"
#include "daos/UserDAO.h"
#include "GameProperties.h"
#include "GameModel.h"
#include "../HelloWorldScene.h"
#include "levels/Level.h"
#include "levels/EnemyWave.h"
#include "bonus/WeaponFirstBonusFactory.h"
#include "../dxco/Language.h"

namespace dxco {

Hints::Hints(GameModel* model) {
	this->model = model;
	this->survivalShown = false;
}

void Hints::trackLoses() {
	bool win = this->model->level->isFinished();
	bool story = this->model->levelNumber != -1;

	if (win) {
		DB::putInteger("story.loses", 0);
	} else if (story) {
		int loses = DB::getInteger("story.loses");
		DB::putInteger("story.loses", loses + 1);
	}

}

std::string Hints::getHint() {
	this->trackLoses();
	std::string hint;

	hint = firstPowerup();
	if (hint != "") {
		return hint;
	}

	hint = flamethrowerFrenzy();
	if (hint != "") {
		return hint;
	}

	hint = superbossFireball();
	if (hint != "") {
		return hint;
	}

	hint = powerup();
	if (hint != "") {
		return hint;
	}

	hint = playAnother();
	if (hint != "") {
		return hint;
	}

	hint = powerupForSurvival();

	return hint;
}

std::string Hints::firstPowerup(){
	//if loses twice and still no attack powerup
	int loses = DB::getInteger("story.loses");
	int attackLevel = DB::getInteger("attack.damage.level");
	bool canBuy = UserDAO::getCoins() > GameProperties::getPrice("attack.damage");

	if (loses == 2 && attackLevel == 1 && canBuy) {
		DB::putInteger("story.loses", 0);
		return Language::get("hint.first");
	}

	return "";
}
std::string Hints::powerup(){
	//if loses three and has money for +1 attack
	int loses = DB::getInteger("story.loses");
	bool canBuy = UserDAO::getCoins() > GameProperties::getPrice("attack.damage");

	if (loses == 3 && canBuy) {
		DB::putInteger("story.loses", 0);
		return Language::get("hint.powerup");
	}

	return "";
}
std::string Hints::playAnother(){
	int loses = DB::getInteger("story.loses");
	bool canBuy = UserDAO::getCoins() > GameProperties::getPrice("attack.damage");

	if (loses == 4 && !canBuy) {
		DB::putInteger("story.loses", 0);
		return Language::get("hint.playanother");
	}

	return "";
}
std::string Hints::powerupForSurvival(){
	//if loses survival in less than 1 min and has less than 3 attacks
	bool survival = this->model->vista->survivalMode;
	int seconds = this->model->timer;
	int attackLevel = DB::getInteger("attack.damage.level");

	if (!this->survivalShown && survival && seconds < 60 && attackLevel < 4) {
		this->survivalShown = true; //show once per session
		return Language::get("hint.survival");
	}

	return "";
}
std::string Hints::superbossFireball(){
	//if loses twice to superboss and hasn't the fireball
	int loses = DB::getInteger("story.loses");
	bool fireballUnlocked = DB::getInteger("firebullet.unlocked") != 0;

	bool isSuperboss = false;
	for (int i=0; i < this->model->level->waves.size(); i++) {
		if(this->model->level->waves[i]->isBoss == 2) {
			isSuperboss = true;
			break;
		}
	}

	if (loses == 2 && !fireballUnlocked && isSuperboss) {
		DB::putInteger("story.loses", 0);
		return Language::get("hint.superboss");
	}

	return "";
}
std::string Hints::flamethrowerFrenzy(){
	//if loses 3 in frenzy like and hasnt unlocked bazooka or fire
	int loses = DB::getInteger("story.loses");
	bool flameUnlocked = DB::getInteger("fire.unlocked") != 0;
	bool bazookaUnlocked = DB::getInteger("bazooka.unlocked") != 0;
	bool isFrenzy = (dynamic_cast<WeaponFirstBonusFactory*>(this->model->level->bonusFactory));

	if (loses == 3 && isFrenzy && (!flameUnlocked || !bazookaUnlocked)) {
		DB::putInteger("story.loses", 0);
		return Language::get("hint.frenzy");
	}

	return "";
}

} /* namespace dxco */
