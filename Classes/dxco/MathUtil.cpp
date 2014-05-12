#include "MathUtil.h"
#include <math.h>

namespace dxco {

float MathUtil::distance(cocos2d::CCPoint a, cocos2d::CCPoint b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	x = x * x;
	y = y * y;

	return sqrt(x + y);
}

float MathUtil::angle(cocos2d::CCPoint center,
		cocos2d::CCPoint pointA) {

	float result = 0;

	if (pointA.y > center.y) {
		// cuadrante 1
		if (pointA.x > center.x) {
			double adyacente = pointA.x - center.x;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa);
		} else { // cuadrante 2
			double adyacente = pointA.y - center.y;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + (PI * 0.5);
		}
	} else {
		// cuadrante 3
		if (pointA.x < center.x) {
			double adyacente = center.x - pointA.x;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + PI;
		} else { // cuadrante 4
			double adyacente = center.y - pointA.y;
			double hipotenusa = distance(pointA, center);

			result = acos(adyacente / hipotenusa) + (PI * 1.5);
		}
	}

	return result;
}


} /* namespace dxco */
