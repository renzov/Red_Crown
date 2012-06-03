#include<cstdio>
const int MAX=100005;
int p[MAX];

struct node {
  node *left;
  node *right;
  int val;
  int d;
  node(){ right = left = NULL; d = 1; }
  node(int v){ right = left = NULL; d = 1; val = v; }
  void remove(){
		if (left != NULL) left->remove();
		delete left;
		if (right != NULL) right->remove();
		delete right;
		left = right = NULL;
  }
};

node *T[MAX];

inline int D(node *N){
  return (N==NULL)? 0:N->d;
}

node *merge(node *A,node *B){
  if ( A == NULL || B == NULL ) return (A==NULL)? B:A;
  node *R,*L;
  if (A->val >= B->val){ R = A; L = B; }
  else { R = B; L = A; }
  R->right = merge( R->right , L );
  if ( D( R->left ) < D( R->right ) ){  
	 node *tmp = R->left; R->left = R->right; R->right = tmp; 
  }
  R->d = D( R->right ) + 1;
  return R;
}

void make_set(int x,int y){
  p[x] = x;
  T[x] = new node(y);
}

int find_set(int x){
  return (x!=p[x])? ( p[x] = find_set(p[x]) ): p[x]; 
}

void rebuilt_heap(int x){
  node *tmp = merge( T[x]->left,T[x]->right );
  T[x]->val >>= 1; T[x]->d = 1;
  T[x]->left = T[x]->right = NULL;
  T[x] = merge( tmp , T[x] );
}

int union_set(int x,int y){
  int px = find_set(x); 
  int py = find_set(y);
  if (px == py) return -1;
  rebuilt_heap(px); rebuilt_heap(py);
  p[py] = px;
  T[px] = merge(T[px],T[py]);
  return T[px]->val;
}

int main(){
  int n,m;
  int v;
  int x,y;
  while (scanf("%d",&n) != EOF){
	 for (int i=0; i < n; ++i){
		scanf("%d",&v);
		make_set(i,v);
	 }
	 scanf("%d",&m);
	 while (m--){
		scanf("%d %d",&x,&y);
		x--,y--;
		printf("%d\n",union_set(x,y));
	 }
	 for (int i=0; i < n; ++i){
		  x = find_set(i);
		  if (T[x] != NULL){
			 T[x]->remove();
			 delete T[x];
			 T[x] = NULL;
		  }
	 }
  }
  return 0;
}