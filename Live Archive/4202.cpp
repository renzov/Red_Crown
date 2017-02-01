#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
  int h1,m1;
  int h2,m2;
  int A[2];
  int B[2];

  int runs;
  scanf("%d",&runs);
  for (int i=1; i<=runs; ++i){
	 scanf("%d:%d %d:%d",&h1,&m1,&h2,&m2);
	 A[0] = h1*60 + m1;
	 A[1] = h2*60 + m2;
	 scanf("%d:%d %d:%d",&h1,&m1,&h2,&m2);
	 B[0] = h1*60 + m1;
	 B[1] = h2*60 + m2;
	 if ( max(A[0],B[0]) <= min(A[1],B[1]) ){
		  printf("Case %d: Mrs Meeting\n",i);
	 }
	 else {
		  printf("Case %d: Hits Meeting\n",i);
	 }
  }

  return 0;
}