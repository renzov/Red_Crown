#include<cstdio>
int d[10005];
int main(){
  int n;
  bool ok;
  int sum;
  int zero;
  while (scanf("%d",&n) && n ){
	ok = true; sum = 0; zero = 0;
	for (int i=0; i < n && ok; ++i){
		scanf("%d",d + i);
		sum += d[i];
		ok = d[i] < n && d[i] >= 0;
		if (d[i]==0) zero++;
	}
	if (!ok){ puts("Not possible"); continue; }
	ok = sum % 2 == 0;
	if (!ok){ puts("Not possible"); continue; }
	int maxDeg = n - zero - 1;
	if (maxDeg < 0) maxDeg = 0;
	for (int i=0;  i < n && ok; ++i){
		ok = d[i] <= maxDeg;
	}
	if (!ok){ puts("Not possible"); continue; }
	puts("Possible");
  }

  return 0;

}