#ifndef _PARAMETER_H
#define _PARAMETER_H

#include <string>

using namespace std;

const int MaxLen = 1000000;
const int DataSize = 1000000;
const int QuerySize = 100;
const double epsilon = 0.01*0.01;
const int tau = 32; //grouping size

//string DataFile = "G:\\work\\DFD_convoy\\dataset\\Geolife_Trajectories_1.3\\AllTra.txt";
//string DataPosFile = "G:\\work\\DFD_convoy\\dataset\\Geolife_Trajectories_1.3\\AllTraPos.txt";
//string QueryFile = "G:\\work\\DFD_convoy\\dataset\\Geolife_Trajectories_1.3\\AllTra.txt";
//string QueryPosFile = "G:\\work\\DFD_convoy\\dataset\\Geolife_Trajectories_1.3\\AllTraPos.txt";

string DataFile = "G:\\work\\DFD_convoy\\dataset\\OSM_FULL\\Trajectory\\AllTra50.txt";
string DataPosFile = "G:\\work\\DFD_convoy\\dataset\\OSM_FULL\\Trajectory\\AllTraPos50.txt";
string QueryFile = "G:\\work\\DFD_convoy\\dataset\\OSM_FULL\\Trajectory\\AllTra50.txt";
string QueryPosFile = "G:\\work\\DFD_convoy\\dataset\\OSM_FULL\\Trajectory\\AllTraPos50.txt";

#endif