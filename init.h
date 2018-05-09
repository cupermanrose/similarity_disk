#ifndef _INIT_H
#define _INIT_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <parameter.h>
#include <Element.h>
#include <iostream>

using namespace std;

struct Cell {
	Point First, last;
};

long long DataTPos[DataSize];
long long QueryTPos[QuerySize];
Cell CellPoint[DataSize];

void Init_DataPos(string filename) {
	FILE* fDataPos = fopen(filename.c_str(), "rb");
	long long TraNum;
	fread(&TraNum, sizeof(long long), 1, fDataPos);
	for (int i = 0; i < TraNum; i++) {
		if (i > DataSize) break;
		long long Pos;
		fread(&Pos, sizeof(long long), 1, fDataPos);
		DataTPos[i] = Pos;
	}
	fclose(fDataPos);
}

void Init_QueryPos(string filename) {
	FILE* fQueryPos = fopen(filename.c_str(), "rb");
	long long TraNum;
	fread(&TraNum, sizeof(long long), 1, fQueryPos);
	for (int i = 0; i < TraNum; i++) {
		if (i > QuerySize) break;
		long long Pos;
		fread(&Pos, sizeof(long long), 1, fQueryPos);
		QueryTPos[i] = Pos;
	}
	fclose(fQueryPos);
}

void Init_Trajectory(Trajectory& A, FILE* fin, long long Pos) {
	A.Points.clear();
	_fseeki64(fin, Pos, SEEK_SET);
	long long TraLen;
	fread(&TraLen, sizeof(long long), 1, fin);

	vector<Point> TempPoints(TraLen);
	fread(&TempPoints[0], sizeof(Point), TraLen, fin);
	A.Points = TempPoints;
	/*for (int i = 0; i < TraLen; i++) {
		Point TempP;
		fread(&(TempP.lat), sizeof(double), 1, fin);
		fread(&(TempP.lon), sizeof(double), 1, fin);
		A.Points.push_back(TempP);
	}*/
}

void Init_CellPoint() {
	FILE* fData = fopen(DataFile.c_str(), "rb");
	for (int i = 0; i < DataSize; i++) {
		Trajectory Tra;
		Init_Trajectory(Tra, fData, DataTPos[i]);
		CellPoint[i].First = Tra.Points[0];
		CellPoint[i].last = Tra.Points[Tra.Points.size() - 1];
	}
	fclose(fData);
}

#endif // !_INIT_H

