#include<cstdio>
struct node{
  int cnt;
  node *link[10];
  node(){
		cnt = 0;
		link[0] = link[1] = link[2] = link[3] = link[4] = link[5] = NULL;
		link[6] = link[7] = link[8] = link[9] = NULL;
  }
};
struct Trie {
  node *root;
  Trie(){ root = new node(); }
  void insert(int d){
		node *act = root;
		if (d == 0){
			 if ( act->link[0] != NULL ) act->link[0]->cnt++;
			 else { act->link[0] = new node(); act->link[0]->cnt++; }
			 return;
		}
		int dig;
		
		while ( d ){
			dig = d%10;
		   d /= 10;
			if ( act->link[dig] == NULL ) act->link[dig] = new node();
		   act = act->link[dig];
		}
		act->cnt++;
  }
  int search(int d){
		node *act = root;
		if (d == 0){
			 return act->link[0] == NULL ? 0:act->link[0]->cnt;
		}
		int dig;
		while ( d ){
			dig = d%10;
		   d /= 10;
			if ( act->link[dig] == NULL ) return 0;
		   act = act->link[dig];
		}
		return act->cnt;
  }
};
const int MAX = 40005;
int a[MAX][4];
Trie t[2];

inline int abs(int x){ return x<0? -x:x; }

int main(){
  int n;
  int sum;
  scanf("%d",&n);
  for (int i=0; i < n; ++i) scanf("%d %d %d %d",&a[i][0],&a[i][1],&a[i][2],&a[i][3]);
  for (int i=0; i < n; ++i){
		for (int j=0; j < n; ++j){
			 sum = a[i][0] + a[j][1];
			 t[ sum >= 0 ].insert( abs(sum) );
		}
  }
  long long res = 0;
  for (int i=0; i < n; ++i){
		for (int j=0; j < n; ++j){
			 sum = a[i][2] + a[j][3];
			 res += t[ sum <= 0 ].search(  abs(sum) );
		}
  }
  printf("%lld\n",res);
  return 0;
}