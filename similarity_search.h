#ifndef  _SIMILARITY_H
#define _SIMILARITY_H

#include <iostream>
#include <stdio.h>
#include <init.h>
#include <DFD.h>
#include <grouping.h>

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
			if (LB_cell(QTra.Points, CellPoint[j]) > epsilon) continue;
			Init_Trajectory(DTra, fData, DataTPos[j]);
			lbcell++;
			//if (DFD_LBrow(QTra.Points, DTra.Points) < epsilon) ans++;
			if (BoolDFD_LBrow(QTra.Points, DTra.Points)) ans++;
		}
	}
	fclose(fData); fclose(fQuery);
	cout << lbcell << endl;
	cout << ans << endl;
}

void Search_baselineG() {
	FILE* fData = fopen(DataFile.c_str(), "rb");
	FILE* fQuery = fopen(QueryFile.c_str(), "rb");
	Trajectory DTra, QTra;
	int ans = 0, lbcell = 0, Grouplb = 0, Groupub = 0;
	for (int i = 0; i < QuerySize; i++) {
		Init_Trajectory(QTra, fQuery, QueryTPos[i]);
		for (int j = 0; j < DataSize; j++) {
			if (LB_cell(QTra.Points, CellPoint[j]) > epsilon) continue;
			lbcell++;

			grouping::GroupTra QTraG;
			grouping::DivideTrajectory(QTra, i, QTraG);

			if (grouping::GlbDFD_LBrow(QTraG, grouping::AllGTra[j]) > epsilon) continue;
			Grouplb++;

			if (grouping::GubDFD_LBrow(QTraG, grouping::AllGTra[j]) < epsilon) ans++;
			else {
				Groupub++;
				Init_Trajectory(DTra, fData, DataTPos[j]);
				//if (DFD_LBrow(QTra.Points, DTra.Points) < epsilon) ans++;
				if (BoolDFD_LBrow(QTra.Points, DTra.Points)) ans++;
			}
		}
	}
	fclose(fData); fclose(fQuery);
	cout << "lbcell: " << lbcell << endl;
	cout << "Grouplb: " << Grouplb << endl;
	cout << "Groupub: " << Groupub << endl;
	cout << "BLGroup answer: " << ans << endl;
}

void Search_New() {
	FILE* fData = fopen(DataFile.c_str(), "rb");
	FILE* fQuery = fopen(QueryFile.c_str(), "rb");
	Trajectory DTra, QTra;
	int ans = 0, lbcell = 0, Grouplb = 0, Groupub = 0, lbband = 0;
	for (int i = 0; i < QuerySize; i++) {
		Init_Trajectory(QTra, fQuery, QueryTPos[i]);
		for (int j = 0; j < DataSize; j++) {
			if (LB_cell(QTra.Points, CellPoint[j]) > epsilon) continue;
			lbcell++;

			grouping::GroupTra QTraG;
			grouping::DivideTrajectory(QTra, i, QTraG);

			if (grouping::GlbDFD_LBrow(QTraG, grouping::AllGTra[j]) > epsilon) continue;
			Grouplb++;

			if (grouping::GubDFD_LBrow(QTraG, grouping::AllGTra[j]) < epsilon) { ans++; continue;}
			Groupub++;

			/*Init_Trajectory(DTra, fData, DataTPos[j]);

			if (grouping::LB_band(QTra, grouping::AllGTra[j], DTra)) continue;
			lbband++;*/

			
			if (EPplus_DFD(QTra.Points, DTra.Points)) ans++;

		}
	}
	fclose(fData); fclose(fQuery);
	cout << "lbcell: " << lbcell << endl;
	cout << "Grouplb: " << Grouplb << endl;
	cout << "Groupub: " << Groupub << endl;
	cout << "lbband: " << lbband << endl;
	cout << "BLGroup answer: " << ans << endl;
}
#endif // ! _SIMILARITY_H

