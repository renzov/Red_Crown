#include<iostream>
#include<map>
#include<string>
using namespace std;

int main(){
	int N;
	string S;

	cin >> N >> S;
	map<string, int> cnt;

	for ( int i=0; i < N - 1; ++i )
		cnt[ S.substr(i,2) ]++;	

	string res;
	int maxCnt = 0;

	for ( map<string,int>::iterator it=cnt.begin(); it != cnt.end() ; ++it ){
		if ( it->second > maxCnt )
			res = it->first, maxCnt = it->second;
	}
	cout << res << endl;
	return 0;
}
