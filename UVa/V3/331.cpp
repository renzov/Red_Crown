#include<cstdio>
#include<algorithm>
using namespace std;

int a[10]; 
int n;
int bound;
int res;

void backtrack(int p){
	if (p > bound) return;
	int i;
	for (i=0; i < n-1 && (a[i] <= a[i+1]) ; ++i);
	if (i == n-1){
		res++;
		return;
	}
	for (; i < n-1; ++i){
		if (a[i] > a[i+1]){
			swap(a[i],a[i+1]);
			backtrack(p+1);
			swap(a[i],a[i+1]);
		}
	}
}

int main(){
	int cases = 0;
	
	while (scanf("%d",&n) && n){
		cases++;
		for (int i=0; i < n; ++i) scanf("%d",a+i);
		bound = 0;
		res = 0;
		for (int i=0; i < n; ++i){
			for (int j=i+1; j < n; ++j)
				if (a[i] > a[j])
					bound++;
		}
		if (bound == 0){
			printf("There are 0 swap maps for input data set %d.\n",cases);
		}
		else {
			backtrack(0);
			printf("There are %d swap maps for input data set %d.\n",res,cases);
		}
	}

	return 0;
}