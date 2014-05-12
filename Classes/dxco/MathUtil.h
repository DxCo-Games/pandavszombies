#ifndef MATHUTIL_H_
#define MATHUTIL_H_

namespace dxco {

class MathUtil {
public:
	static float distance(cocos2d::CCPoint a, cocos2d::CCPoint b);
	static float angle(cocos2d::CCPoint center, cocos2d::CCPoint pointA);

};

} /* namespace dxco */
#endif /* MATHUTIL_H_ */
