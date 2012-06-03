#include<cstdio>

const int KB = 1024;
const int MAX = 256*KB;
struct node {
  node *edge[52];
  void clear(){
		for (int i=0; i < 52; ++i) edge[i] = NULL;
  }
  node(){
	 for (int i=0; i < 52; ++i) edge[i] = NULL;
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
  void insert(int *s){
		node *act = root;
		for (int i=0; s[i] >= 0; ++i){
		  if (act->edge[ s[i] ] == NULL){  used++; mem[used].clear(); act->edge[ s[i] ] = &(mem[ used ]); };
		  act = act->edge[ s[i] ];
		}
  }
  void clear(){
		used = 0;
		mem[ used ].clear();
		root = &(mem[ used ]);
  }
};

int suit[256];

int main(){
  int a[100];
  char s[5];
  int v;
  int n;
  int m;
  suit['C'] = 0; suit['D'] = 1; suit['H'] = 2; suit['S'] = 3;
  while (scanf("%d",&n) && n){
		Trie t;
		while (n--){
		  scanf("%d",&m);
		  a[m] = -1;
		  while (m--){
			 scanf("%s",s);
			 switch (s[0]){
				case 'A': v = suit[ s[1] ]*13; break;
				case '1': v = suit[ s[2] ]*13 + 9; break;
				case '2': v = suit[ s[1] ]*13 + 1; break;	
				case '3': v = suit[ s[1] ]*13 + 2; break;
				case '4': v = suit[ s[1] ]*13 + 3; break;
				case '5': v = suit[ s[1] ]*13 + 4; break;
				case '6': v = suit[ s[1] ]*13 + 5; break;
				case '7': v = suit[ s[1] ]*13 + 6; break;
				case '8': v = suit[ s[1] ]*13 + 7; break;
				case '9': v = suit[ s[1] ]*13 + 8; break;
				case 'J': v = suit[ s[1] ]*13 + 10; break;
				case 'Q': v = suit[ s[1] ]*13 + 11; break;
				case 'K': v = suit[ s[1] ]*13 + 12; break;
			 }
			 a[m] = v;
		  }
		  t.insert(a);
		}
		printf("%d\n",used);
  }
  return 0;
}