#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<climits>
#include<cmath>
#include<algorithm>
#define all( x )  x.begin() , x.end()
#define X first
#define Y second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > point;
typedef pair< double , int > node;

const int MAXS = 250;

int N,M;
map<point, int> H;
int segment[ MAXS ][ 2 ];
vector<int> rev[ 2*MAXS ];
int cnt[ 2 * MAXS ];
point P[ 2*MAXS ];
bool isvertex[ 2*MAXS ];
double D[2*MAXS][2*MAXS];
bool G[2*MAXS][2*MAXS];
int pre[2*MAXS];
vector<int> id_col[MAXS];
int base;
int start, fin;

int get_id( const point &p ){
	if ( H.find(p) == H.end() ){
		P[N] = p;
		return H[p] = N++;
	}
	return H[p];
}

bool cmp( const int &i, const int &j ){
	return D[base][i] < D[base][j];
}

bool colinear( int i, int j, int k ){
	return (P[j].X-P[i].X)*(P[k].Y-P[i].Y) -  
		   (P[k].X-P[i].X)*(P[j].Y-P[i].Y) == 0; 
}

bool inside( int &i, int &j, int &k ){
	if ( !colinear( i, j, k ) ) return false;
	return min( P[i].X, P[j].X ) <= P[k].X && P[k].X <= max( P[i].X, P[j].X ) &&
 		   min( P[i].Y, P[j].Y ) <= P[k].Y && P[k].Y <= max( P[i].Y, P[j].Y );
}

int dist2( int i, int j ){
	return  (P[i].X - P[j].X)*(P[i].X - P[j].X) + 
			(P[i].Y - P[j].Y)*(P[i].Y - P[j].Y);
}

int dot( int &i, int &j, int &k ){
	point A = point( P[j].X - P[i].X , P[j].Y - P[i].Y );
	point B = point( P[k].X - P[j].X , P[k].Y - P[j].Y );
	return A.X * B.X + A.Y*B.Y;
}

bool dijkstra(){
	priority_queue< node, vector<node>, greater<node> > q;
	double d[2*MAXS];
	bool vis[2*MAXS];
	for ( int i=0; i < N; ++i )
		d[i] = 1000000000, vis[i] = false, pre[i] = -1;
	
	d[start] = 0.0;
	q.push( node(d[start], start) );
	int u,v;
	double w;
	while ( !q.empty() ){
		u = q.top().second;
		w = q.top().first;
		q.pop();
		if ( vis[u] ) continue;
		if ( u == fin ) return true;
		vis[u] = true;
		for ( v=0; v < N; ++v ){
			if ( G[u][v] && (d[v] > d[u] + D[u][v]) ){
				d[v] = d[u] + D[u][v];
				pre[v] = u;
				q.push( node( d[v] , v ) );
			}
		}
	}
	return false;
}

void print_ans( int u ){
	if ( u != start )
		print_ans( pre[u] );
	printf("%d %d\n", P[u].X, P[u].Y);
}

int main(){
	point s,e;
	while ( scanf("%d", &M) && M ){
		H.clear(); N = 0;
		scanf("%d %d %d %d", &s.X, &s.Y, &e.X, &e.Y);
		start = get_id( s );
		fin = get_id( e );
		
		for ( int i=0; i < M; ++i ){
			id_col[i].clear();
			scanf("%d %d %d %d", &s.X, &s.Y, &e.X, &e.Y);
			segment[i][0] = get_id( s );
			segment[i][1] = get_id( e );
		}
		// Counting for each point in how many segs it appears (it det. the vertices)
		for ( int i=0; i < N; ++i ){
			isvertex[i] = false;
			cnt[i] = 0;	
			rev[i].clear();
			for ( int j=0; j < M; ++j ){
				if ( segment[j][0] == i || segment[j][1] == i || 
					 inside( segment[j][0], segment[j][1], i ) ){
					id_col[j].push_back( i );					
					cnt[i]++;
					if ( segment[j][0] == i || segment[j][1] == i )
						rev[i].push_back(j);
				}
			}
		}
		// Determine the vertices
		for ( int i=0; i < M; ++i ){
			if ( cnt[ segment[i][0] ] > 1 && cnt[ segment[i][1] ] > 1 ){
				isvertex[ segment[i][0] ] = true;
				isvertex[ segment[i][1] ] = true;
			}
		}
		// Calculate distances
		for (int i=0; i < N; ++i){
			D[i][i] = 0.0; 
			G[i][i] = false;
			for ( int j=i+1; j < N; ++j ){
				D[i][j] = D[j][i] = sqrt(dist2( i , j ));
				G[i][j] = G[j][i] = false;
			}
		}
		// Create the graph
		int a,b, ang, s;
		bool l, r;
		int idx;
		for ( int i=0; i < M; ++i ){
			if ( isvertex[ segment[i][0] ] && isvertex[ segment[i][1] ] ){
				base = segment[i][0];		
				sort( id_col[i].begin(), id_col[i].end(), cmp );
				idx = 0;
				a = id_col[i][idx];	
				while ( a != segment[i][1] ){
					l = r = false;
					idx++;
					b = id_col[i][idx];
					while ( !isvertex[b] ){
						for ( int j=0; j < (int)rev[b].size(); ++j ){
							s = rev[b][j];
							if ( segment[s][0] == b ){
								ang = dot( a , b , segment[s][1] );	
							}
							else {
								ang = dot( a , b , segment[s][0] );
							}
							if (ang == 0) r = l = true;
							else if ( ang < 0 ) r = true;
							else l = true;
						}
						idx++;
						b = id_col[i][idx];
					}
					G[a][b] = G[b][a] = true;
					if ( l ) G[a][b] = false;
					if ( r ) G[b][a] = false;
					a = b;
				}
			}
		}
		// Find shortest path
		if (dijkstra()){
			print_ans( fin );
			puts("0");
		}
		else
			puts("-1");
	}
	return 0;
}

