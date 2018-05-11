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
	fread(DataTPos, sizeof(long long), DataSize, fDataPos);
	/*for (int i = 0; i < DataSize; i++) {
		long long Pos;
		fread(&Pos, sizeof(long long), 1, fDataPos);
		if (DataTPos[i] != Pos) cout << i << endl;
	}*/
	fclose(fDataPos);
}

void Init_QueryPos(string filename) {
	FILE* fQueryPos = fopen(filename.c_str(), "rb");
	long long TraNum;
	fread(&TraNum, sizeof(long long), 1, fQueryPos);
	//fread(QueryTPos, sizeof(long long), QuerySize, fQueryPos);
	int offset = TraNum / QuerySize;
	int QueryNum = 0;
	for (int i = 0; i < TraNum; i++) {
		long long Pos;
		fread(&Pos, sizeof(long long), 1, fQueryPos);
		if ((i%offset == 0)&&(QueryNum<QuerySize)) {
			QueryTPos[QueryNum] = Pos;
			QueryNum++;
		}
	}
	fclose(fQueryPos);
}

void Init_Trajectory(Trajectory& A, FILE* fin, long long Pos) {

	_fseeki64(fin, Pos, SEEK_SET);
	long long TraLen;
	fread(&TraLen, sizeof(long long), 1, fin);
	A.Points.resize(TraLen);
	fread(&(A.Points[0]), sizeof(Point), TraLen, fin);
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
		//Trajectory Tra;
		//Init_Trajectory(Tra, fData, DataTPos[i]);
		//CellPoint[i].First = Tra.Points[0];
		//CellPoint[i].last = Tra.Points[Tra.Points.size() - 1];

		Point First, Last;
		_fseeki64(fData, DataTPos[i], SEEK_SET);
		long long TraNum;
		fread(&TraNum, sizeof(long long), 1, fData);
		fread(&First, sizeof(Point), 1, fData);
		_fseeki64(fData, DataTPos[i] + sizeof(long long) + sizeof(Point)*(TraNum - 1), SEEK_SET);
		fread(&Last, sizeof(Last), 1, fData);

		CellPoint[i].First = First;
		CellPoint[i].last = Last;
	}
	fclose(fData);
}

#endif // !_INIT_H

