#include<cstdio>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;

int pos[9][9][10];
int num[9][9];
int res[9][9];
int left;

void init(){
  int i,j,k;
  for(i=0; i<9; ++i)
	 for (j=0;j<9; ++j){
		num[i][j] = 9;
		for (k=1; k < 10; ++k){
		  pos[i][j][k] = 1;
		}
	 }
}

void undo_change( int x, int y ){
  int v = res[x][y];
  res[x][y] = 0;
  int i,j,k;
  int ix = 3*(x / 3);
  int iy = 3*(y / 3);
  for (i=ix; i < (ix + 3) ; ++i){
	 for (j=iy; j < (iy + 3); ++j){		
		pos[i][j][v]++;
		if ( pos[i][j][v] > 0 ){
		  num[i][j]++;
		}		
	 }
  }
  for (i=ix-1,j=ix+3; i >= 0 || j < 9 ; ++j,--i){
		if (i >= 0){
		  pos[i][y][v]++;
		  if ( pos[i][y][v] > 0 ){
			 num[i][y]++;
		  }
		}
		if (j < 9){
		  pos[j][y][v]++;
		  if ( pos[j][y][v] > 0 ){
			 num[j][y]++;
		  }
		}
  }
  for (i=iy-1,j=iy+3; i >= 0 || j < 9 ; ++j,--i){
		if (i >= 0){
		  pos[x][i][v]++;
		  if ( pos[x][i][v] > 0 ){
			 num[x][i]++;
		  }
		}
		if (j < 9){
		  pos[x][j][v]++;
		  if ( pos[x][j][v] > 0 ){
			 num[x][j]++;
		  }
		}
  }
}
void delete_elem( int x, int y ){
  int v = res[x][y];
  int i,j,k;
  int ix = 3*(x / 3);
  int iy = 3*(y / 3);
  for (i=ix; i < (ix + 3) ; ++i){
	 for (j=iy; j < (iy + 3); ++j){		
		pos[i][j][v]--;
		if ( pos[i][j][v] == 0 ){
		  num[i][j]--;
		}		
	 }
  }
  for (i=ix-1,j=ix+3; i >= 0 || j < 9 ; ++j,--i){
		if (i >= 0){
		  pos[i][y][v]--;
		  if ( pos[i][y][v] == 0 ){
			 num[i][y]--;
		  }
		}
		if (j < 9){
		  pos[j][y][v]--;
		  if ( pos[j][y][v] == 0 ){
			 num[j][y]--;
		  }
		}
  }
  for (i=iy-1,j=iy+3; i >= 0 || j < 9 ; ++j,--i){
		if (i >= 0){
		  pos[x][i][v]--;
		  if ( pos[x][i][v] == 0 ){
			 num[x][i]--;
		  }
		}
		if (j < 9){
		  pos[x][j][v]--;
		  if ( pos[x][j][v] == 0 ){
			 num[x][j]--;
		  }
		}
  }
}
bool backtrack(){
  if (left == 0) return true;
  assert(left > 0);
  /* check for minimum */
  int i,j,k;
  int mini = 10;
  int x,y;
  for (i=0; i < 9; ++i)
	 for (j=0; j < 9; ++j){
		if ( !res[i][j] && (mini > num[i][j]) ){
		  mini = num[i][j];
		  x = i; y = j;
		}
	 }
  if (mini == 0) return false; /* error - no solution */
  for (k=1; k < 10; ++k){
	 if ( pos[x][y][k] > 0 ){
		  res[x][y] = k;
		  delete_elem( x , y );
		  left--;
		  if ( !backtrack() ){
			 left++;
			 undo_change( x , y );
		  }
		  else return true;
	 }
  }
  return false;
}

int main(){
  int runs;
  int i,j;
  scanf("%d",&runs);
  while (runs--){
	 init();
	 left = 9*9;
	 for (i=0; i < 9; ++i)
		for (j=0; j < 9; ++j){
		  scanf("%1d",&res[i][j]);
		  if (res[i][j]){
			 delete_elem( i , j );
			 left--;
		  }
		}
	 if (!backtrack()) puts("NP");
	 for (i=0; i < 9; ++i){
		for (j=0; j < 9; ++j)
		  printf("%d",res[i][j]);
		putchar('\n');
	 }
  }
  return 0;
}