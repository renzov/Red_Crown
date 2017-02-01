#include<cstdio>
#include<climits>
#include<cstring>

int r,c;
bool M[20][20];
bool t[20][20];
int dx[]={1,0,-1,0};
int dy[]={0,-1,0,1};

void tap(int y,int x){
  int i;
  int nx,ny;
  for (i=0; i < 4; ++i){
	 nx = x + dx[i];
	 ny = y + dy[i];
	 if (nx < 0 || nx >= c || ny < 0 || ny >= r ) continue;
	 t[ny][nx] = !t[ny][nx];
  }
  t[y][x] = !t[y][x]; 
}

int solve(int res){
  int i,j;
  for (i=1; i < r; ++i)
	 for (j=0; j < c; ++j){
		if ( t[i-1][j] ){ tap( i , j ); res++; }
	 }
  bool valid = true;
  for (i=0; i < r; ++i)
	 for (j=0; j < c; ++j)
		if ( t[i][j] ) return INT_MAX;
  return res;
}

int main(){
  int best,tmp;
  char car;
  int i,j;
  int cnt;
  while (scanf("%d %d",&r,&c) && r){
		for (i=0; i<r; ++i)
		  for (j=0; j<c; ++j){
			 scanf(" %c",&car);
			 M[i][j] = car=='X'? true:false;
		  }
		
		best = INT_MAX;
		for (i=0; i < (1<<c); ++i){
		  cnt = 0;
		  memcpy(t,M,sizeof(M));
		  for (j=0; j < c; ++j){
			 if ( (i >> j)&1 ){ cnt++; tap(0,j); }
		  }
		  tmp = solve(cnt);
		  if (tmp < best) best = tmp;
		}
		if (best < INT_MAX) printf("You have to tap %d tiles.\n",best);
		else puts("Damaged billboard.");
  }
  return 0;
}