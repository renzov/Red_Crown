#include<cstdio>
#include<cmath>
#include<cstring>
int v[105];
bool pos[10005];

int main(){

  int n,x;
  int a,b;

  while (scanf("%d %d",&n,&x) && n){
	 for (int i=0; i < n; ++i){
		scanf("%d.%d",&a,&b);
		v[i] = a*100 + b;
	 }
	 x--;
	 memset(pos,false,sizeof(pos));
	 pos[0] = true;
	 for (int i=0; i < n; ++i){
		if (i != x){
		  for (int j=10000; j >= 0; --j){
				if ( pos[j] && (j + v[i]) <= 10000)
				  pos[j + v[i]] = true;
		  }
		}
	 }
	 double best = 0.0;
	 double tmp;
	 if ( v[x] == 0 ) puts("0.00");
	 else {
		for (int j=0; j <= 10000; ++j){
		  if (pos[j] && (j + v[x]) > 5000){
			 tmp = ( 100.0 * v[x] ) / ( v[x] + j );
			 if (tmp > best) best = tmp;
		  }
		}
		best = floor(best*100 + .5)/100;
		printf("%0.2lf\n",best);
	 }
  }
  return 0;
}