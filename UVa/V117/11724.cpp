#include<cstdio>
#include<queue>
#include<vector>
#include<stack>
#include<cctype>
#include<algorithm>
using namespace std;

vector<int> G[30];
bool def[30]={0};
bool visited[30];
int indegree[30];
int dist[30]={0};
char posfix[500];

int evaluate(){
  int u,v;
  stack<int> s;
  for (int i=0; posfix[i]; ++i){
	 if (isalpha(posfix[i])){
		s.push( dist[ posfix[i]-'a' ] );
	 }
	 else {
		v = s.top();
		s.pop();
		u = s.top();
		s.pop();
		if (posfix[i]=='+'){
		  u+=v;
		}
		else {
		  u*=v;
		}
		s.push(u);
	 }
  }
  return s.top();
}

void to_posfix(char *exp){
  int p = 0;
  stack<char> s;
  for (int i=0; exp[i]; ++i){
	 switch(exp[i]){
		  case '(' : s.push(exp[i]);  break;
		  case '+' : while (!s.empty() && (s.top()=='*' || s.top()=='+')){
							 posfix[p++] = s.top();
							 s.pop();
						 }
						 s.push(exp[i]);
						 break;
		  case '*' : while (!s.empty() && s.top()=='*'){
							 posfix[p++] = s.top();
							 s.pop();
						 }
						 s.push(exp[i]);
						 break;
		  case ')' : while (s.top() != '('){
							 posfix[p++] = s.top();
							 s.pop();
						 }
						 s.pop();
						 break;
		  default :  posfix[p++] = exp[i]; break;
	 }
  }
  while (!s.empty()){
	 posfix[p++] = s.top();
	 s.pop();
  }
  posfix[p] = '\0';
}

bool topsort(){
  queue< int > q;
  for (int i=0; i < 26; ++i){
	 if (def[i] && !indegree[i]){
		dist[i] = 1;
		visited[i] = true;
		q.push( i );
	 }
  }
  int u,v;
  while (!q.empty()){
	 u = q.front();
	 q.pop();
	 for (int i=0; i < G[u].size(); ++i){
		v = G[u][i];
		indegree[v]--;
		dist[v] = max(dist[v],dist[u]+1);
		if (indegree[v] == 0){
		  visited[v] = true;
		  q.push(v);
		}
	 }
  }
  for (int i=0; i<26; ++i)
	 if (def[i] && !visited[i]) return false;
  return true;
}

int main(){
  int m;
  int runs;
  char exp[500];
  char c1,c2;

  scanf("%d",&runs);

  for (int k=1; k <= runs; ++k){
	 scanf("%s",exp);
	 scanf("%d",&m);
	 for (int i=0; i < 26; ++i){ 
		def[i] = visited[i] = false;
		indegree[i] = 0;
		dist[i] = 0;
		G[i].clear();
	 }
	 for (int i=0; exp[i]; ++i) 
		if (islower(exp[i])) 
		  def[ exp[i] - 'a' ] = true;
	 for (int i=0; i < m; ++i){
		scanf(" %c > %c",&c1,&c2);
		G[c2 - 'a'].push_back( c1 - 'a' );
		indegree[ c1-'a' ]++;
	 }
	 printf("Case %d:",k);
	 if (topsort()){
		  to_posfix(exp);
		  printf(" %d\n",evaluate());
	 }	
	 else {
		printf(" -1\n");
	 }
  }

  return 0;
}