#include<cstdio>
const int MAX = 100000 * 4;

int seg_tree[MAX] = {0};
char prop[MAX] = {0};

void update(int n,int L,int R,int l,int r){
  if (l==L && r==R){
	 seg_tree[n] = (R - L + 1) - seg_tree[n];
	 prop[n] = 1 - prop[n];
	 return;
  }
  int M = (L + R) >> 1;
  if (prop[n]){
	 seg_tree[n<<1] = (M - L + 1) - seg_tree[n<<1];
	 seg_tree[(n<<1) + 1] = (R-(M+1)+1) - seg_tree[(n<<1)+1];
	 prop[n<<1] = 1 - prop[n<<1];
	 prop[(n<<1) + 1] = 1 - prop[(n<<1) + 1];
	 prop[n] = 0;
  }
  if (r <= M) update(n<<1,L,M,l,r);
  else if (M < l) update((n<<1)+1,M+1,R,l,r);
  else {
	 update(n<<1,L,M,l,M);
	 update((n<<1)+1,M+1,R,M+1,r);
  }
  seg_tree[n] = seg_tree[n<<1] + seg_tree[(n<<1) + 1];
}

int query(int n,int L,int R,int l,int r){
  if (L==l && r==R) return seg_tree[n];
  int M = (L + R) >> 1;
  if (prop[n]){
	 seg_tree[n<<1] = (M - L + 1) - seg_tree[n<<1];
	 seg_tree[(n<<1) + 1] = (R-(M+1)+1) - seg_tree[(n<<1)+1];
	 prop[n<<1] = 1 - prop[n<<1];
	 prop[(n<<1) + 1] = 1 - prop[(n<<1) + 1];
	 prop[n] = 0;
  }
  if (r<=M) return query(n<<1,L,M,l,r);
  if (l > M) return query((n<<1)+1,M+1,R,l,r);
  return query(n<<1,L,M,l,M) + query((n<<1)+1,M+1,R,M+1,r);
}

int main(){
  int n,m;
  int l,r;
  int op;
  scanf("%d %d",&n,&m);
  while (m--){
	 scanf("%d %d %d",&op,&l,&r);
	 if (op)
		printf("%d\n",query(1,1,n,l,r));
	 else
		update(1,1,n,l,r);
  }
  return 0;
}