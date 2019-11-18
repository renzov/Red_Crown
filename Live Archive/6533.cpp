#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXN = 64;
int N;
vector<long long> L[MAXN];

void process(){
	long long l;
	for ( int i=0; i < N; ++i ){
		scanf("%lld", &l);
		L[l].push_back(-1);
	}	
	long long Mx = 1;
	for ( int i=N; i > 0; --i ){
		if ( (int)L[i].size() ){
			for ( int j=0; j < L[i].size(); ++j )
				if ( L[i][j] == -1 )
					L[i][j] = Mx;
			for ( int j=0; (j + 1) < (int)L[i].size(); j += 2 ){
				L[ i  - 1 ].push_back( L[i][j] + L[i][j+1] );
			}
			Mx = *max_element( L[i].begin(), L[i].end() );
		}
	}
	printf("%lld\n", L[0][0]);
	for ( int i=0; i <= N; ++i ) 
		L[i].clear();
}

int main(){
	while ( scanf("%d", &N) == 1 ) 
		process();
	return 0;
}
