#include<cstdio>
#include<algorithm>
using namespace std;

inline int maximum(int a,int b){
	 return a > b ? a:b;
}

const int MAX = 500002; 
int a[2][MAX];
int s[2];

int getMax(int t){
  if (s[0]==0 && s[1]==0) return 0;
  if (s[0]==0 && s[1]!=0) return 1;
  if (s[0]!=0 && s[1]==0) return 1;
  
  int p[2] = {0};
  int res = 1;
  int act = a[t][p[t]++];
  int next;

  while (p[0] < s[0] || p[1] < s[1]){
		next = 1-t;
		while ( p[next] < s[next] && a[next][ p[next] ] <= act){
			 p[next]++;
		}
		if (p[next] >= s[next]) break;
		act = a[next][p[next]++];
		t = next;
		res++;
  }
  return res;
}

int main(){

  int runs;
  int n;
  int num;

  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		s[0] = s[1] = 0;
		for (int i=0; i < n; ++i){
			 scanf("%d",&num);
			 if (num < 0){
				a[0][s[0]++] = -num;
			 }
			 else {
				a[1][s[1]++] = num;
			 }
		}
		sort(a[0],a[0] + s[0]);
		sort(a[1],a[1] + s[1]);
		printf("%d\n",maximum(getMax(0),getMax(1)));
  }

  return 0;
}