#include<iostream>
#include<string>
#include<sstream>
using namespace std;
string M[25];
string C[25];
int di[]={0,-1,-1,-1,0,1,1,1};
int dj[]={1,1,0,-1,-1,-1,0,1};

void simulate(){
	int cnt;
	int ii,jj;
	for ( int i=0; i < 20; ++i ) C[i] = M[i];
	for ( int i=0; i < 20; ++i ){
		for ( int j=0; j < 20; ++j ){
			cnt = 0;
			for ( int k=0; k < 8; ++k ){
				ii = i + di[k]; jj = j + dj[k];
				if ( ii < 0 || jj < 0 || ii >= 20 || jj >= 20 ) continue;
				if ( C[ii][jj] == 'O' ) cnt++;
			}
			if ( C[i][j] == 'O' ){
				M[i][j] = ( cnt >= 2 && cnt <= 3 )? 'O':' ';
			}
			else {
				M[i][j] = ( cnt == 3 )? 'O':' ';
			}
		}
	}
}

int main(){
	string sep = "********************";
	int x,y;
	int n;
	int runs;
	string line;
	cin >> runs;
	while ( runs-- ){
		for ( int i=0; i < 20; ++i ) M[i] = "                    "; //Init matrix
		cin >> n; getline(cin,line); // Reading til end of line
		while ( getline(cin,line) ){
			if ( !line.size() ) break;
			stringstream in(line);
			in >> x >> y;
			--x,--y;
			M[x][y] = 'O';
		}
		cout << sep << endl;
		while ( n-- ){
			for ( int i=0; i < 20; ++i ) cout << M[i] << endl;
			if ( n ) cout << sep << endl;
			simulate();
		}
		cout << sep << endl;
		if ( runs ) cout << endl;
	}
	return 0;
}
