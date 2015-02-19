#ifndef USERDAO_H_
#define USERDAO_H_

#include <string>

#define FACEBOOK_USERID_KEY "facebook_user_id"
#define FACEBOOK_ACCESS_TOKEN_KEY "facebook_access_token"
#define FACEBOOK_FIRSTNAME_KEY "facebook_firstname"
#define FACEBOOK_LASTNAME_KEY "facebook_lastname"
#define FACEBOOK_USERNAME_KEY "facebook_username"
#define BEST_SCORE_KEY "best_store"
#define COINS_KEY "coins"
#define LAST_LEVEL_UNLOCKED "last_level_unlocked"

namespace dxco {

/**
 * Stores:
 *  Name
 *  FBid
 *  BestScore per level (score1, score2...)
 */
class UserDAO {

public:
	static std::string getFacebookID();
	static std::string getAccessToken();
	static std::string getGameName();

	static void saveFacebookUser();

	static void updateBestScore(int score);
	static int getBestScore();

	static void addCoins(int coinsToAdd);
	static void deleteCoins(int coinsToDelete);
	static int getCoins();

	static void finishLevel(int level, int stars);
	static bool levelEnabled(int level);
	static int getLevelStars(int level);

	static int getLastUnlockedLevel();
private:
	static void doSaveFacebookUser();
	static void deleteAllScores();
};

} /* namespace dxco */
#endif /* USERDAO_H_ */
