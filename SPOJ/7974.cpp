#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
  int a,b,c;
  while (scanf("%d %d %d",&a,&b,&c) && (a||b||c)){
		if (b<a) swap(a,b);
		if (c<a) swap(a,c);
		if (c<b) swap(b,c);
		if ( (b-a) == (c-b) ){
		  printf("AP %d\n",c + (b-a));
		}
		else {
		  printf("GP %d\n",c*(b/a));
		}
  }
  return 0;
}