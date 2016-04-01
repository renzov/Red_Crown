#include<cstdio>
#include<cassert>
#include<algorithm>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

const int MAXN = 100005;
const int MAXV = 21 * MAXN;

int A[MAXN];
int B[MAXN];
int ord[MAXN];
int rev[MAXN];

struct Query {
	char type;
	int x, y, z;
	Query (char t, int X, int Y, int Z){
		type = t, x = X, y = Y, z = Z;
	}
	Query (){}
};

Query q[ 35001 ];

bool cmp( const int &i , const int &j ){
	return A[i] < A[j];
}

struct node {
	int L, R, sum;
	node( int l, int r, int S ){
		L = l, R = r, sum = S;
	}
	node(){}
};

node MEM[ MAXV ];
int root[ MAXN ];
int cur_node;

int insert( const int &vertex, int L , int R, int p ){
	if ( L <= p && p <= R  ){
		if ( L == R ){
			MEM[cur_node] = node(0,0,1);
			return cur_node++;
		}
		int res = cur_node++;
		int M = ( L + R ) >> 1;
		MEM[res].L = insert( MEM[vertex].L , L , M , p );
		MEM[res].R = insert( MEM[vertex].R , M + 1 , R , p );
		MEM[res].sum = MEM[vertex].sum + 1;
		return res;
	}
	return vertex;
}

int query( const int &v , const int &u, int L, int R, int k  ){
	if ( L==R ) return L;
	int M = (L+R) >> 1;
	int s = MEM[ MEM[v].L ].sum - MEM[ MEM[u].L ].sum;
	if ( k <= s )
		return query( MEM[v].L , MEM[u].L , L , M , k );
	else 
		return query( MEM[v].R , MEM[u].R , M + 1, R , k - s );
}

int query2( const int &v, int L, int R, int l, int r ){
	if ( l==L && r == R ) return MEM[v].sum;
	int M = ( L + R ) >> 1;
	if ( r <= M ) return query2( MEM[v].L , L , M , l , r );
	if ( l > M ) return query2( MEM[v].R , M + 1, R , l , r );
	return query2(MEM[v].L, L, M, l, M) + query2(MEM[v].R, M+1, R, M+1, r);
}

int main(){
	int M;
	int N;
	int Q;
	int l,r,k;
	char s[10];
	int cases = 0;
	int sum1, sum2, sum3 = 0;

	while ( scanf("%d", &M) != EOF ){
		cases++;
		Q = N = 0;
		for ( int i=0; i < M; ++i ){
			scanf("%s", s);
			if ( s[0] == 'I' ){
				scanf("%d", A + i );
				ord[i] = i;
				N++;
			}
			else if ( s[6] == '1' ){ //Query 1
				scanf("%d %d %d", &l ,&r, &k);
				q[ Q++ ] = Query( s[6] , l - 1, r - 1, k );
			}
			else if ( s[6] == '2' ){ //Query 2
				scanf("%d", &l);
				q[Q++] = Query(s[6], l , N , -1 );
			}
			else {	//Query 3
				scanf("%d", &l);
				q[Q++] = Query(s[6], l , N, -1 );
			}
		}
		sort( ord, ord + N, cmp );
		for ( int i=0; i < N; ++i ) B[i] = A[ord[i]], rev[ ord[i] ] = i;
		
		sum1 = sum2 = sum3 = 0;
		MEM[0].L = MEM[0].R = MEM[0].sum = 0;
		cur_node = 1;

		for ( int i=0; i < N; ++i ){
			root[ i ] = insert( (i)? root[i-1]:0 , 0, N-1, rev[i] );		
		}
		int res, pos;
		for ( int i=0; i < Q; ++i ){
			Query &p = q[i];
			switch (p.type){
				case '1' : 	res = query( root[ p.y ] , root[ (p.x)? (p.x-1):0 ] , 0 , N-1 , p.z ); 
							break;
				case '2' : 	pos = lower_bound( B , B + N , p.x ) - B;
						   	res = query2( root[ p.y - 1 ] , 0 , N - 1 , 0 , pos  ); 
						   	break;
				case '3' : 	res = query( root[ p.y - 1 ] , 0 , 0 , N - 1 , p.x ); 
						   	break;
			}
		}

	}
	return 0;
}

