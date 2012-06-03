#include<cstdio>
int best;
bool diag1[20];
bool diag2[20];
bool row[10];
int M[10][10];

void backtrack(int c,int sum){
  if (c == 8){
		if (best < sum) best = sum;
		return;
  }
  for (int i=0; i < 8; ++i){
		if (!row[i] && !diag1[7 + c - i] && !diag2[c + i]){
		  row[i] = diag1[7 + c - i] = diag2[c + i] = true;
		  backtrack(c+1,sum + M[i][c]);
		  row[i] = diag1[7 + c - i] = diag2[c + i] = false;
		}
  }
}

int main(){
  
  int runs;
  scanf("%d",&runs);
  while (runs--){
		for (int i=0; i < 8; ++i)
			 for (int j=0; j < 8; ++j)
				  scanf("%d",&M[i][j]);
		for (int i=0; i < 20; ++i)
			diag1[i] = diag2[i] = false;
		for (int i=0; i < 8; ++i)
			row[i] = false;
		best = -1;
		backtrack(0,0);
		printf("%5d\n",best);
  }
  return 0;
}