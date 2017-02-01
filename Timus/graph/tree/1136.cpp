#include<cstdio>
struct node{
  node *left;
  node *right;
  int key;
  node(){ left = right = NULL; }
  node(int val){
	 left = right = NULL;
	 key = val;
  }
};

int a[3005];
int cnt;

void insert(node * &root,int val){
  if (root == NULL){
		root = new node(val);
		return;
  }
  else if (val < root->key){
	 insert(root->left,val);
  } 
  else {
	 insert(root->right,val);
  }
}

void print(node *root){
  if (root != NULL){
	 print(root->right);
	 print(root->left);
	 cnt++;
	 if (cnt > 1) putchar(' ');
	 printf("%d",root->key);
  }
}

int main(){
  int n;
  node *root = NULL;
  scanf("%d",&n);
  for (int i=0; i < n; ++i)
	 scanf("%d",a+i);
  for (int i=n-1; i >= 0; --i)
	 insert(root,a[i]);
  cnt = 0;
  print(root);
  putchar('\n');
  return 0;
}