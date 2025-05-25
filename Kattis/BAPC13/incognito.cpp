#include<iostream>
#include<string>
#include<map>
using namespace std;

void process(){
	int N;
	cin >> N;
	map<string, int> cnt;
	string name, type;
	for ( int i = 0; i < N; ++i ){
		cin >> name >> type;
		cnt[type]++;
	}
	long long res = 1LL;
	for ( map<string, int>::iterator it = cnt.begin(); it != cnt.end(); it++ ){
		res *= ( it->second + 1 );
	}
	printf("%lld\n", res - 1 );
}

int main(){
	int t;
	cin >> t;
	while ( t-- )
		process();
	return 0;
}
