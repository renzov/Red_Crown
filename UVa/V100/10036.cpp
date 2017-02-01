#include<cstdio>

bool state[2][105];
int v[10005];

inline int abs(int x){ return x<0? -x:x; }

int mod(int x,int k){
  if (x>=0) return x%k;
  int t = abs(x);
  int y = t / k;
  x = x + (y*k);
  if (x < 0) x+=k;
  return x;
}

int main(){
  int n,k;
  int x;
  int runs;
  int next;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d %d",&n,&k);
	 for (int i=0; i < n; ++i)	scanf("%d",v+i);
	 for (int i=0; i < k; ++i) state[0][i] = false;
	 state[0][mod(v[0],k)] = true;
	 x = 0;
	 for (int i=1; i < n; ++i){
		for (int j=0; j < k; ++j) state[1-x][j] = false;
		for (int j=0; j < k; ++j){
			 if (state[x][j]){
				next = mod(j + v[i],k);
				state[1-x][next] = true;
				next = mod(j - v[i],k);
				state[1-x][next] = true;
			 }
		}
		x = 1 - x;
	 }
	 if ( state[x][0] ) puts("Divisible");
	 else puts("Not divisible");
  }
  return 0;
}