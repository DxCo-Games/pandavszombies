#include "UserDAO.h"

#include "../../dxco/DB.h"
#include "../../dxco/StringUtil.h"
#include "../../dxco/facebook/FacebookAPI.h"

namespace dxco {

std::string UserDAO::getFacebookID() {
	return DB::getString(FACEBOOK_USERID_KEY);
}

void UserDAO::saveFacebookUser() {

	if (FacebookAPI::hasFacebookSession()) {
		CCLOG("Usuario conectado con facebook");
		std::string facebookAccessToken = DB::getString(FACEBOOK_ACCESS_TOKEN_KEY);
		std::string newAccessToken = FacebookAPI::getAccessToken();

		if (facebookAccessToken != newAccessToken) {
			UserDAO::doSaveFacebookUser();
		}
	} else {
		CCLOG("Usuario sin conexion con facebook");
	}
}

std::string UserDAO::getAccessToken() {
	std::string resultado = DB::getString(FACEBOOK_ACCESS_TOKEN_KEY);

	return resultado;
}

std::string UserDAO::getGameName() {

	std::string resultado = "";

	std::string firstName = DB::getString(FACEBOOK_FIRSTNAME_KEY);
	std::string lastName = DB::getString(FACEBOOK_LASTNAME_KEY);

	if (firstName != "") {
		resultado = firstName;

		if (lastName != "") {
			resultado += " ";
			resultado += lastName[0];
			resultado += ".";
		}
	}

	return resultado;
}

void UserDAO::doSaveFacebookUser() {

	std::string accessToken = FacebookAPI::getAccessToken();
	std::string facebookId = FacebookAPI::getUserID();
	std::string firstName = FacebookAPI::getFirstName();
	std::string lastName = FacebookAPI::getLastName();
	std::string userName = FacebookAPI::getUsername();

	std::string oldFacebookId = DB::getString(FACEBOOK_USERID_KEY);

	CCLOG("Registrando Usuario");
	CCLOG("Access Token : %s", accessToken.c_str());
	CCLOG("Facebook ID : %s", facebookId.c_str());
	CCLOG("First name : %s", firstName.c_str());
	CCLOG("Last name : %s", lastName.c_str());
	CCLOG("User name : %s", userName.c_str());

	DB::putString(FACEBOOK_ACCESS_TOKEN_KEY, accessToken);

	if (oldFacebookId != facebookId) {
		DB::putString(FACEBOOK_USERID_KEY, facebookId);
		DB::putString(FACEBOOK_FIRSTNAME_KEY, firstName);
		DB::putString(FACEBOOK_LASTNAME_KEY, lastName);
		DB::putString(FACEBOOK_USERNAME_KEY, userName);
		UserDAO::deleteAllScores();
	}
}

void UserDAO::addCoins(int coinsToAdd) {
	int coins = DB::getInteger(COINS_KEY);
	DB::putInteger(COINS_KEY, coins + coinsToAdd);
}

int UserDAO::getCoins() {
	return DB::getInteger(COINS_KEY);
}

void UserDAO::updateBestScore(int score) {

	int currentScore = UserDAO::getBestScore();

	if (score > currentScore) {
		DB::putInteger(BEST_SCORE_KEY, score);
	}
}

int UserDAO::getBestScore() {
	return DB::getInteger(BEST_SCORE_KEY);
}

void UserDAO::deleteAllScores() {
	DB::putInteger(BEST_SCORE_KEY, 0);
}

void UserDAO::finishLevel(int level, int stars) {
	//save stars and unlock next
	std::string current = "level"+StringUtil::toString(level);
	int previousStars = DB::getInteger(current, -1);
	if (stars > previousStars) {
		//update only if mark improved
		DB::putInteger(current, stars);
	}
	std::string next = "level"+StringUtil::toString(level+1);
	if (DB::getInteger(next, -1) == -1) {
		//unlock only if locked
		DB::putInteger(next, 0);
	}
}

bool UserDAO::levelEnabled(int level) {
	return DB::getInteger("level"+StringUtil::toString(level), -1) > -1;
}

int UserDAO::getLevelStars(int level) {
	return DB::getInteger("level"+StringUtil::toString(level), -1);
}

} /* namespace dxco */
