#include<cstdio>
#include<cmath>
double len;
int n;
double price[60];
double dist[60];
double best;
double cap;
double mpg;
double limit;

void backtrack(double paid, double left, int p){
  if (paid >= best) return;
  if (p==(n-1)){
		best = paid;
		return;
  }
  double d,w;
  double nw;
  for (int i=p + 1; i < n && ((dist[i] - dist[p]) <= len); ++i){
		d = left * mpg;
		w = dist[i] - dist[p];
		if (d >= w){
		  backtrack( paid , left - (w/mpg) , i );
		}
		if (left <= limit){
			 nw = 200.0 + paid + ((cap - left) * price[p]);
			 nw = floor(nw + 0.5);
			 backtrack( nw , cap - (w/mpg) , i );
		}
  }
}

int main(){
  int m;
  double d,p;
  double dest;
  double init;
  int cases = 0;

  while (scanf("%lf",&dest) && dest > 0.0){
		cases++;  
		scanf("%lf %lf %lf %d",&cap,&mpg,&init,&n);
		len = mpg * cap;
		limit = cap / 2.0;
		dist[0] = 0.0;
		price[0] = init;
		for (int i=1; i <= n; ++i) dist[i] = 10e10;
		scanf("%lf %lf",&dist[1],&price[1]);
		m = 2;
		for (int i=2; i <= n; ++i){
		  scanf("%lf %lf",&d,&p);
		  if (fabs(d-dist[m-1]) < 0.001){
			 if (price[m-1] > p) price[m-1] = p;
		  }
		  else {
			 dist[m] = d;
			 price[m] = p;
			 m++;
		  }
		}
		dist[m] = dest;
		price[m] = 0.0;
		m++;
		n = m;
		best = 10e10;
		backtrack(init*100.0,cap,0);
		int res = (int)floor(best + 0.5);
		printf("Data Set #%d\nminimum cost = $%d.%02d\n",cases,res/100,res%100);
  }
  return 0;
}