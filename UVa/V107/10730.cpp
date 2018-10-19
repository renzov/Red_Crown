#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 10005;
int A[MAXN];
int idx[MAXN];
int N;

bool isantiarith(){
	int maxD = N >> 1;
	int val;
	int cnt, act;
	for ( int diff = -maxD; diff <= maxD; ++diff ){
		for ( int i=0; i < N; i++ ){
			cnt = 0;
			act = i;
			while ( cnt < 2 ){	
				val = A[act] + diff;	
				if ( val < 0 || val >= N || idx[val] <= act ) break;
				cnt++; 
				act = idx[ val ];		
			}
			if ( cnt == 2 ) return false; 
		}
	}
	return true;
}

int main(){
	while ( scanf("%d", &N) && N ){
		getchar(); // reads :
		fill( idx, idx + N, -1 );
		for ( int i=0; i < N; ++i ){
			scanf("%d", A + i);
			idx[ A[i] ] = i;
		}
		if ( isantiarith() ) puts("yes");
		else puts("no");
	}
	return 0;
} 
