#include<map>
#include<string>
#include<iostream>
#include<sstream>
#include<vector>
#include<set>
#include<cstdio>
#include<cctype>
#include<algorithm>
using namespace std;
const int INF = 999999999;
typedef pair<int,int> pii;

struct mx{
  string from;
  string to;
  int p;
  mx(){}
  mx(string f,string t,int pr){
		from = f;
		to = t;
		p = pr;
  }
};

vector<mx> W;
vector<bool> up;

bool match(string &from,string &s){
	if (from == s) return true;
	if (from[0]=='*' ){
		string::reverse_iterator r = from.rbegin();
		string::reverse_iterator f = s.rbegin();
		while (r != from.rend()){
			if (*r=='*') return true;
			if (f == s.rend()) return false;
			if (*r != *f) return false;
			r++,f++;
		}
		return true;
	}
	return false;
}

bool isnumber(string &a){
	for (int i=0; i < a.size(); ++i)
		if (!isdigit(a[i])) return false;
	return true;
}

int main(){
  int n;
  cin >> n;
  string a,b;
  string prev = "";
  string from,to;
  int p;
  int u,v;
  
  up = vector<bool>(n,true);
  W = vector<mx>(n);
  
  for (int i=0; i < n; ++i){
		cin >> a >> b;
		if (isnumber(a)){
			 from = prev;
			 sscanf(a.c_str(),"%d",&p);
			 to = b;
		}
		else {
			from = a;
			sscanf(b.c_str(),"%d",&p);
			cin >> to;
			prev = a;
		}
		W[i] = mx(from,to,p);
  }
    
  int best;
  int bi;
  cin >> a;
  while (a != "X"){
	
	cin >> from;
	
	switch(a[0]){
		case 'U' : 
			for (int i=0; i < n; ++i){
				if (match(W[i].to,from)) up[i] = true;
			}
		break;
		case 'D' : 
			for (int i=0; i < n; ++i){	
				if (match(W[i].to,from)) up[i] = false;
			}
		break;
		case 'A' : 
			best = -1;
			for (int i=0; i < n; ++i){
				if (match(W[i].from,from) && up[i]){
					if (best==-1 || best > W[i].p){
						bi = i;
						best = W[i].p;
					}
				}
			}
			cout << from << " => ";
			if (best != -1) cout << W[bi].to;
			cout << endl;
		break;
	}
 
	cin >> a;
  }

  return 0;
}