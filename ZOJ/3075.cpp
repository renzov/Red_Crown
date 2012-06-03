#include<cstdio>
#include<climits>

const int MAX = 4 * 100002;
int seg_tree[MAX];
long long seg_tree_min[MAX]; 
int a[100002];
int N,P,Q,F;

inline long long min(long long a,long long b){
  return (a<b)? a:b;
}

inline int min(int a,int b){
  return (a<b)? a:b;
}


void build_tree(int n,int l,int r){
  if (l==r){
	 seg_tree[n] = a[l];
	 seg_tree_min[n] = ((long long)l * F) + a[l];
	 return;
  }
  int m = (l + r) >> 1;
  build_tree(2*n,l,m);
  build_tree(2*n+1,m+1,r);
  seg_tree[n] = min(seg_tree[2*n],seg_tree[2*n+1]);
  seg_tree_min[n] = min(seg_tree_min[2*n],seg_tree_min[2*n+1]);
}

int query(int n,int L,int R,int l,int r){
  if (l==L && r==R) return seg_tree[n];
  int m = (L + R) >> 1;
  if (r <= m) return query(2*n,L,m,l,r);
  if (l > m) return query(2*n+1,m+1,R,l,r);
  return min( query(2*n,L,m,l,m) , query(2*n+1,m+1,R,m+1,r) );
}

long long query_min(int n,int L,int R,int l,int r){
  if (l==L && r==R) return seg_tree_min[n];
  int m = (L + R) >> 1;
  if (r <= m) return query_min(2*n,L,m,l,r);
  if (l > m) return query_min(2*n+1,m+1,R,l,r);
  return min( query_min(2*n,L,m,l,m) , query_min(2*n+1,m+1,R,m+1,r) );
}

int main(){
  long long res;
  int to,from;
  long long temp1;
  long long temp2;
  while (scanf("%d %d %d %d",&N,&P,&Q,&F) != EOF){
		for (int i=1; i <= N; ++i) scanf("%d",a+i);
		build_tree(1,1,N);
		res = INT_MAX;
		for (int i=1; i < (N-P); ++i){
		  from = i + P + 1;
		  to = min(i+Q+1,N);
		  temp1 = query(1,1,N,from,to);
		  temp2 = INT_MAX;
		  if (to<N){
			 temp2 = query_min(1,1,N,to+1,N);
			 temp2 -= (long long)F*to;
		  }
		  if (temp1 > temp2) temp1 = temp2;
		  if (res > (temp1 + a[i])) res = temp1 + a[i];
		}
		printf("%lld\n",res);
  }
  return 0;
}