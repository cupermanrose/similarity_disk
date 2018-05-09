#ifndef  _SIMILARITY_H
#define _SIMILARITY_H

#include <iostream>
#include <stdio.h>
#include <init.h>
#include <DFD.h>

using namespace std;

void Search_baseline() {
	FILE* fData = fopen(DataFile.c_str(), "rb");
	FILE* fQuery = fopen(QueryFile.c_str(), "rb");
	Trajectory DTra, QTra;
	int ans = 0;
	int lbcell = 0;
	for (int i = 0; i < QuerySize; i++) {
		Init_Trajectory(QTra, fQuery, QueryTPos[i]);
		for (int j = 0; j < DataSize; j++) {
			Init_Trajectory(DTra, fData, DataTPos[j]);
			if (LB_cell(QTra.Points, DTra.Points) > epsilon) continue;
			lbcell++;
			//if (DFD_LBrow(QTra.Points, DTra.Points) < epsilon) ans++;
			if (double_DFD(QTra.Points, DTra.Points) < epsilon) ans++;
		}
	}
	cout << lbcell << endl;
	cout << ans << endl;
}

#endif // ! _SIMILARITY_H

