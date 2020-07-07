#include<cstdio>
#include<map>
#include<queue>
#include<cctype>
#include<algorithm>
using namespace std;
typedef pair<int,int> pii;
const int MAXN = 16;

int N;
int R, C;
int L;

char M[MAXN][MAXN];
int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};

struct state {
	pii V[4];
	
	state(){}
	void set( pii A[] ){
		for ( int i=0; i < N; ++i )
			V[i] = A[i];
	}
	void set( const pii &e, const int &idx ){
		V[idx] = e;
	}
	void normalize(){
		sort( V + 1, V + N );
	}
	pii get( const int &idx ){
		return V[idx];
	}
	bool operator<( const state &S ) const {
		for ( int i=0; i < N; ++i )
			if ( V[i] != S.V[i] ) return V[i] < S.V[i];
		return false;
	}
};

map< state, int > D;
queue<state> Q;

pii next_pos( const pii &p, const int &dir ){
	int i = p.first, j = p.second;
	while ( M[i + dx[dir]][j + dy[dir]] != 'W' ){
		i += dx[dir];
		j += dy[dir];
	}
	return pii(i , j);
}

void process(){
	scanf("%d %d %d", &C, &R, &L);
	for ( int i=1; i <= R; ++i )
		scanf("%s", &M[i][1]);
	// Pad the borders of the matrix
	for ( int i=0; i <= R+1; ++i )
		M[i][0] = M[i][C + 1] = 'W';
	for ( int j=0; j <= C + 1; ++j )
		M[0][j] = M[R + 1][j] = 'W';
		
	pii A[4];
	pii end;
	int idx;

	for ( int i=1; i <= R; ++i )
		for ( int j=1; j <= C; ++j ){
			if ( isdigit( M[i][j] ) ){
				idx = M[i][j] - '0';
				idx--;
				M[i][j] = '.';
				A[idx] = pii( i, j );
			}
			else if ( M[i][j] == 'X' ){
				end = pii( i, j );
				M[i][j] = '.';
			}
		}
	
	sort( A + 1, A + N );
	
	state start;
	state act;
	state nxt;
	pii one, tmp;
	int d;

	start.set( A );
	D[ start ] = 0;
	Q.push( start );
	bool found = false;

	while ( !Q.empty() ){
		act = Q.front();	
		Q.pop();
		one = act.get(0);
		d = D[act];

		if ( one.first == end.first && one.second == end.second ){
			found = true;
			printf("%d\n", D[ act ]);
			break;
		}
		if ( d >= L ) continue;

		for ( int i=0; i < N; ++i ){
			A[i] = act.V[i];
			M[ A[i].first ][ A[i].second ] = 'W';
		}

		for ( int i=0; i < N; ++i ){
			tmp = A[i];
			M[ tmp.first ][ tmp.second ] = '.';
			for ( int j=0; j < 4; ++j ){
				A[i] = next_pos( tmp, j );
				nxt.set( A );
				nxt.normalize();
				if ( D.find( nxt ) == D.end() ){
					D[nxt] = d + 1;
					Q.push( nxt );
				}
			}
			M[ tmp.first ][ tmp.second ] = 'W';
			A[i] = tmp;
		}
		for ( int i=0; i < N; ++i )
			M[ A[i].first ][ A[i].second ] = '.';			
	}
	if ( !found ) puts("NO SOLUTION");
	
	while ( !Q.empty() ) Q.pop();
	D.clear();
}

int main(){
	while ( scanf("%d", &N) == 1 )
		process();
	return 0;
}
