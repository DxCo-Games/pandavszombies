#ifndef FILEUTIL_H_
#define FILEUTIL_H_

#include <string>

namespace dxco {

class FileUtil {
public:
	static std::string readFile(std::string& path);
	static bool writeFile(std::string& path, std::string& content);
};

} /* namespace dxco */
#endif /* FILEUTIL_H_ */
