#include "ColorUtil.h"


ColorUtil::ColorUtil(void)
{
}


ColorUtil::~ColorUtil(void)
{
}

/*��ȡccColorf����ɫ����*/
ccColor4F ColorUtil::getColor4F(int r,int g,int b,int alpha)
{
	ccColor4F c4 = {r/255.f, g/255.f, b/255.f, alpha/255.f};
	return c4;
}