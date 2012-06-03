#include<cstdio>

const int KB = 1024;
const int MAX = 128*KB;
char word[100002][12];
int n;

struct node {
  int w;
  node *edge[26];
  void clear(){
	 	w = -1;
		for (int i=0; i < 26; ++i) edge[i] = NULL;
  }
} mem[ MAX ];

int used = 0;

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
		act->w = n-1;
  }
  int search(char *s){
		node *act = root;
		int where;
		for (int i=0; s[i]; ++i){
		  where = s[i] - 'a';
		  if (act->edge[ where ] == NULL) return -1;
		  act = act->edge[ where ];
		}
		return act->w;
  }
  void clear(){
		used = 0;
		mem[ used ].clear();
		root = &(mem[ used ]);
  }
};

int main(){
  char line[25];
  Trie t;
  char tmp[12];
  n = 0;
  while (gets(line) && line[0]){
		sscanf(line,"%s %s",word[n++],tmp);
		t.insert(tmp);
  }
  int idx;
  while (scanf("%s",tmp) != EOF){
		idx = t.search(tmp);
		if (idx == -1) puts("eh");
		else puts(word[idx]);
  }
  return 0;
}