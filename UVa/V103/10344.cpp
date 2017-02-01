#include<cstdio>
#include<set>
#include<algorithm>
using namespace std;

int v[5];

bool dfs(int s,int p){
  if ( p == 4 ){
	 if ( (s + v[p]) == 23 ) return true;
	 if ( (s - v[p]) == 23 ) return true;
	 if ( (s * v[p]) == 23 ) return true;
	 return false;
  }
  return dfs( s + v[p] , p+1 ) || dfs( s - v[p] , p+1 ) || dfs( s * v[p] , p+1 );
}

int main(){
  bool f;
  while ( scanf("%d %d %d %d %d",v,v+1,v+2,v+3,v+4) && v[0] ){
	 sort( v , v + 5 );
	 do {
		f = dfs(v[0],1);
		if ( f ) break;
	 }
	 while ( next_permutation(v,v+5) );
	 if ( f ) puts("Possible");
	 else puts("Impossible");
  }
  return 0;
}