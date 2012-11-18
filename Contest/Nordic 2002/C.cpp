#include<cstdio>
#include<algorithm>
#include<climits>
using namespace std;
const int MAXE = 400000;
int B[1005];
int E[1005];
int n,m;
int M,P;

int q[2000];
int qt,qf;
int head[2000];
int to[MAXE];
int cap[MAXE];
int flow[MAXE];
int next[MAXE];
int used[2000];
int bneck[2000];
int visited[2000];

int augment_path(int s,int t){
	int u,v;
	int e,f;
	fill( visited , visited + n , false );
	qt =  qf = 0;	
	q[qt++] = s;
	bneck[s] = INT_MAX;
	used[s] = -1;  visited[s] = true;
	while ( qf < qt ){
		u = q[qf++];
		if ( u == t ){
			f = bneck[t];
			while ( u != s ){
				e = used[u];
				flow[e] += f; flow[e^1] -= f;
				u = to[e^1];
			}
			return f;
		}
		for ( e = head[u]; e >= 0 ; e=next[e] ){
			v = to[e];
			if ( !visited[v] && flow[e] < cap[e] ){
				visited[v] = true;
				q[qt++] = v;
				bneck[v] = min( bneck[u] , cap[e] - flow[e] );
				used[v] = e;
			}
		}
	}
	return 0;
}

void add( int u , int v, int c ){
	to[m] = v, next[m] = head[u], cap[m] = c, flow[m] = 0, head[u] = m++;
	to[m] = u, next[m] = head[v], cap[m] = c, flow[m] = c, head[v] = m++;
}

int Edmonds_Karp( int s , int t ){
	int maxFlow = 0;
	int f;
	while ( f=augment_path(s,t) ) maxFlow += f;
	return maxFlow;
}

int main(){
	
	int runs;
	int s,t;
	scanf("%d",&runs);
	while ( runs-- ){
		s = 0;
		scanf("%d %d",&M,&P);
		n = M + 105; t = M + 101;
		fill( head, head + n, -1 );
		m = 0;
		// Adding the pianos to the source
		for ( int i=1; i <= M ; ++i ) add( s , i , 1 );		
		// Put the restriction of max number of pianos to carry in a day
		for ( int i=1; i <= 100; ++i ){ add( M + i , t , (P>>1) );  }
		//Adding arc to represent possible days of transport
		for ( int i=1; i <= M; ++i ){
			scanf("%d %d",B+i,E+i);
			for ( int j=B[i]; j <= E[i]; ++j ){
				if ( (j % 7) != 0 && ( j % 7 ) != 6 ){
					add( i , M + j , 1 );
				}
			}
		}
		if ( Edmonds_Karp(s,t) == M ) puts("fine");
		else {
			//Reset flow ---
			for ( int i=0; i < m; ++i ){
				if ( i & 1 ) flow[i] = cap[m];
				else flow[i] = 0;
			}
			for ( int j=6; j <= 100; j+= 7 ){
				for ( int i=1; i <= M; ++i ){
					if ( B[i] <= j && j <= E[i] ){ add( i , M + j , 1 ); }
					if ( (j+1) <= 100 && B[i] <= (j+1) && (j+1) <= E[i] ){ add( i , M + j + 1 , 1 ); }
				}
			}
			if ( Edmonds_Karp( s , t ) == M ) puts("weekend work");
			else puts("serious trouble");
		}
	}
	return 0;
}
