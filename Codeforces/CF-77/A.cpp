#include<cstdio>
using namespace std;

char S[128];

int main(){

	scanf("%s", S);

	int cnt = 0;
	char last = '-';
	bool ok = true;

	for ( int i=0; S[i] && ok ; ++i ){
		if ( S[i] == last ){
			cnt++;
		}
		else {
			cnt = 1;
			last = S[i];
		}
		ok = cnt < 7;
	}
	if ( ok ) ok = cnt < 7;
	puts(ok? "NO":"YES");
	return 0;
}
