#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;

#define M 101
#define N 101

bool graph[M][N];
bool seen[N];
int matchL[M], matchR[N];
int n, m;


struct point {
	double x,y;
};

inline double dist(const point &a,const point &b){
	return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool bpm( int u )
{
    for( int v = 0; v < n; v++ ) if( graph[u][v] )
    {
        if( seen[v] ) continue;
        seen[v] = true;

        if( matchR[v] < 0 || bpm( matchR[v] ) )
        {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

point g[M];
point h[N];

int main()
{
   double d,t;
	double s,v;
	
	while (scanf("%d %d %lf %lf",&m,&n,&s,&v) == 4){
		
		for (int i=0; i < m; ++i){
			scanf("%lf %lf",&g[i].x,&g[i].y);
		}
		
		for (int i=0; i < n; ++i){
			scanf("%lf %lf",&h[i].x,&h[i].y);
		}
		
		for (int i=0; i < m; ++i)
			for (int j=0; j < n; ++j){
				d = dist(g[i],h[j]);
				t = d/v;
				if (fabs(t-s) < 0.001 || t < s)
					graph[i][j] = true;
				else graph[i][j] = false;
			}
		
		memset( matchL, -1, sizeof( matchL ) );
		memset( matchR, -1, sizeof( matchR ) );
		int cnt = 0;
		for( int i = 0; i < m; i++ ){
			memset( seen, 0, sizeof( seen ) );
			if( bpm( i ) ) cnt++;
		}
		cout << m - cnt << endl;

	}
    
    return 0;
}
