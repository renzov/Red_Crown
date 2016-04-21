#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXN = 100005;

int Y[MAXN];
int U[MAXN];
int rev[MAXN];
// Segment trees for the sums
int cntE[4*MAXN];
int cntB[4*MAXN];
int sumE[4*MAXN];
int sumB[4*MAXN];
// For the union find
int p[MAXN];
int rnk[MAXN];
int Left[MAXN];
int Right[MAXN];
int size[MAXN];

inline int find_set( int x ){ return (x==p[x])? x:(p[x]=find_set(p[x])); }

void incBegin( int node, int L, int R, int pos, int val ){
	sumB[node] += val;
	if (val > 0) cntB[node]++;
	if (val < 0) cntB[node]--;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M ) incBegin( node<<1, L, M, pos, val );
	else incBegin( (node<<1)|1, M+1, R, pos, val);
}

void incEnd( int node, int L, int R, int pos, int val ){
	sumE[node] += val;
	if ( val > 0 ) cntE[node]++;
	if ( val < 0 ) cntE[node]--;
	if ( L == R ) return;
	int M = ( L + R ) >> 1;
	if ( pos <= M ) incEnd( node<<1, L, M, pos, val );
	else incEnd( (node<<1)|1, M+1, R, pos, val);
}

pii queryE(int node, int L, int R, int l,int r){
	if ( l==L && r==R ) return pii(cntE[node],sumE[node]);
	int M = ( L + R ) >> 1;
	if ( r <= M ) return queryE( node<<1, L, M, l, r );
	if ( l > M ) return queryE( (node<<1)|1, M+1, R, l, r );
	pii res1 = queryE(node<<1, L , M, l , M);
	pii res2 = queryE((node<<1)|1, M+1, R, M+1, r);
	return pii( res1.first + res2.first , res1.second + res2.second );
}

pii queryB(int node, int L, int R, int l,int r){
	if ( l==L && r==R ) return pii(cntB[node],sumB[node]);
	int M = ( L + R ) >> 1;
	if ( r <= M ) return queryB( node<<1, L, M, l, r );
	if ( l > M ) return queryB( (node<<1)|1, M+1, R, l, r );
	pii res1 = queryB(node<<1, L , M, l , M);
	pii res2 = queryB((node<<1)|1, M+1, R, M+1, r);
	return pii( res1.first + res2.first , res1.second + res2.second );
}


int link_set( int x, int y ){
	if ( rnk[x] > rnk[y] ){
		p[y] = x, size[x] += size[y]; 
		if (Left[x] > Left[y] ) Left[x] = Left[y];
		if (Right[x] < Right[y] ) Right[x] = Right[y];	
		return x;
	}
	else if ( rnk[y] > rnk[x] ){
		p[x] = y, size[y] += size[x];
		if (Left[y] > Left[x] ) Left[y] = Left[x];
		if (Right[y] < Right[x] ) Right[y] = Right[x];
		return y;
	}
	p[y] = x, rnk[x]++, size[x] += size[y]; 
	if (Left[x] > Left[y] ) Left[x] = Left[y];
	if (Right[x] < Right[y] ) Right[x] = Right[y];	
	return x;		
}

int main(){
	int runs;
	int N, M;
	int x,y;
	int S;
	char cmd[10];

	scanf("%d", &runs);
	while (runs--){
		scanf("%d", &N);
		for ( int i=0; i < N; ++i ){
			scanf("%d %d", &x, Y + i );
			U[i] = Y[i];
		}
		sort( U, U + N );
		S = unique( U , U + N ) - U;
		// init segment trees
		for ( int i=0; i < 4*S; ++i ) cntE[i] = cntB[i] = sumE[i] = sumB[i] = 0;
		// compress coord
		for ( int i=0; i < N; ++i ){
			rev[i] = lower_bound( U, U + S, Y[i] ) - U;
			// init union find
			p[i] = i, rnk[i] = size[i] = 1;
			Left[i] = Right[i] = rev[i];
			//update trees
			incBegin( 1, 0, S-1, rev[i] , 1 );
			incEnd( 1 , 0, S-1, rev[i] , 1  );
		}
		//process the queries
		scanf("%d", &M);
		int comp = N; //Number of current components
		pii res1, res2;
		while ( M-- ){
			scanf("%s", cmd);
			if ( cmd[0] == 'r' ){
				scanf("%d %d", &x, &y);
				if ( (x=find_set(x)) == (y=find_set(y)) ) continue;
				// Undo info in segment trees
				incBegin( 1, 0, S-1, Left[x], -size[x] );
				incBegin( 1, 0, S-1, Left[y], -size[y] );
				incEnd( 1, 0, S-1, Right[x], -size[x] ); 
				incEnd( 1, 0, S-1, Right[y], -size[y] );
				// Insert new information
				x = link_set( x, y );
				comp--;
				incBegin( 1, 0, S-1, Left[x], size[x] ); 
				incEnd( 1, 0, S-1, Right[x], size[x] );
			}
			else { // query
				scanf("%d.%d", &x, &y);
				y = lower_bound( U, U + S, x ) - U;
				if ( y == S || x < U[0] ){
					puts("0 0");
				}
				else if ( x < U[y] ){
					res1 = (y > 0)? queryE( 1, 0, S-1, 0, y-1 ):pii(0,0);
					res2 = queryB( 1, 0, S-1, y, S-1);
					printf("%d %d\n", comp - res1.first - res2.first, N - res1.second - res2.second );
				}
				else { // x == U[y]
					res1 = queryE( 1, 0, S-1, 0, y );
					res2 = (y < (S-1))? queryB( 1, 0, S-1, y + 1, S-1 ):pii(0,0);
					printf("%d %d\n", comp - res1.first - res2.first, N - res1.second - res2.second );					
				}	
			}
		}
	}
	return 0;
}

