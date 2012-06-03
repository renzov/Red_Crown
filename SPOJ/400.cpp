#include<cstdio>

char M[101][21];

int main(){
  char line[205];
  int C;
  bool inc;
  int y,x;
  while (scanf("%d",&C) && C){
		scanf("%s",line);
		y = 0;
		x = 0;
		inc = true;
		for (int i=0; line[i]; ++i){
		  M[y][x] = line[i];
		  if (inc) x++;
		  else x--;
		  if (x >= C){ x = C - 1; y++; inc = false; }
		  else if (x < 0){ x = 0; y++; inc = true; }
		}
		
		for (int j=0; j < C; ++j){
			 for (int i=0; i < y; ++i)
				putchar(M[i][j]);
		}
		putchar('\n');
  }

  return 0;
}