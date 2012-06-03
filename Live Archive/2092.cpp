#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
  int runs;
  int n;
  int tmp,pos;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 vector<int> a(n);
	 vector<int> ord(n);
	 vector<int> p(n);
	 vector<bool> used(n,false);
	 for (int i=0; i < n; ++i){ scanf("%d",&a[i]); ord[i] = a[i]; }
	 sort(ord.begin(),ord.end());
	 for (int i=0;i < n; ++i) p[i] = lower_bound( ord.begin(), ord.end() , a[i] ) - ord.begin();
	 int res = 0;
	 for (int i=0; i < n; ++i){
		if (!used[i]){
		  pos = i;
		  do {
			 used[pos] = true;
			 pos = p[ pos ];
		  }
		  while (!used[pos]);
		  res++;
		}
	 }
	 res = n - res;
	 printf("%d",res);
	 if (runs) putchar(' ');
  }
  return 0;
}