#ifndef _DFD_H
#define _DFD_H

#include <init.h>
#include <dist.h>

using namespace std;

double g[2][MaxLen];

double LB_cell(vector<Point>& A, vector<Point>& B) {
	return (max(double_dist(A[0], B[0]), double_dist(A[A.size() - 1], B[B.size() - 1])));
}

double double_DFD(vector<Point>& A, vector<Point>& B) {
	int LengthA = A.size();
	int LengthB = B.size();
	for (int i = 0; i < LengthA; i++) {
		double *gTemp1 = g[i % 2];
		double *gTemp2 = g[(i - 1) % 2];
		for (int j = 0; j < LengthB; j++) {
			double distemp = double_dist(A[i], B[j]);
			
			if (i != 0) {
				if (j != 0) {
					gTemp1[j] = max(min(min(gTemp2[j], gTemp1[j - 1]), gTemp2[j - 1]), distemp);
				}
				else gTemp1[j] = max(gTemp2[j], distemp);
			}
			else if (j != 0) {
				gTemp1[j] = max(gTemp1[j - 1], distemp);
			}
			else gTemp1[j] = distemp;
		}
	}
	return g[(LengthA - 1) % 2][LengthB - 1];
}

double DFD_LBrow(vector<Point>& A, vector<Point>& B) {
	int LengthA = A.size();
	int LengthB = B.size();
	for (int i = 0; i < LengthA; i++) {
		double LBrow = INFINITY;
		double *gTemp1 = g[i % 2];
		double *gTemp2 = g[(i - 1) % 2];

		for (int j = 0; j < LengthB; j++) {
			double distemp = double_dist(A[i], B[j]);
			LBrow = min(distemp, LBrow);

			if (i != 0) {
				if (j != 0) {
					gTemp1[j] = max(min(min(gTemp2[j], gTemp1[j - 1]), gTemp2[j - 1]), distemp);
				}
				else gTemp1[j] = max(gTemp2[j], distemp);
			}
			else if (j != 0) {
				gTemp1[j] = max(gTemp1[j - 1], distemp);
			}
			else gTemp1[j] = distemp;
		}
		if (LBrow > epsilon) return LBrow;
	}
	return g[(LengthA - 1) % 2][LengthB - 1];
}


#endif // !_DFD_H

