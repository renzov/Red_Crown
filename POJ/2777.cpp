#include<cstdio>
const int MAX = 100000 * 4; 
int prop[ MAX ];
int seg_tree[ MAX ]; 

void build_tree(int n,int l,int r){
  seg_tree[n] = 1; /* color 1 */
  prop[n] = 0; 
  if (l==r) return;
  int m = (l + r) >> 1;
  build_tree(2*n,l,m); build_tree(2*n+1,m+1,r); 
}

int query(int n,int L,int R,int l,int r){
  if (r < L || l > R ) return 0;
  if (l==L && r==R) return seg_tree[n];
  int m = (L + R) >> 1;
  if (prop[n]){
		seg_tree[2*n] = prop[n];
		prop[2*n] = prop[n];
		seg_tree[2*n+1] = prop[n];
		prop[2*n+1] = prop[n];
		prop[n] = 0;
  }
  if (r <= m) return query(2*n,L,m,l,r);
  if (l > m) return query(2*n+1,m+1,R,l,r);
  return query(2*n,L,m,l,m) | query(2*n+1,m+1,R, m+1, r);
}

void update(int n,int L,int R,int l,int r,int p){
  if (r < L || l > R ) return;
  if (L==l && r==R){
		seg_tree[n] = (1<<p);
		prop[n] = (1<<p);
		return;
  }
  if (prop[n]){
		seg_tree[2*n] = prop[n];
		prop[2*n] = prop[n];
		seg_tree[2*n+1] = prop[n];
		prop[2*n+1] = prop[n];
		prop[n] = 0;
  }
  int m = (L + R) >> 1;
  if (r <= m) update(2*n,L,m,l,r,p);
  else if ( l > m ) update(2*n+1,m+1,R,l,r,p);
  else {
		update(2*n,L,m,l,m,p);
		update(2*n+1,m+1,R,m+1,r,p);
  }
  seg_tree[n] = seg_tree[2*n] | seg_tree[2*n+1];
}

int main(){
  int L,T,O;
  char c;
  int l,r,col;
  int mask;
  scanf("%d %d %d",&L,&T,&O);
  build_tree(1,1,L);
  while (O--){
	 scanf(" %c",&c);
	 if (c == 'C'){
		  scanf("%d %d %d",&l,&r,&col);
		  if (l < 1) l = 1;
		  if (r > L) r = L;
		  if (l > r){ int tmp = l; l = r; r = tmp; }
		  col--;
		  update(1,1,L,l,r,col);
	 }
	 else {
		  scanf("%d %d",&l,&r);
		  if (l < 1) l = 1;
		  if (r > L) r = L;
		  if (l > r){ int tmp = l; l = r; r = tmp; }
		  mask = query(1,1,L,l,r);
		  printf("%d\n",__builtin_popcount(mask));
		  
	 }
  }
  return 0;
}