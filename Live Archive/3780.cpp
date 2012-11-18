#include<cstdio>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
const int MAXV = 500;
const int MAXE = 200000;
const int INF = INT_MAX;
int n,M,m;
int type[MAXV];

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

void add( int u , int v , int c ){
	to[m] = v, flow[m] = 0, cap[m] = c, next[m] = head[u], head[u] = m, m++;
	to[m] = u, flow[m] = c, cap[m] = c, next[m] = head[v], head[v] = m, m++;
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
	while ( f=augment_path( s , t ) )
		maxFlow += f;
	return maxFlow;
}


void read_input(){
	int u,v;
	for ( int i=1; i <= n; ++i ){
		scanf("%d",type+i);
		if ( type[i] ) add( 0 , i , 1 );
		else add( i , n+1 , 1 );
	}
	for ( int i=0; i < M; ++i ){
		scanf("%d%d",&u,&v);
		add( u , v , 1 );
		add( v , u , 1 );
	}
	n += 2;
}

int main(){
	int sink;
	while ( scanf("%d%d",&n,&M) && n ){
		m = 0;
		fill( head , head + MAXV , -1 );
		sink = n + 1;
		read_input();
		printf("%d\n",Edmonds_Karp(0,sink));
	}
	return 0;
}
