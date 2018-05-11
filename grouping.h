#ifndef _GROUPING_H
#define _GROUPING_H

#include <vector>
#include <parameter.h>
#include <Element.h>
#include <windows.h>
#include <init.h>

using namespace std;

namespace grouping {

	const int dimension = 2;
	const double eps = 1.0E-10;

	struct MBR {
		double U[dimension], L[dimension];
	};

	struct GroupTra {
		int length, number;
		int position[tau]; // store ending position of each position
		MBR MBR[tau];
	};

	GroupTra AllGTra[DataSize];
	double g[2][tau];

	void ClearMBR(MBR& MBR) {
		for (int i = 0; i < dimension; i++) {
			MBR.L[i] = INFINITY;
			MBR.U[i] = -INFINITY;
		}
		return;
	}

	void CreateMBR(MBR& MBR, Trajectory& T, int left, int right) { // create MBR from left to right-1
		ClearMBR(MBR);
		for (int i = 0; i < dimension; i++) {
			for (int j = left; j < right; j++) {
				if (i == 0) {
					MBR.L[0] = min(MBR.L[0], T.Points[j].lat);
					MBR.U[0] = max(MBR.U[0], T.Points[j].lat);
				}
				else {
					MBR.L[1] = min(MBR.L[1], T.Points[j].lon);
					MBR.U[1] = max(MBR.U[1], T.Points[j].lon);
				}
			}
		}
		return;
	}

	double UDis(MBR& M1, MBR& M2) {
		double res = 0;
		for (int i = 0; i < dimension; i++) {
			double dis1 = abs(M1.U[i] - M2.L[i]);
			double dis2 = abs(M1.L[i] - M2.U[i]);
			dis1 = max(dis1, dis2);
			res = res + dis1*dis1;
		}
		//return sqrt(res);
		return res;
	}

	double LDis(MBR& M1, MBR& M2) {
		double res = 0;
		for (int i = 0; i < dimension; i++) {
			if ((M1.U[i] + eps > M2.U[i]) && (M1.L[i] - eps < M2.U[i])) continue;
			if ((M2.U[i] + eps > M1.U[i]) && (M2.L[i] - eps < M1.U[i])) continue;
			double dis1 = abs(M1.U[i] - M2.L[i]);
			double dis2 = abs(M1.L[i] - M2.U[i]);
			dis1 = min(dis1, dis2);
			res = res + dis1*dis1;
		}
		//return sqrt(res);
		return res;
	}

	double GlbDFD_LBrow(GroupTra& A, GroupTra& B) {
		int LengthA = A.length;
		int LengthB = B.length;
		for (int i = 0; i < LengthA; i++) {
			double LBrow = INFINITY;
			double *gTemp1 = g[i % 2];
			double *gTemp2 = g[(i - 1) % 2];

			for (int j = 0; j < LengthB; j++) {
				double distemp = LDis(A.MBR[i], B.MBR[j]);
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

	double GubDFD_LBrow(GroupTra& A, GroupTra& B) {
		int LengthA = A.length;
		int LengthB = B.length;
		for (int i = 0; i < LengthA; i++) {
			double LBrow = INFINITY;
			double *gTemp1 = g[i % 2];
			double *gTemp2 = g[(i - 1) % 2];

			for (int j = 0; j < LengthB; j++) {
				double distemp = UDis(A.MBR[i], B.MBR[j]);
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

	void DivideTrajectory(Trajectory& T, int TID, GroupTra& NewT) {
		NewT.number = TID;
		if (T.Points.size() < tau) {
			NewT.length = 1;
			NewT.position[0] = T.Points.size();
			CreateMBR(NewT.MBR[0], T, 0, NewT.position[0]);
			return;
		}

		NewT.length = tau;
		int unit = T.Points.size() / tau;
		for (int i = 0; i < tau; i++) {
			int left, right;
			left = i*unit;
			if (i == tau - 1) right = T.Points.size();
			else right = left + unit;
			NewT.position[i] = right;
			//cout << left << ' ' << right << ' ' << T.Points.size() << endl;
			CreateMBR(NewT.MBR[i], T, left, right);
		}
		return;
	}

	double GetDistPM(Point& A, MBR& M) { //  min dist
		double res = 0;
		for (int i = 0; i < dimension; i++) {
			if (i == 0) {
				if (A.lat < M.L[0]) res = res + (M.L[0] - A.lat)*(M.L[0] - A.lat);
				if (A.lat > M.U[0]) res = res + (A.lat - M.U[0])*(A.lat - M.U[0]);
			}
			else {
				if (A.lon < M.L[1]) res = res + (M.L[1] - A.lon)*(M.L[1] - A.lon);
				if (A.lon > M.U[1]) res = res + (A.lon - M.U[1])*(A.lon - M.U[1]);
			}
		}
		//return sqrt(res);
		return res;
	}

	double GetPdist(Point&A, double lat, double lon) {
		Point B;
		B.lat = lat; B.lon = lon;
		return double_dist(A, B);
	}

	bool LB_band(Trajectory& TempQ, GroupTra& TempGT, Trajectory& DTra) {// true: has a LB_band; false no lower bound
		double d1, d2, d3, d4, d;
		int PrePos = 0; // lbband of Q_i must < lbband of Q_i+1
		for (int i = 0; i < TempQ.Points.size(); i++) {
			bool flag = false;
			for (int j = 0; j < TempGT.length; j++) {
				if (flag) continue;
				d = GetDistPM(TempQ.Points[i], TempGT.MBR[j]);
				d1 = GetPdist(TempQ.Points[i], TempGT.MBR[j].L[0], TempGT.MBR[j].L[1]);
				d2 = GetPdist(TempQ.Points[i], TempGT.MBR[j].L[0], TempGT.MBR[j].U[1]);
				d3 = GetPdist(TempQ.Points[i], TempGT.MBR[j].U[0], TempGT.MBR[j].L[1]);
				d4 = GetPdist(TempQ.Points[i], TempGT.MBR[j].U[0], TempGT.MBR[j].U[1]);
				if ((d1 < epsilon) && (d2 < epsilon)) { flag = true; continue; }
				if ((d1 < epsilon) && (d3 < epsilon)) { flag = true; continue; }
				if ((d2 < epsilon) && (d4 < epsilon)) { flag = true; continue; }
				if ((d3 < epsilon) && (d4 < epsilon)) { flag = true; continue; }
				if (d < epsilon) {
					int st, en; // position of Tra
					if (j == 0) { st = 0; }
					else { st = AllGTra[TempGT.number].position[j - 1]; }
					en = AllGTra[TempGT.number].position[j];
					for (int k = st; k < en; k++) {
						if (k < PrePos) continue;
						if (double_dist(TempQ.Points[i], DTra.Points[k]) < epsilon) flag = true;
						if (flag) PrePos = k;
						if (flag) break;
					}
				}
			}
			if (!flag) return true; // can find any point is close to All_Query[Q].Points[i]
		}
		return false;
	}

	void Init() {
		FILE* fData = fopen(DataFile.c_str(), "rb");
		for (int i = 0; i < DataSize; i++) {
			Trajectory Tra;
			Init_Trajectory(Tra, fData, DataTPos[i]);
			GroupTra NewT;
			DivideTrajectory(Tra, i, NewT);
			AllGTra[i] = NewT;
		}
		fclose(fData);
	}
}

#endif // !_GROUPING_H
