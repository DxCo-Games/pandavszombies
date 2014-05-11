#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <vector>

namespace dxco {

class StringUtil {
public:
	static std::string toString(int data);
	static std::string toString(float data);
	static int toInt(std::string data);
	static std::vector<std::string> split(const std::string &s, char delim);
};

} /* namespace dxco */
#endif /* STRINGUTIL_H_ */
