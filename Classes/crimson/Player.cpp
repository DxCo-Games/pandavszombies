#include "Player.h"
#include "Bullet.h"
#include "GameModel.h"
#include "Weapon.h"
#include "Shotgun.h"
#include "FireWeapon.h"
#include "SMG.h"
#include "../HelloWorldScene.h"
#include "../dxco/SpriteUtil.h"

namespace dxco {

Player::Player(cocos2d::CCSprite* sprite, std::map<int, Animation*>& animations) : TopDownItem(sprite, animations, PLAYER_ANGLE_POSITIONS) {
	this->state = QUIETO;
	this->life = PLAYER_LIFE;
	this->score = 0;
	this->moving = false;
	this->moveRotation;
}

void Player::hurt(float damage) {
	this->life -= damage;
	if(damage > 0) {
		this->model->damage = true;

		if(this->state != HERIDO1 && this->state != HERIDO2) {
			//TODO use both animations
			this->state = HERIDO2;
		}
	}

	if (this->life > PLAYER_LIFE) {
		this->life = PLAYER_LIFE;
	}
}


void Player::update(float dt) {
	//FIXME this line is overriding the sprite of the weapon
	Item::update(dt);

	if (this->moving) {
		this->state = CAMINANDO;
		cocos2d::CCPoint position = this->getLocation();

		float x = position.x;
		float y = position.y;

		float deltaX = cos(this->moveRotation) * PLAYER_SPEED * dt;
		float deltaY = sin(this->moveRotation) * PLAYER_SPEED * dt;

		float finalX = x + deltaX;
		float finalY = y + deltaY;

		float mapWidth = this->model->mapa->getWidth();
		float mapHeight = this->model->mapa->getHeight();

		if (finalX > 0 && finalX < mapWidth && finalY > 0
				&& finalY < mapHeight) {
			this->model->mapa->move(-deltaX, -deltaY);
			this->model->vista->clouds->move(-deltaX, -deltaY);

			//undo map movement so player stays in the middle
			SpriteUtil::move(this->sprite, deltaX, deltaY);

			//update z order for isometric ordering of characters
			int zorder = 100 - y * 100 / mapHeight;
			this->model->mapa->reorderChild(this->sprite, zorder);

			//put the emmiter where the player is
			this->model->vista->fire->setPosition(finalX, finalY);
		}
	} else {
		this->state = QUIETO;
	}
}

bool Player::isActive() {
	return this->life > 0;
}

void Player::setWeapon(weapons type) {
	this->weaponType = type;
	model->vista->fire->setVisible(false);

	switch(type) {
	case SHOTGUN: {
		this->weapon = new Shotgun(this->model);
		break;
	}
	case SMG_: {
		this->weapon = new SMG(this->model);
		break;
	}
	case FIRE: {
		model->vista->fire->setVisible(true);
		this->weapon = new FireWeapon(this->model);
		break;
	}
	default:{
		this->weapon = new Weapon(this->model);
		break;
	}
	}
}

cocos2d::CCPoint Player::getLocation() {
	cocos2d::CCPoint location = Item::getLocation();
//	location.setPoint(location.x - this->model->vista->mapa->getPositionX(),
//			location.y - this->model->vista->mapa->getPositionY());

	return location;
}

} /* namespace dxco */
