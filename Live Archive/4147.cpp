#include<cstdio>

bool b[1<<11][2];

int main(){
  
  int runs;
  int n,m;
  int x;
  scanf("%d",&runs);
  
  while (runs--){
	 scanf("%d %d",&n,&m);
	 for ( int i=0; i < 1<<n; ++i ) b[i][0] = true;
	 for ( int i=0; i < m; ++i ){
		scanf("%d",&x);
		x--; b[x][0] = false;
	 }
	 bool change = true;
	 int res = 0;
	 x = 0;
	 for ( int i=n; i >= 1 && change; --i ){
		change = false;
		for ( int j=0; j < (1<<i) ; j+=2 ){
		  if ( b[j][x] ^ b[j+1][x] ) res++;
		  b[j>>1][1-x] = b[j][x] | b[j+1][x];
		  if ( b[j>>1][1-x] ) change = true;
		}
		x = 1 - x;
	 }
	 printf("%d\n",res);
  }
  return 0;
}