#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX = 200;
int T[MAX][MAX]; //Mininum time needed for firefighter i to reach fire j (rounded to ceil) 
int H, F, V; 
int maxT;
bool seen[MAX];
int limit;
int hole[MAX];

int time_needed( int X1, int Y1 , int X2 , int Y2 ){
	double d = sqrt( (X1-X2)*(X1-X2)*1.0 + (Y1-Y2)*(Y1-Y2)*1.0 );
	return (int)ceil(d/V);
}

bool alternate( int u ){
	if ( seen[u] ) return false;
	seen[u] = true;
	for ( int v = 0 ; v < F; ++v ){
		if ( T[u][v] <= limit && ( hole[v] < 0 || alternate( hole[v] ) ) ){
			hole[v] = u;
			return true; 
		}
	}
	return false;
}

int bpm(){
	int cnt = 0;
	for ( int i=0; i < H; ++i ){
		fill( seen , seen + F , false );
		if ( alternate(i) ) cnt++;
	}
	return cnt;
}

void init(){
	fill( hole , hole + F , -1 );
}

int process(){
	//Case all is reacheable in 0 sec.
	limit = 0;
	init();
	if ( bpm() == H ) return 0;
	int m;
	int l = 0;
	int r = maxT;
	while ( (r - l) > 1 ){
		m = ( l + r ) >> 1;
		limit = m;
		init();
		if ( bpm() == H ){
			r = m;
		}
		else {
			l = m;
		}
	}
	return r;
}

void read_input(){
	int X[MAX];
	int Y[MAX];
	int x,y;
	for ( int i=0; i < H; ++i )
		scanf("%d%d",X+i,Y+i);
	maxT = 0;
	for ( int j=0; j < F; ++j ){
		scanf("%d%d",&x,&y);
		for ( int i=0; i < H; ++i ){
			T[i][j] = time_needed( X[i] , Y[i] , x , y );
			maxT = max( maxT , T[i][j] );
		}
	}
}

int main(){
	int res;
	while ( scanf("%d%d%d",&H,&F,&V) && H && F && V ){
		read_input();
		res = process();
		printf("%d\n",res);	
	}
	return 0;
}
