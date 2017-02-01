#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define mp(x,y) make_pair((x),(y))
struct block {
	int x,y,z;
	block(){}
	block(int X,int Y,int Z){ x = X; y = Y; z = Z; }
};
block a[15][3];
vector< pair<int,int> > G[15][3];
int d[15][3][1<<15];

void dfs( int i , int k, int mask ){
	int maxi = 0;
	int j,l;
	int mask2;
	for ( int t=0; t < G[i][k].size() ; ++t ){
		j = G[i][k][t].first;
		l = G[i][k][t].second;
		if ( (mask >> j)&1 ) continue;
		mask2 = mask | ( 1<<i );
		if ( d[j][l][mask2] == -1 )
			dfs( j , l , mask2 );
		maxi = max( maxi , d[j][l][mask2] );
	}
	d[i][k][mask] = maxi + a[i][k].z;
}

inline bool pode( int i , int k , int j , int l ){
	return a[i][k].x >= a[j][l].x && a[i][k].y >= a[j][l].y;
}

int main(){
	int x,y,z;	
	int n;
	int m;
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		scanf("%d",&n);
		for (int i=0; i < n; ++i){
			scanf("%d %d %d",&x,&y,&z);
			a[i][0] = block( min(x,y) , max(x,y) , z );
			a[i][1] = block( min(x,z) , max(x,z) , y );
			a[i][2] = block( min(y,z) , max(y,z) , x );
		}
		for ( int i=0; i < n; ++i )
			for ( int k=0; k < 3; ++k ){
				G[i][k].clear();
				for ( int mask = 0; mask < (1<<n) ; ++mask )
					d[i][k][mask] = -1;
			}
		//Create the DAG
		for ( int i=0; i < (n-1); ++i )
			for ( int k=0; k < 3; k++ )
				for ( int j=i+1; j < n; ++j )
					for ( int l=0; l < 3; ++l ){
						if ( pode(i,k,j,l) )
							G[i][k].push_back(mp(j,l));
						if ( pode(j,l,i,k) )
							G[j][l].push_back(mp(i,k));
					}
		int res = 0;
		for ( int i=0; i < n; ++i ){
			for ( int k=0; k < 3; ++k ){
				if ( d[i][k][0] == -1 )
					dfs( i , k , 0 );
				res = max(d[i][k][0],res);
			}
		}	
		printf("%d\n",res);
	}

	return 0;
}

