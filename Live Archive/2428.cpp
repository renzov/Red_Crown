#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;

const double eps = 0.0001;

struct cistern{
  double b;
  double h;
  double w;
  double d;

  bool operator<(const cistern &that) const{
  return b < that.b;
  }

};

int n;
double avail;
double maxLevel;

void search(cistern C[],int n){
  double low = 0.0;
  double high = maxLevel;
  double mid;
  bool ok;
  double tmp;
  double vol;

  while ((high - low) > eps){
	 mid = (low + high)/2.0;
	 ok = true;
	 tmp = avail;
	 for (int i=0; i < n; ++i){
	 if (C[i].b >= mid) break;
	 if (mid >= (C[i].b + C[i].h)){
		vol = C[i].h*C[i].w*C[i].d;
	 }
	 else {
		vol = (mid - C[i].b)*C[i].w*C[i].d;
	 }
	 if (vol > tmp){ ok = false; break; }
		tmp -= vol;
	 }
	 if (ok) low = mid;
	 else high = mid;
  }
  low = floor(low*100 + 0.5)/100;
  printf("%0.2lf\n",low);
}

int main(){

  int runs;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 cistern C[n];
	 double total = 0.0;
	 maxLevel = 0.0;
	 for (int i=0; i < n; ++i){
		scanf("%lf %lf %lf %lf",&C[i].b,&C[i].h,&C[i].w,&C[i].d);
		if ((C[i].b + C[i].h) > maxLevel) maxLevel = C[i].b + C[i].h; 
		total += (C[i].h*C[i].w*C[i].d);
	 }
	 scanf("%lf",&avail);
	 if (avail > total) printf("OVERFLOW\n");
	 else{ 
		sort(C , C + n); 
		search(C,n); 
	 }
	 if (runs) putchar('\n');
  }
  return 0;
}
