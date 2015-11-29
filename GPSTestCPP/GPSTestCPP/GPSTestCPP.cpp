// GPSTestCPP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define M_PI       3.14159265358979323846

const double EARTH_RADIUS = 6378.137;//地球半径



static double ConvertDegreesToRadians(double degrees)
{
	return degrees * M_PI / 180;
}

static double ConvertRadiansToDegrees(double radian)
{
	return radian * 180.0 / M_PI;
}

static double HaverSin(double theta)
{
	double v;

	v = sin(theta / 2);
	return v * v;
}


static double getGPSDistance(double lat1, double lng1, double lat2, double lng2)
{
	double vLng, vLat, h, distance;

	lat1 = ConvertDegreesToRadians(lat1);
	lng1 = ConvertDegreesToRadians(lng1);
	lat2 = ConvertDegreesToRadians(lat2);
	lng2 = ConvertDegreesToRadians(lng2);

	//差值
	vLat = fabs(lat1 - lat2);
	vLng = fabs(lng1 - lng2);
	//h is the great circle distance in radians, great circle就是一个球体上的切面，它的圆心即是球心的一个周长最大的圆。
	h = HaverSin(vLat) + cos(lat1) * cos(lat2) * HaverSin(vLng);
	distance = 2 * EARTH_RADIUS * sin(sqrt(h));
	return distance;

}


static double rad(double d)
{
	return d * M_PI / 180.0;
}
static double GetDistance(double lat1, double lng1, double lat2, double lng2)
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double a = radLat1 - radLat2;
	double b = rad(lng1) - rad(lng2);

	double s = 2 * sin(sqrt(pow(sin(a / 2), 2) +
		cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
	s = s * EARTH_RADIUS;
	s = round(s * 10000) / 10000;
	return s;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double lat1, lat2, lat3, lat4;
	double lng1, lng2, lng3, lng4;

	double distance1, distance2, distance3;

	lat1 = 39.60656198611111;
	lat2 = 39.606536991666665;
	lat3 = 39.606530219444444;
	lat4 = 39.606542725;

	lng1 = 116.21423292777777;
	lng2 = 116.21428956944445;
	lng3 = 116.21428175;
	lng4 = 116.21426485833334;
	
	distance1 = GetDistance(lat1, lng1, lat2, lng2);
	distance2 = GetDistance(lat2, lng2, lat3, lng3);
	distance3 = GetDistance(lat3, lng3, lat4, lng4);

	printf("distance1:%f\n", distance1);
	printf("distance2:%f\n", distance2);
	printf("distance3:%f\n", distance3);

	printf("distance new ctFuntion:%f\n", getGPSDistance(lat1, lng1, lat2, lng2));
	printf("distance new ctFuntion:%f\n", getGPSDistance(lat2, lng2, lat3, lng3));
	printf("distance new ctFuntion:%f\n", getGPSDistance(lat3, lng3, lat4, lng4));



	getchar();

	
	return 0;
}

