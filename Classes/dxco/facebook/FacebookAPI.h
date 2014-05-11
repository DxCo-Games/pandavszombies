#ifndef FACEBOOKAPI_H_
#define FACEBOOKAPI_H_

#include <jni.h>

#include <string>

namespace dxco {

class FacebookAPI {
public:
	static std::string getAccessToken();
	static std::string getUserID();
	static std::string getUsername();
	static std::string getFirstName();
	static std::string getLastName();
	static bool hasFacebookSession();
	static void invite();
	static void rate(); //TODO remover de aca y crear SocialUtil o SocialAPI
};

} /* namespace dxco */
#endif /* FACEBOOKAPI_H_ */
