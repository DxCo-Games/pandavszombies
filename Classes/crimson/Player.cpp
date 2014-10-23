#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "GameProperties.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "FireWeapon.h"
#include "FireBulletWeapon.h"
#include "Bazooka.h"
#include "SMG.h"
#include "../HelloWorldScene.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) :
		TopDownItem(PLAYER_ANGLE_POSITIONS), Item(sprite, animations){
	this->state = QUIETO;
	this->life = 0; //set outside
	this->movementSpeedBonus = 1;
	this->weaponSpeedBonus = 1;
	this->shieldActivated = 0;
	this->score = 0;
	this->moving = false;
	this->moveRotation;
	this->weapon = NULL;
	this->weaponBonus = NULL;
	this->invertido = false;
}

void Player::hurt(float damage) {

	if (shieldActivated == 0 || damage < 0) {
		this->life -= damage;
		if(damage > 0) {
			this->model->playerHurt = true;
			this->state = HERIDO;
		}

		float playerLife = this->model->prop->get("player.life");
		if (this->life > playerLife) {
			this->life = playerLife;
		}
	}
}


void Player::update(float dt) {
	Item::update(dt);

	//this->hurt is resetted on every update, check state to tell if its hurt
	bool wasHurt = this->state == HERIDO;
	float speed = this->model->prop->get("player.speed");
	if (wasHurt) {
		speed *= 0.7;
	}

	this->updateFireLocation();

	if (this->moving) {
		if (this->invertido) {
			this->state = CAMINANDO_INVERTIDO;
		} else {
			this->state = CAMINANDO;
		}

		cocos2d::CCPoint position = this->getLocation();

		float x = position.x;
		float y = position.y;

		float deltaX = cos(this->moveRotation) * speed * this->movementSpeedBonus * dt;
		float deltaY = sin(this->moveRotation) * speed * this->movementSpeedBonus * dt;

		float finalX = x + deltaX;
		float finalY = y + deltaY;

		float mapWidth = this->model->mapa->getWidth();
		float mapHeight = this->model->mapa->getHeight();

		if (finalX - this->getWidth() / 4 < 0 || finalX + this->getWidth() / 4 > mapWidth){
			//cancel X movement
			deltaX = 0;
			finalX = x;
		}

		if (finalY - this->getHeight() / 2 < 0 || finalY > mapHeight){
			//cancel Y movement
			deltaY = 0;
			finalY = y;
		}

		if (deltaX != 0 || deltaY != 0) {
			this->model->mapa->move(-deltaX, -deltaY);
			this->model->vista->clouds->move(-deltaX, -deltaY);
			this->model->vista->bubble->setPosition(cocos2d::CCPoint(finalX, finalY - 5));

			//undo map movement so player stays in the middle
			SpriteUtil::move(this->sprite, deltaX, deltaY);
			int zorder = 1000 - this->getBottomPosition() * 1000 / mapHeight;
			this->model->mapa->reorderChild(this->sprite, zorder);
		}
	} else {
		this->state = QUIETO;
	}
}


void Player::updateFireLocation() {
	int angleState = this->getAngleState();
	int x = this->getLocation().x;
	int y = this->getLocation().y;

	int screenCenterX = x - 40;
	int screenCenterY = y - 40;

	int playerWidth = 40;
	int playerHeight = 40;
	//FIXME calculate this only once.
	//TODO fix rotation to match the direction of the weapon
	//TODO esto si se puede reutilizar

	if (angleState < 8) {
		//put the flash below the panda
		this->model->vista->fire->setZOrder(
				this->model->player->getSprite()->getZOrder() - 1);
	} else {
		this->model->vista->fire->setZOrder(
				this->model->player->getSprite()->getZOrder() + 1);
	}

	float rotationAngle = angleState * -22.5;
	float radianAngle = rotationAngle / -57.2957795;

	switch (angleState) {

	case 0: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 31 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 31 + sin(radianAngle) * playerHeight);
		break;
	}
	case 1: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 40 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 20 + sin(radianAngle) * playerHeight);
		break;
	}
	case 2: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 49 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 9 + sin(radianAngle) * playerHeight);
		break;
	}
	case 3: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 56 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 5 + sin(radianAngle) * playerHeight);
		break;
	}
	case 4: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 59 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 7 + sin(radianAngle) * playerHeight);
		// 90 grados
		break;
	}
	case 5: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 47 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 22 + sin(radianAngle) * playerHeight);
		break;
	}
	case 6: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 54 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 18 + sin(radianAngle) * playerHeight);
		break;
	}
	case 7: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 55 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 29 + sin(radianAngle) * playerHeight);
		break;
	}
	case 8: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 50 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 41 + sin(radianAngle) * playerHeight);
		// 180
		break;
	}
	case 9: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 41 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 52 + sin(radianAngle) * playerHeight);
		break;
	}
	case 10: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 33 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 62 + sin(radianAngle) * playerHeight);
		break;
	}
	case 11: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 28 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 68 + sin(radianAngle) * playerHeight);
		break;
	}
	case 12: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 23 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 65 + sin(radianAngle) * playerHeight);
		// 270
		break;
	}
	case 13: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 22 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 62 + sin(radianAngle) * playerHeight);
		break;
	}
	case 14: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 21 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 55 + sin(radianAngle) * playerHeight);
		break;
	}

	case 15: {
		this->model->vista->fire->setPositionX(
				screenCenterX + 27 + cos(radianAngle) * playerWidth);
		this->model->vista->fire->setPositionY(
				screenCenterY + 44 + sin(radianAngle) * playerHeight);
		break;
	}
	}
}

bool Player::isActive() {
	return this->life > 0;
}

void Player::setWeapon(weapons type) {
	this->weaponType = type;
	model->vista->hideFire();

	if (this->weapon != NULL) {
		this->model->vista->mapa->removeChild(this->weapon->flashSprite, true);
	}

	switch(type) {
	case SHOTGUN: {
		this->weapon = new Shotgun(this->model);
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/shotgun.png");
		break;
	}
	case SMG_: {
		this->weapon = new SMG(this->model);
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/smg.png");
		break;
	}
	case FIRE: {
		model->vista->showFire();
		this->weapon = new FireWeapon(this->model);
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/flame_thrower.png");
		break;
	}
	case BAZOOKA: {
		this->weapon = new Bazooka(this->model);
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/bazooka.png");
		break;
	}
	case FIREBULLET: {
		this->weapon = new FireBulletWeapon(this->model);
		//FIXME need icon
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/fire.png");
		break;
	}
	default:{
		this->weapon = new Weapon(this->model);
		SpriteUtil::setTexture(model->vista->weaponIcon, "bonus/PISTOLA.png");
		break;
	}
	}
}

} /* namespace dxco */
