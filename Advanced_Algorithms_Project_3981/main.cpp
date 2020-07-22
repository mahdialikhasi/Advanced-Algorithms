#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>
int main(){
	ifstream inFile;
	inFile.open("./inputX.txt");
	int k;
	inFile >> k;
	int n;
	inFile >> n;
	vector<pair<int, int> > position(n);
	for (int i = 0; i < n; ++i)
	{
		inFile >> position[i].first >> position[i].second;
	}
	inFile.close();
	ofstream outFile;
	outFile.open("./gamsSample");
	outFile << "Set 	i 		/";
	for (int i = 0; i < n; ++i){
		outFile << " v-" << i;
		if(i != n - 1){
			outFile << ",";
		}else{
			outFile << " /" << endl;
		}
	}
	outFile << "		j 		/";
	for (int i = 0; i < n; ++i){
		outFile << " v-" << i;
		if(i != n - 1){
			outFile << ",";
		}else{
			outFile << " /;" << endl;
		}
	}
	outFile << endl << "Table 	d(i,j)" << endl;
	for (int i = 0; i < n; ++i){
		outFile << "	" << "v-" << i;
	}
	outFile << endl;
	for (int i = 0; i < n; ++i){
		outFile << "v-" << i;
		for (int j = 0; j < n; ++j){
			outFile << "	" << sqrt((position[i].first - position[j].first) * (position[i].first - position[j].first) + 
				(position[i].second - position[j].second) * (position[i].second - position[j].second));
		}
		outFile << endl;
	}
	outFile << endl; 
	outFile << "Positive Variables 	y(i, j);" << endl;
	outFile << "Binary Variables 	x(j);" << endl;
	outFile << "Variables          	w;" << endl;
	outFile << "Equations 	sigy(i)" << endl << "			sigx" << endl << "			p(i)" << endl << "			check(i,j);" << endl;
	outFile << "sigy(i).. 		sum(j, y(i,j))=e=1;" << endl;
	outFile << "p(i).. 			sum(j, y(i,j) * d(i,j))=l=w;" << endl;
	outFile << "sigx.. 			sum(j, x(j))=e=" << k << ";" << endl;
	outFile << "check(i,j).. 	y(i,j)=l=x(j);" << endl;
	outFile << "Model resalloc /all/;" << endl;
	outFile << "option solprint = on ;" << endl;
	outFile << "solve resalloc using MIP minimizing w;" << endl;
	outFile.close();
	system("/opt/gams/gams30.1_linux_x64_64_sfx/gams gamsSample lo=2");
	
	return 0;
}