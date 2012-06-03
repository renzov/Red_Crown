#include<cstdio>
#include<cmath>
const double INF = 10e12;
double dp[105];
int a[105];

double b,e,v,f;
int r;

inline int min(int x,int y){ return x <= y? x:y; }

double get_time(int d){
  int i;
  double t=0.0;
  for (i=0; i < d; ++i){
	 if (i < r){
		t += (1.0/(v - f * (r-i)) ); 
	 }
	 else {
		t += (1.0/(v - e * (i-r) ) );
	 }
  }
  return t;
}

int main(){
  int n,i,j,d;
  double t;
  while (scanf("%d",&n) && n){
	 a[0] = 0;
	 dp[0] = 0.0;
	 for (i=1; i <= n; ++i){
		scanf("%d",a+i);
		dp[i] = INF;
	 }
	 scanf("%lf",&b);
	 scanf("%d %lf %lf %lf",&r,&v,&e,&f);
	 for (i=1; i <= n; ++i){
		for (j=0; j < i; ++j){
		  d = (a[i] - a[j]);
		  t = get_time(d);
		  if (j > 0) t += b;
		  if ( dp[i] > (dp[j] + t) ) dp[i] = dp[j] + t;
		}
	 }
	 printf("%0.4lf\n",dp[n]);
  }
  return 0;
}