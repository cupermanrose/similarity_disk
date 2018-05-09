#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <vector>

struct Point {
	double lat, lon;
};

struct Trajectory {
	vector<Point> Points;
};


#endif