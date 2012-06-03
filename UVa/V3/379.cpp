#include<cstdio>

char M[8][8];
int di[] = {0,-1,0,1};
int dj[] = {1,0,-1,0};

inline bool valid(int i,int j){
  return (i >= 0 && i < 7 && j >= 0 && j < 7 && M[i][j] != '*');
}

void init(){
  for (int i=0; i < 7; ++i)
	 for (int j=0; j < 7; ++j)
		  M[i][j] = '.';
	M[0][0] = M[0][1] = M[0][5] = M[0][6] = '*';
	M[1][0] = M[1][1] = M[1][5] = M[1][6] = '*';
	M[5][0] = M[5][1] = M[5][5] = M[5][6] = '*';
	M[6][0] = M[6][1] = M[6][5] = M[6][6] = '*';
}

void check(int p){
  if (p <= 3){ M[0][p + 1] = 'X'; return; }
  if (p <= 6){ M[1][p - 2] = 'X'; return; }
  if (p <= 13){ M[2][p - 7] = 'X'; return; }
  if (p <= 20){ M[3][p - 14] = 'X'; return; }
  if (p <= 27){ M[4][p - 21] = 'X'; return; }
  if (p <= 30){ M[5][p - 26] = 'X'; return; }
  M[6][p - 29] = 'X';
}

bool has_move(){
  int start , end;
  int be , bs , dir;
  int ni,nj;
  
  be = bs = -1;
  for (int i=0; i < 7; ++i){
		for (int j=0; j < 7; ++j){
			 if (M[i][j] == '*' || M[i][j] == '.') continue;
			 for (int k=0; k < 4; ++k){
				  ni = i + di[k];
				  nj = j + dj[k];
				  if (valid(ni,nj) && M[ni][nj] == 'X' && valid(ni + di[k],nj + dj[k]) && M[ni + di[k]][nj + dj[k]]=='.'){
						end = (ni + di[k])*7 +  (nj + dj[k]);
						start = i*7 + j;
						if (end > be){
							 be = end;
							 bs = start;
							 dir = k;
						}
						else if (be == end && bs < start){
							 bs = start;
							 dir = k;
						}
				  }
			 } 
		}
  }
  if (bs == -1) return false;
 
  int i = bs / 7;
  int j = bs % 7;
  M[i][j] = '.';
  M[i + di[dir]][j + dj[dir]] = '.';
  M[i + 2*di[dir]][j + 2*dj[dir]] = 'X';
  return true;
}

int count_total(){
  int res = 0;
  int cnt = 0;
  for (int i=0; i<7; ++i)
	 for (int j=0; j < 7; ++j){
		  if (M[i][j] == '*') continue;
		  cnt++;
		  if (M[i][j] == 'X') res += cnt;
	 }
  return res;
}

int main(){

  int runs;
  int pos;
  int res; 
  scanf("%d",&runs);
  puts("HI Q OUTPUT");
  while (runs--){
	 init();
	 while (scanf("%d",&pos) && pos){
		  check(pos);
	 }
	 while (has_move());
	 res = count_total();
	 printf("%d\n",res);
  }
  puts("END OF OUTPUT");
  return 0;
}