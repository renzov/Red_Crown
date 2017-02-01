#include<cstdio>
#include<cstring>

const int NN = 25;
const int INF = 100000;

int cap[NN][NN];
// flow network
int fnet[NN][NN];
// BFS
int q[NN], qf, qb, prev[NN];

inline int min( int x,int y ){ return x <= y? x:y; }

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
		  if ( flow >= INF ) break;
        // find an augmenting path
        memset( prev, -1, sizeof( prev ) );
        qf = qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prev[q[qb++] = v] = u;
        // see if we're done
        if( prev[t] == -1 ) break;
        // get the bottleneck capacity
        int bot = INF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            bot = min( bot , cap[u][v] - fnet[u][v] + fnet[v][u] );
        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;
        flow += bot;
    }
    return flow;
}

//----------------- EXAMPLE USAGE -----------------
int main()
{
    char s[10];
	 int n,m,len;
	 int runs;
	 int v;
	 scanf("%d",&runs);
	 while ( runs-- ){
		 memset( cap, 0, sizeof( cap ) );
		 scanf("%d %d",&n,&m);
		 for ( int u=0; u < n; ++u ){
			 scanf("%s %d",s,&len);
			 if ( s[0] == 'I' ) cap[n][u] = INF;
			 for ( int j=0; j < len; ++j ){
				scanf("%d",&v);
				cap[u][v] += INF;
				cap[v][u] += 1;
				cap[u][v] = min( INF , cap[u][v] ); cap[v][u] = min( INF , cap[v][u] );
			 }
		 }
		 int res = fordFulkerson( n + 1, n, m );
		 if ( res >= INF ) printf("PANIC ROOM BREACH\n");
		 else printf("%d\n",res);
	 }
    return 0;
}