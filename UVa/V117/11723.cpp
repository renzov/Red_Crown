#include<cstdio>
int main(){
  int n,r,t;
  int cases = 0;
  while ( scanf("%d %d",&r,&n) && n ){
	 cases++;
	 if ( n >= r ) printf("Case %d: %d\n",cases,0);
	 else {
		r -= n;
		t = r/n;
		if ( r % n ) t++;
		if ( t > 26 ) printf("Case %d: impossible\n",cases);
		else printf("Case %d: %d\n",cases,t);
	 }
  }
  return 0;
}