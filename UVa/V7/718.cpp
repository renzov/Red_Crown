#include<cstdio>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;

bool G[105][105];
int X[105];
int Y[105];
int d[105];
bool reachB[105];
int F,E,A,B;

struct triple{
	int x,y,d;
	triple(){}
	triple(int q,int w,int e) : d( q ), x( w ), y( e ){}
};

triple egcd(int a,int b){
    if( !b ) return triple( a, 1 , 0 );
    triple q = egcd( b, a % b );
    return triple( q.d, q.y, q.x - a / b * q.y );
}

triple diophantine(int a,int b,int c){
	triple t = egcd(a,b);
	if (c % t.d) return triple(0,0,0);
	t.x *= (c/t.d);
	t.y *= (c/t.d);
	return t;
}

bool connected(int a,int b){
	int A = X[a];
	int B = X[b];
	int C = Y[b] - Y[a];
	triple t = diophantine(A,B,C);
	if (t.d == 0) return false;
}

bool can_reach(int a,int f){
	if (f < Y[a]) return false;
	return !((f-Y[a])%X[a]);
}


int gcd (int a, int b, int & x, int & y) {
  if (a == 0) {
	 x = 0; y = 1; 
	 return b;
  }
  int q = b / abs(a);
  if (a < 0) q*=-1;
  int m = b - a*q;
  int x1, y1; int d = gcd ( m , a, x1, y1); 
  x = y1 - (b / a) * x1; 
  y = x1; 
  return d;
}

int main(){

	int runs;
	int x,y;
	int d = gcd(-7,13,x,y);
	if (d < 0) x*=-1,y*=-1,d*=-1;
	//triple t = diophantine(13,-7,21);
	printf("%d %d %d\n",x,y,d);
	/*scanf("%d",&runs);
	while (runs--){
		scanf("%d %d %d %d",&F,&E,&A,&B);
		for (int i=0; i < E; ++i){
			scanf("%d %d",&X[i],&Y[i]);
		}
		for (int i=0; i < E; ++i){
			G[i][i] = false;
			reachB[i] = false;			
			d[i] = -1;			
			for (int j=i+1; j < E; ++j)
				G[i][j] = G[j][i] = false;
		}
		for (int i=0; i < E; ++i)
			for (int j=i+1; j < E; ++j)
				if (connected(i,j)) 
					G[i][j] = G[j][i] = true;
		queue<int> q;		
		for (int i=0; i < E; ++i){
			if  (can_reach(i,A)){ q.push(i); d[i] = 0; }
			if  (can_reach(i,B)) reachB[i] = true;		
		}
		int u,v;
		while (!q.empty()){
			u = q.front();
			q.pop();
			if (reachB[u]){ d[B] = d[u]; break; }
			for (v=0; v < E; ++v){ 
				if (v!=u && G[u][v]){
					q.push(v);
					d[v] = d[u] + 1;
				}
			}
		}
		if (d[B] != -1) puts("It is possible to move the furniture.");
		else puts("The furniture cannot be moved.");
	}
	*/
	return 0;
}
