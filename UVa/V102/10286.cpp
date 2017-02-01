#include<cstdio>
#include<cmath>
const double prop = 1.067395682;
int main(){
  double L;
  while ( scanf("%lf",&L) != EOF ){
	 printf("%0.10lf\n",L*prop);
  }

  return 0;
}