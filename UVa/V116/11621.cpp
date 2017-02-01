#include<cstdio>
#include<set>
using namespace std;
int main(){
  long long n;
  long long p2 = 1;
  long long p3 = 1;
  set<long long> S;
  for (int i=0; i < 32; ++i){
		  p3 = 1;
		  for (int j=0; j < (32-i); ++j){
				S.insert(p2*p3);
				p3*=3;
		  }
		  p2*=2;
  }
  while (scanf("%lld",&n) && n){
		printf("%lld\n",*S.lower_bound(n));
  }
  return 0;
}