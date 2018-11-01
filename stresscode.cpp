#include "bits/stdc++.h"
using namespace std;

int main() {
	system(
			"g++ -lm -O2 -std=c++11 -pipe -o ac.exe ./ac.cpp");
	system(
			"g++ -lm -O2 -std=c++11 -pipe -o wa.exe ./wa.cpp");
	int tc = 1;
	while (1) {
		ofstream ofs("test.in");
		int n = rand()%5 + 1;
		int m = rand()%5 + 1;
		ofs << n << " " << m << endl;
		while(m--){
            int op;
            op = rand()%2+1;
            ofs << op << " ";
            if(op==1) ofs << rand()%n + 1 << endl;
            else{
                int At = rand()%n+1;
                int sz = rand()%(n - At + 1) + 1;
                ofs << At << " " << sz << endl;
            }
		}
		ofs.close();
		system("ac.exe <test.in >ac.txt");
		system("wa.exe <test.in >wa.txt");
		ifstream acs("ac.txt");
		ifstream was("wa.txt");
		string ac, wa;
		getline(was, wa, (char) EOF);
		getline(acs, ac, (char) EOF);
		was.close();
		acs.close();
		cerr << tc++ << endl;
		if (ac != wa){
			break;
		}
	}
}
