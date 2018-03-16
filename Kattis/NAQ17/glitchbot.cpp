#include<iostream>
#include<string>
using namespace std;

const int MAXN = 55;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int xe, ye;
int N;
int ins[MAXN];
string name[] = {"Left", "Right", "Forward"};

bool test(){
	int x = 0, y = 0;
	int dir = 1;
	for ( int i=0; i < N; ++i ){
		switch ( ins[i] ){
			case 1 : dir = (dir + 3)%4; break;
			case 0 : dir = (dir + 1)%4; break;
			case 2 : x += dx[dir], y += dy[dir]; break;
		}
	}
	return x == xe && y == ye;
}

int main(){
	string I;
	cin >> xe >> ye;
	cin >> N;

	for (int i=0; i < N; ++i){
		cin >> I;
		switch (I[0]){
			case 'L' : ins[i] = 0; break;
			case 'R' : ins[i] = 1; break;
			case 'F' : ins[i] = 2; break;
		}
	}
	int tmp;
	for ( int i=0; i < N; ++i ){
		tmp = ins[i];
		for ( int j=0; j < 3; ++j ){
			if ( j != ins[i] ){
				ins[i] = j;
				if ( test() ){
					cout << i + 1 << " " << name[j] << endl;
					return 0; 
				}
				ins[i] = tmp;
			}
		}
	}
	return 0;
}
