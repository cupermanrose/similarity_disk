#ifndef _DIST_H
#define _DIST_H

#include <Element.h>

using namespace std;

double double_dist(Point& A, Point& B) {
	double lat = A.lat - B.lat;
	double lon = A.lon - B.lon;
	double c = lat*lat + lon*lon;
	//return sqrt(c);
	return c;
}

bool bool_dist(Point& A, Point& B) {
	double lat = A.lat - B.lat;
	double lon = A.lon - B.lon;
	double c = lat*lat + lon*lon;
	//return sqrt(c);
	if (c < epsilon) return true;
	return false;
}
#endif // !_DIST_H
