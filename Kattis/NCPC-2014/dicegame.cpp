#include<iostream>
#include<vector>
using namespace std;

int main(){
	int G = 0, E = 0;
	int v;

	for ( int i = 0; i < 4; ++i ){
		cin >> v;
		G += v;
	}
	for ( int i = 0; i < 4; ++i ){
		cin >> v;
		E += v;
	}
	if ( G > E ) cout << "Gunnar" << endl;
	else if ( E > G ) cout << "Emma" << endl;
	else cout << "Tie" << endl;
	return 0;
}
