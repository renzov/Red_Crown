#include<cstdio>
#include<cctype>

const int KB = 1024;
const int MAX = 128*KB;

struct node {
  int w;
  node *edge[26];
  void clear(){
	 	w = 0;
		for (int i=0; i < 26; ++i) edge[i] = NULL;
  }
} mem[ MAX ];

int used = 0;
int val;

struct Trie {
  node *root;
  Trie(){
	 used = 0;
	 mem[ used ].clear();
	 root = &(mem[ used ]);
  }
  void insert(char *s){
		node *act = root;
		int where;
		for (int i=0; s[i]; ++i){
		  where = s[i] - 'a';
		  if (act->edge[ where ] == NULL){  mem[used].clear(); act->edge[ where ] = &(mem[ used++ ]); };
		  act = act->edge[ where ];
		}
		act->w = val;
  }
  int search(char *s){
		node *act = root;
		int where;
		for (int i=0; s[i]; ++i){
		  if (isdigit(s[i])) return 0;
		  where = s[i] - 'a';
		  if (act->edge[ where ] == NULL) return 0;
		  act = act->edge[ where ];
		}
		return act->w;
  }
};

int main(){
  int n,m;
  char s[100];
  Trie t;
  scanf("%d %d",&n,&m);
  while ( n-- ){
		scanf("%s %d",s,&val);
		t.insert(s);
  }
  int res;
  while (m--){
	 res = 0;
	 while (scanf("%s",s) && s[0] != '.'){
		  res += t.search(s);
	 }
	 printf("%d\n",res);
  }
  return 0;
}