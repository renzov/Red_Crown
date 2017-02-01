#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

int main(){

  int f,r;
  int F[ 100 ];
  int R[ 100 ];
  double d[100*100];
  
  while (scanf("%d",&f) && f){
		scanf("%d",&r);
		for (int i=0; i < f; ++i)
		  scanf("%d",F + i);
		for (int i=0; i < r; ++i)
		  scanf("%d",R + i);
		
		for (int i=0; i < f; ++i)
			for (int j=0; j < r; ++j)
			  d[i*r + j] = (double)R[j] / F[i];
	
		sort(d,d+(r*f));
		
		double best = 0.0;
		
		for (int i=0; i < ((r*f)-1); ++i){
		  if (d[i+1]/d[i] > best) best = d[i+1]/d[i];
		}
		best = floor( best*100 + 0.5 )/100;
		printf("%.2lf\n",best);
  }

  return 0;
}