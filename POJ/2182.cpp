#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX = 8000;

int a[MAX + 2];
int seg_tree[MAX * 4];
int res[MAX + 2];
int pos = 0;
void build_tree(int n,int l,int r){
  seg_tree[n] = r - l + 1;
  if (l==r) return;
  int m = (l+r) >> 1;
  build_tree(n<<1,l,m); build_tree((n<<1) + 1, m+1, r); 
}

void update(int N,int val){
  int l = 1;
  int r = N;
  int n = 1;
  int m;
  while (l!=r){
	 seg_tree[n]--;
	 m = (l+r)>>1;
	 if (seg_tree[n<<1] >= val){ r = m; n <<= 1; }
	 else { val -= seg_tree[n<<1]; l = m+1; n <<= 1; n++; }
  }
  seg_tree[n]--;
  res[pos++] = l;
}

int main(){
  int n;
  scanf("%d",&n);
  a[0] = 1;
  for (int i=1; i < n; ++i){
	 scanf("%d",a+i);
	 a[i]++;
  }
  build_tree(1,1,n);
  for (int i=n-1; i >= 0; --i){
	 update(n,a[i]);
  }
  for (int i=n-1; i >= 0; --i) printf("%d\n",res[i]);
  return 0;
}