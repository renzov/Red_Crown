#include<cstdio>
#include<cstring>
char st[10000][5];
char guess[ 12 ][5];
int c[12];
int f[12];

bool candidate(int x,int y){
	int cc = 0;
	int ff = 0;
	bool unif[5] = {0};
	bool left[5] = {0};
	for (int i=0; i < 4; ++i){
		if (st[x][i] == guess[y][i]){ cc++; left[i] = unif[i] = true; }
	}
	if (cc!=c[y]) return false;
	for (int i=0; i < 4; ++i)
		if (!unif[i]){
		  for (int j=0; j < 4; ++j){
				if ( !left[j] && st[x][j] == guess[y][i]){
				  ff++;
				  unif[i] = left[j] = true;
				  break;
				}
		  }
		}
  return ff == f[y];
}

int main(){
  int runs;
  int tmp;
  int pot;
  int n;
  for (int i=0; i < 10000; ++i){
	 tmp = i; pot = 1000;
	 for (int j=0; j < 4; ++j){
		st[i][j] = (char)(tmp / pot) + '0';
		tmp %= pot;
		pot/=10;
	 }
	 st[i][4] = '\0';
  }
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (int i=0; i < n; ++i){
		scanf("%s %d/%d",guess[i],c+i,f+i);
	 }
	 int res;
	 int cnt = 0;
	 bool ok;
	 for (int i=0; i < 10000; ++i){
		ok = true;
		for (int j=0;j < n && ok; ++j)
		  ok = candidate(i,j);
		if (ok){ cnt++; res = i; }
		if (cnt > 1) break;
	 }
	 if (cnt == 1) puts(st[res]);
	 else if (cnt == 0) puts("impossible");
	 else puts("indeterminate");
  }
  return 0;
}