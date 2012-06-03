#include<cstdio>
#include<numeric>
#include<map>
#include<vector>
#include<cstring>
using namespace std;

char M[3][30];
int bit[10];
map<int,int> H;
int ans[10];
int v[10];
int sol;
int mask;

void init(){
  int p;
  p = (1 << 5) + (1 << 8);
  H[p] = 1; bit[1] = p;
  p = (1 << 1) + (1 << 4) + (1 << 5) + (1 << 6) + (1<<7);
  H[p] = 2; bit[2] = p;
  p =	(1 << 1) + (1 << 4) + (1 << 5) + (1 << 7) + (1<<8);
  H[p] = 3; bit[3] = p;
  p = (1 << 3) + (1 << 4) + (1 << 5) + (1 << 8);
  H[p] = 4; bit[4] = p;
  p = (1 << 1) + (1 << 3) + (1 << 4) + (1 << 7) + (1 << 8);
  H[p] = 5; bit[5] = p;
  p = (1 << 1) + (1 << 3) + (1 << 4) + (1 << 6) + (1 << 7) + (1 << 8);
  H[p] = 6; bit[6] = p;
  p = (1 << 1) + (1 << 5) + (1 << 8);
  H[p] = 7; bit[7] = p;
  p = (1 << 1) + (1 << 3) + (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7) + (1 << 8);
  H[p] = 8; bit[8] = p;
  p = (1 << 1) + (1 << 3) + (1 << 4) + (1 << 5) + (1 << 7) + (1 << 8);
  H[p] = 9; bit[9] = p;
  p = (1 << 1) + (1 << 3) + (1 << 5) + (1 << 6) + (1 << 7) + (1 << 8);
  H[p] = 0; bit[0] = p;
}

void backtrack(int p){
	 int tmp = v[p];
	 int bm,bt;
	 int sum;
	 for (map<int,int>::iterator it=H.begin(); it != H.end(); ++it){
		bm = __builtin_popcount(mask);
		bt = __builtin_popcount(it->first);
		if ((bm < bt) && (mask & it->first) == mask){
			v[p] = it->second;
			sum = 0;
			for (int i=8; i >= 0; --i){
			   sum += (v[i]*(9-i));	
			}
			if ((sum % 11) == 0){
				sol++;
				for (int i=0; i < 10; ++i) ans[i] = v[i];
			}
		} 
	 }
	 v[p] = tmp;
}

int analize(int c){
  int n = 0;
  for (int i=0; i < 3; ++i){
		for (int j=0; j < 3; ++j){
			 if (M[i][j+c] != ' ') n |= (1<<(i*3 + j));
		}
  }
  if (H.find(n) != H.end()) return H[n];
  mask = n;
  return -1;
}


int main(){
  int runs;
  int cnt;
  int idx;

  init();

  scanf("%d",&runs);
  while (getchar() != '\n');

  while (runs--){
		 cnt = 0;
		 for (int i=0; i < 3; ++i){
			 gets(M[i]);
			 if (strlen(M[i]) < 27){
				M[i][26] = ' ';
				M[i][27] = '\0';
			 }
		 }
		 for (int i=0; i < 9; ++i){
				v[i] = analize(i*3);
				if (v[i] == -1){
					 idx = i;
					 cnt++;
				}
		 }
		 if (cnt > 1){ printf("failure\n"); }
		 else if (cnt == 1){
			 sol = 0;
			 backtrack(idx);
			 if (sol == 0){
				  printf("failure\n");
			 }
			 else {
				  for (int i=0; i < 9; ++i) printf("%d",ans[i]);
				  putchar('\n');
			 }
		 }
		 else {
			 int sum = 0;
			 for (int i=8; i >= 0; --i){
				  sum += (v[i]*(9-i));
			 }
			 if (sum % 11 == 0){
				  for (int i=0; i < 9; ++i) printf("%d",v[i]);
				  putchar('\n');
			 }
			 else {
				  sol = 0;
				  for (int i=0; i < 9; ++i){
						mask = bit[ v[i] ];
						backtrack(i);
				  }
				  if (sol == 0){
						printf("failure\n");
				  }
				  else if (sol == 1){
						for (int i=0; i < 9; ++i) printf("%d",ans[i]);
						putchar('\n');
				  }
				  else {
						printf("ambiguous\n");
				  }
			 }
		 }
  }
  return 0;
}
