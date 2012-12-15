#include "DXMath.h"
namespace DXMath
{

	float AngleFromXY_0_To_TWOPI(const float _x, const float _y)
	{
		
		float theta(0.0f);
		if(IsZero(_x))
		{
			if(IsZero(_y))
				return 0.0f;
			if(_y > 0.0f)
				return HALFPI;
			if(_y < 0.0f)
				return TWOPI - HALFPI;
		}
		// 1st and 4th quadarant
		if(_x > 0.0f)
		{
			theta = atanf(_y/_x);
			if(theta < 0.0f)// in 4th quadrant
				theta += TWOPI;// [0, 2 * PI);
		}
		else// 3rd and 4th quadarnt.
		{
			theta = atanf(_y/_x) + PI;//[0, 2 * PI);
		}

		return theta;
	}
}// end of namspace DXMath.

