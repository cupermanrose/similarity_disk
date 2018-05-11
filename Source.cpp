#include <iostream>
#include <string>
#include <fstream>
#include <mytime.h>
#include <parameter.h>
#include <Element.h>
#include <init.h>
#include <windows.h>
#include <similarity_search.h>

using namespace std;

int main() {
	init_time();
	Init_DataPos(DataPosFile);
	Init_QueryPos(QueryPosFile);
	Init_CellPoint();
	out_time("Init: ");

	init_time();
	grouping::Init();
	out_time("grouping Init ");

	/*init_time();
	Search_baseline();
	out_time("baseline ");*/

	init_time();
	Search_New();
	out_time("New ");

	init_time();
	Search_baselineG();
	out_time("baselineG ");

	

	system("pause");
}