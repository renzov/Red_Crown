#include<cstdio>
using namespace std;
bool up[25];
int C[25];
int main(){
  int n,m,c;
  int x;
  int best;
  bool blown;
  int cases = 0;
  int sum;
  while ( scanf("%d %d %d",&n,&m,&c) && ( n || m || c ) ){
	 cases++;
	 for ( int i=0; i < n; ++i ){ up[i] = false; scanf("%d",C+i); }
	 sum = 0;
	 best = 0;
	 blown = false;
	 for ( int i=0;  i < m; ++i){
		scanf("%d",&x); x--;
		if ( !blown ){
		  if ( up[x] ){ up[x] = false; sum -= C[x]; }
		  else {
			 if ( (sum + C[x]) <= c ){
				sum += C[x];
				up[x] = true; 
			 }
			 else {
				blown = true;
			 }
			 if ( sum > best ) best = sum;
		  }
		}
	 }
	 printf("Sequence %d\n",cases);
	 if ( blown ) puts("Fuse was blown.");
	 else printf("Fuse was not blown.\nMaximal power consumption was %d amperes.\n",best);
	 putchar('\n');
  }

  return 0;
}