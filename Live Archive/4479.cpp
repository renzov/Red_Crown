#include<cstdio>
#include<climits>
#include<algorithm>
using namespace std;
const int MATCH = 5;
const int TEAM = 41;
const int MAXE = 20000;
const int MAXV = 6500;
const int INF = INT_MAX;
int N,M,G;
int m;
int n;
int to[MAXE];
int flow[MAXE];
int cap[MAXE];
int next[MAXE];
int head[MAXV];

int used[MAXV];
int bneck[MAXV];
int q[MAXV];
int qf,qt;
bool visited[MAXV];

int left[TEAM][TEAM];
int point[TEAM];

void add( int u , int v , int c ){
	to[m] = v, flow[m] = 0, cap[m] = c, next[m] = head[u], head[u] = m, m++;
	to[m] = u, flow[m] = c, cap[m] = c, next[m] = head[v], head[v] = m, m++;
	if ( m > MAXE ) while(1);
}

int augment_path( int s, int t ){
	int u,v;
	int e;
	int f = 0;

	qf = qt = 0; //Initializing the queue
	q[ qt++ ] = s;
	bneck[s] = INF;
	
	fill( visited , visited + n , false );
	used[s] =  -1;
	visited[s] = true;
	while ( qf < qt ){
		u = q[qf++];
		if ( u==t ){
			f = bneck[t];
			while ( u != s ){
				e = used[u];
				flow[e] += f; flow[e^1] -= f;
				u = to[e^1];
			}
			return f;
		}
		for ( e = head[u]; e >= 0 ; e = next[e] ){
			v = to[e];
			if ( flow[e] < cap[e] && !visited[v] ){
				bneck[v] = min( bneck[u] , cap[e] - flow[e] );
				visited[v] = true;
				q[qt++] = v;
				used[v] = e;
			}
		}
	}
	return 0;
}

int Edmonds_Karp( int s , int t ){
	int maxFlow = 0;
	int f;
	//Getting the Max-Flow
	while ( f=augment_path( s , t ) ){
		maxFlow += f;
	}
	return maxFlow;
}


void read_input(){
	char s[3];
	int u,v;
	for ( int i=0; i < G ; ++i ){
		scanf("%d %s %d",&u,s,&v);
		left[min(u,v)][max(u,v)]--;
		if ( s[0] == '<' ){
			point[v] += 2;
		}
		else if ( s[0] == '>' ){
			point[u] += 2;
		}
		else {
			point[u]++,point[v]++;
		}
	}
}

bool process(){
	int maxPoint = point[0];
	for ( int j=1; j < N; ++j ){
		maxPoint += 2*left[0][j];
	}
	int src = 0;
	// team 1 to N-1 are nodes 1 ... N-1 in the network
	int lastNode = N;
	int begMatch = N; //to know where nodes representing matches begin
	int expected = 0;
	for ( int j=1; j < N; ++j )
		if ( (maxPoint-point[j]-1) < 0 ) return false;
		else { add( src , j , maxPoint-point[j]-1 ); }
	for ( int i=1; i < N; ++i ){
		for ( int j=i+1; j < N; ++j ){
			for ( int k=0; k < left[i][j]; ++k ){
				add( i , lastNode , 2 );
				add( j , lastNode , 2 ); lastNode++;
				expected += 2;
			}
		}
	}
	int sink = lastNode;
	n = sink + 1;
	if ( n > MAXV ) while(1);
	//create the match to sink nodes
	for ( int i=begMatch; i < sink ; ++i )
		add( i , sink , 2 );
	int res = Edmonds_Karp( src , sink );
	return res == expected;
}

void init(){
	m = 0;
	fill( point , point + N , 0 );
	fill( head , head + MAXV , -1 );
	for ( int i=0; i < N; ++i )
		for ( int j=i+1; j < N ; ++j )
			left[i][j] = M;
}

int main(){
	while ( scanf("%d%d%d",&N,&M,&G) && N ){
		init();
		read_input();
		if ( process() ) puts("Y");
		else puts("N");
	}
	return 0;
}

