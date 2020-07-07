#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int MAXN = 5005;
int A, B;
char S[MAXN];


void process(){
	scanf("%s", S);
	int N = strlen(S);
	int b = 0, w = 0;
	for ( int i=0; i < N; ++i ){
		if ( S[i] == 'B' ){
			b++;
		}
		else {
			w++;
		}
	}
	
	vector<int> posW;
	vector<int> posB;
	for ( int i=0; i < N; ++i ){
		if ( S[i] == 'W' && i < b )
			posW.push_back(i);
		else if ( S[i] == 'B' && i >= b )
			posB.push_back(i);
	}
	
	
	int res = A * posW.size();
	int pW = posW.size() - 1;
	int pB = 0;
	int nswaps;
	while ( pW >= 0 ){
		nswaps = posB[pB] - posW[pW];
		if ( nswaps * ( A - B ) >= A ) break;
		res -= A;
		res += nswaps * ( A - B );
		pW--;
		pB++;
	}
	printf("%d\n", res);
}

int main(){
	while ( scanf("%d %d", &A, &B) == 2 )
		process();
	return 0;
}
