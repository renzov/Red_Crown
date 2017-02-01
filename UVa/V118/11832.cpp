#include<cstdio>
#include<set>
using namespace std;
int v[42];
bool btup[42][80002];
char res[42];

int main(){
  
  int n,f;
  int zero,last;
  int x;
  char bb;
  int next;
  
  while ( scanf("%d %d",&n,&f) && n ){
	 for (int i=1; i <= n; ++i){ scanf("%d",v+i); }
	 set<int> state[2];
	 zero = n * 1000;
	 f += zero;
	 last = zero << 1;
	 state[0].insert(zero);
	 x = 0;
	 for (int i=0; i <= n; ++i)
		for (int j=0; j <= last; ++j)
		  btup[i][j] = false;

	 btup[0][zero] = true;
 
	 for (int i=1; i <= n; ++i){
		state[1-x].clear();
		for(set<int>::iterator it = state[x].begin(); it != state[x].end(); ++it){
			 next = *it + v[i];
			 if ( next >= 0 && next <= last ){ state[1-x].insert(next); btup[i][next] = true; }
			 next = *it - v[i];
			 if ( next >= 0 && next <= last ){ state[1-x].insert(next); btup[i][next] = true; }
		}
		x = 1 - x;
	 }
	 if ( !btup[n][f] ){
		puts("*");
	 }
	 else {
		  state[0].clear();
		  x = 0;
		  state[0].insert(f);
		  for (int i=n; i > 0; i--){
				state[1-x].clear();
				bb = 0;
				for(set<int>::iterator it = state[x].begin(); it != state[x].end(); ++it){
				  next = *it + v[i];
				  if ( next >= 0 && next <= last && btup[i-1][next] ){ state[1-x].insert(next); bb |= 1; }
				  next = *it - v[i];
				  if ( next >= 0 && next <= last && btup[i-1][next] ){ state[1-x].insert(next); bb |= 2; }
				}
				if ( bb == 3 ) res[i-1] = '?';
				else if ( bb == 2 ) res[i-1] = '+';
				else res[i-1] = '-';
				x = 1 - x;
		  }
		  res[n] = '\0';
		  puts(res);
	 }
  }
  return 0;
}