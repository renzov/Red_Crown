#include<algorithm>
#include<cstdio>
#include<climits>
using namespace std;

const int MAXN = 505;

int G[MAXN][MAXN];
int D[2*MAXN][MAXN];
int size[2*MAXN];

int bs( int L, int U, int a[], int n ){
	if ( n == 1 ){
		return a[0] >= L && a[0] <= U;
	}
	if ( U < a[0] || L > a[n-1] ) return 0;
	int left,right;
	int l,m,r;	
	if ( L <= a[0] ){
		left = 0;
	}
	else {
		l = 0;
		r = n-1;
		while ( (r-l) > 1 ){
			m = (l+r) >> 1;
			if ( a[m] < L ) l = m;
			else r = m;
		}
		left = r;
	}

	if ( a[left] > U ) return 0;

	if ( a[n-1] <= U ){
		right = n-1;
	}
	else {
		l = left;
		r = n-1;
		while ( (r-l) > 1 ){
			m = (l+r) >> 1;
			if ( a[m] > U ) r = m;
			else l = m;
		}
		right = l;
	}

	if ( a[right] < L ) return 0;

	return (right - left + 1);
}


int main(){
	int N,M,Q,L,U;

	while ( scanf("%d %d",&N,&M) && M && N ){
		for ( int i=0; i < N; i++ )
			for ( int j=0; j < M; ++j ){
				scanf("%d",&G[i][j]);			
			}
		int d = 0;
		int j,k;
		for ( int i=M-1; i >= 0 ; --i){
			for ( j=0,k=i; k < M && j < N ; ++j, ++k ){
				D[d][j] = G[j][k]; 
			}
			size[d] = j;
			d++;
		}
		for ( int i=1; i < N ; ++i ){
			for ( j=0,k=i; k < N && j < M; ++j, ++k ){
				D[d][j] = G[k][j]; 
			}
			size[d] = j;
			d++;
		}
		//Process Queries
		scanf("%d",&Q);
		int best;
		while (Q--){
			scanf("%d %d",&L,&U);
			//printf("%d %d\n",L,U);			
			best = 0;
			for ( int i=0; i < d ; ++i ){			
				if ( best < size[i] )				
					best = max( best, bs( L , U , D[i] , size[i] ) );
			}
			printf("%d\n",best);			
		}
		puts("-");
	}
	return 0;
}
