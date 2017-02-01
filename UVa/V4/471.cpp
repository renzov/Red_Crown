#include<string>
#include<sstream>
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
long long N;
set< long long > S1;
bool used[10];
const long long LIMIT = 9999999999LL;

bool diferent( long long n ){
	bool dig[10]={0};
	int d;
	while (n){
		d = n % 10;
		if ( dig[d] ) return false;
		dig[d] = true;
		n/=10;
	}
	return true;
}

void backtrack( long long den ){
	if ( (den * N) > LIMIT ) return;
	if ( diferent(N*den) ){
		S1.insert( N*den );	
	}
	for ( int i=0; i < 10; ++i )
		if ( !used[i] ){
			used[i] = true;
			backtrack( den*10 + i );
			used[i] = false;
		}
}

void process( string &s ){
	S1.clear();
	sscanf(s.c_str(),"%lld",&N);
	memset( used, false , sizeof(used) );
	for ( int i=1; i < 10; ++i ){
		used[i] = true;
		backtrack( i );
		used[i] = false;
	}
	for ( set<long long>::iterator it=S1.begin(); it != S1.end(); it++ ){
		cout << *it << " / " << (*it) / N << " = " << N << endl;
	}
}

int main(){
	string line;
	int runs;
	cin >> runs;
	while ( runs-- ){
		cin >> line;
		if ( line.size() <= 10 ){
			process(line);
		}
		if ( runs ) cout << endl;
	}
	return 0;
}
