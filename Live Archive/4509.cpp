#include<cstdio>
#include<climits>
const int GRASS = -2;
const int GRAVE = -1;
int M[35][35];

struct triple {
  int x,y,w;
  triple(){}
  triple(int X,int Y,int W){ x = X,y = Y, w = W; }
};

triple Hole[30*30 + 2];
int d[35][35];

void init( int W , int H ){
	for ( int i=0; i < H; ++i )
		 for ( int j=0; j < W; ++j ){
			 M[i][j] = GRASS;
			 d[i][j] = INT_MAX;
		 }
}

int main(){
  int W,H;
  int m,n;
  int x,y,w;
  int nx,ny;
  while ( scanf("%d %d",&W,&H) && W ){
	 init( W , H );
	 scanf("%d",&m);
	 for ( int i=0; i < m; ++i ){
		scanf("%d %d",&x,&y);
		M[y][x] = GRAVE;
	 }
	 scanf("%d",&m);
	 for ( int i=0; i < m; ++i ){
		scanf("%d %d %d %d %d",&x,&y,&nx,&ny,&w);
		M[y][x] = i;
		Hole[i].x = nx; Hole[i].y = ny; Hole[i].w = w;
	 }
	 n = W*H;
	 d[0][0] = 0;
	 //Bellman Ford
	 for ( int k=0; k < n-1; ++k ){
		for ( int i=0; i < H; ++i){
		  for ( int j=0; j < W; ++j ){
				if ( i==(H-1) && j==(W-1) ) continue;
				if ( M[i][j] != GRAVE && d[i][j] != INT_MAX ){
					 if ( M[i][j] != GRASS ){
						nx = Hole[ M[i][j] ].x; ny = Hole[ M[i][j] ].y; w = Hole[ M[i][j] ].w;
						if ( d[ny][nx] > (d[i][j] + w) ) d[ny][nx] = d[i][j] + w;
					 }
					 else {
						if ( j + 1 < W && M[i][j+1] != GRAVE && (d[i][j+1] > (d[i][j] + 1)) ) d[i][j+1] = d[i][j] + 1;
						if ( j > 0 && M[i][j-1] != GRAVE && (d[i][j-1] > (d[i][j] + 1)) ) d[i][j-1] = d[i][j] + 1;
						if ( i + 1 < H && M[i+1][j] != GRAVE && (d[i+1][j] > (d[i][j] + 1)) ) d[i+1][j] = d[i][j] + 1;
						if ( i > 0 && M[i-1][j] != GRAVE && (d[i-1][j] > (d[i][j] + 1)) ) d[i-1][j] = d[i][j] + 1;
					 }
				}
		  }
		}
	 }

	 bool neg = false;
	 for ( int i=0; i < H && !neg; ++i){
		  for ( int j=0; j < W && !neg; ++j ){
				if ( i==(H-1) && j==(W-1) ) continue;
				if ( M[i][j] != GRAVE && d[i][j] != INT_MAX ){
					 if ( M[i][j] != GRASS ){
						nx = Hole[ M[i][j] ].x; ny = Hole[ M[i][j] ].y; w = Hole[ M[i][j] ].w;
						if ( d[ny][nx] > (d[i][j] + w) ) neg = true;
					 }
					 else {
						if ( j + 1 < W && M[i][j+1] != GRAVE && (d[i][j+1] > (d[i][j] + 1)) ) neg = true;;
						if ( j > 0 && M[i][j-1] != GRAVE && (d[i][j-1] > (d[i][j] + 1)) ) neg = true;;
						if ( i + 1 < H && M[i+1][j] != GRAVE && (d[i+1][j] > (d[i][j] + 1)) ) neg = true;;
						if ( i > 0 && M[i-1][j] != GRAVE && (d[i-1][j] > (d[i][j] + 1)) ) neg = true;
					 }
				}
		  }
	 }

	 if ( neg ) puts("Never");
	 else if ( d[H-1][W-1] >= INT_MAX ) puts("Impossible");
	 else printf("%d\n",d[H-1][W-1]);
  }
  return 0;
}