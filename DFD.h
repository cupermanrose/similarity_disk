#ifndef _DFD_H
#define _DFD_H

#include <init.h>
#include <dist.h>

using namespace std;

double g[2][MaxLen];
bool f[2][MaxLen];

double LB_cell(vector<Point>& A, Cell& B) {
	return (max(double_dist(A[0], B.First), double_dist(A[A.size() - 1], B.last)));
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

bool BoolDFD_LBrow(vector<Point>& A, vector<Point>& B) {
	int LengthA = A.size();
	int LengthB = B.size();
	for (int i = 0; i < LengthA; i++) {
		bool LBrow = false; // LBrow=false: no distemp is less epsilon
		bool *fTemp1 = f[i % 2];
		bool *fTemp2 = f[(i - 1) % 2];

		for (int j = 0; j < LengthB; j++) {
			bool distemp = bool_dist(A[i], B[j]);
			LBrow = LBrow | distemp;

			if (i != 0) {
				if (j != 0) {
					fTemp1[j] = (fTemp2[j] | fTemp1[j - 1] | fTemp2[j - 1]) & distemp;
				}
				else fTemp1[j] = fTemp2[j] & distemp;
			}
			else if (j != 0) {
				fTemp1[j] = fTemp1[j - 1] & distemp;
			}
			else fTemp1[j] = distemp;
		}
		if (!LBrow) return LBrow;
	}
	return f[(LengthA - 1) % 2][LengthB - 1];
}

#endif // !_DFD_H

