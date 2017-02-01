#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

pair<long long,string> lst[105];

long long find_min_cost(long long N,long long M,long long A,long long B){
  long long cost = 0;
  long long diff,mid;
  while (N > M){
	 mid = N/2;
	 if (mid < M){ cost += (N-M)*A; }
	 else {
		diff = N - mid;
		if (diff*A < B){
			 cost += (diff*A);
		}
		else {
		  cost += B;
		}	  
	}
	N = mid;
  }
  return cost;
}

int main(){

  int runs;
  int N,M,L;
  int A,B;
  char name[25];

  scanf("%d",&runs);
  for (int k=1; k <= runs; ++k){
	 scanf("%d %d %d",&N,&M,&L);
	 for (int i=0; i < L; ++i){
		  scanf(" %[A-Z]:%d,%d",name,&A,&B);
		  lst[i].first = find_min_cost(N,M,A,B);
		  lst[i].second = string(name);
	 }
	 sort(lst,lst+L);
	 cout << "Case " << k << "\n";
	 for (int i=0; i < L; ++i){
		cout << lst[i].second << " " << lst[i].first << "\n";
	 }
  }
  
  return 0;
}