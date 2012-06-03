#include<cstdio>
#include<cstring>
#include<vector>
#include<string>
#include<cctype>
using namespace std;

int m;
int p;

struct node {
  int idx;
  node *edge[26];
  node(){ for ( int i=0; i < 26; ++i ) edge[i] = NULL; idx = -1; }
  void clear(){
	 for ( int i=0; i < 26; ++i ) if ( edge[i] != NULL ){ edge[i]->clear(); delete edge[i]; }
  }
};

struct Trie {
  node *root;
  Trie(){ root = NULL; }
  void clear(){
	 if ( root != NULL ) root->clear();
	 root = new node();
  }
  node *search( char *s ){
	 node *act = root;
	 int where;
	 p = 0;
	 for ( int i=0; s[i]; ++i ){
		where = s[i] - 'a';
		if ( act->edge[where] == NULL ) return NULL;
		act = act->edge[where];
		p = (p + 1)%m;
	 }
	 return act;
  }
  void insert( char *s , int id ){
	 node *act = root;
	 int where;
	 for ( int i=0; s[i]; ++i ){
		 where = s[i] - 'a';
		 if ( act->edge[where] == NULL ) act->edge[where] = new node();
		 act = act->edge[where];
	 }
	 act->idx = id;
  }
};

Trie t;

bool dfs(node *u , int player){
  if( u->idx != -1 && player==p ) return false;
  for ( int i=0; i < 26; ++i ){
	 if ( u->edge[i] != NULL ){
		if ( !dfs( u->edge[i] , (player+1)%m ) ) return false;
	 }
  }
  return true;
}

bool dfs2( node *u, int player ){
  if ( u->idx != -1 && player == p ) return false;
  else if ( u->idx != -1 && player != p ) return true;
  for ( int i=0; i  < 26; ++i ){
	 if ( u->edge[i] != NULL ){
		if ( dfs2(u->edge[i] , (player+1)%m ) ) return true;
	 }
  }
  return false;
}

char s[1000000];
char w[1000000];

int main(){
  int n;
  while (1){
	 gets(s);
	 sscanf(s,"%d",&m);
	 if ( m < 2 ) break;
	 t.clear(); n = 0;
	 gets(w);
	 while ( sscanf(w,"%s",s) == 1 ){
		if ( strlen(s) >= 4 ){
			 t.insert(s,n);
			 n++;
		}
		gets(w);
	 }
	 gets(w);
	 int k = 0;
	 while (isalpha(w[k])){
		s[k] = w[k]; k++;
	 }
	 s[k] = '\0';
	 printf("%s ",s);
	 node *vertex = t.search(s);
	 if ( vertex == NULL ||  vertex->idx != -1 ){
		printf("Challenge\n");
	 }
	 else {
		int res = -1;
		int sec = -1;
		bool found = false;;
		for ( int i=0; i < 26 && !found; ++i ){
		  if ( vertex->edge[i] != NULL ){
			 if ( dfs( vertex->edge[i] , p ) ){
				res = i; found = true;
			 }
			 else if ( dfs2( vertex->edge[i] , p ) ){
				sec = i;
			 }
		  }
		}
		if ( res == -1 && sec == -1 ) puts("Bluff");
		else if ( res != -1 ) printf("%c\n",(char)(res+'a'));
		else printf("%c\n",(char)(sec+'a'));
	 }
  }
  return 0;
}