#include<iostream>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

typedef pair<char,char> cc;

vector<cc> after;
vector<cc> before;
string line;

int main(){
  int v[30];

  while (getline(cin,line)){
		if (line.size() == 0) continue;
		bool used[30] = {0};
		string res = "";
		before.clear();
		after.clear();
		int p;
		cout << "Expression: " << line << endl;
		string tmp = "";
		for (int i=0; i < line.size(); ++i)
			if (!isspace(line[i])) tmp+=line[i];
		line = tmp;	
		for (p=0; p < line.size(); ++p){
			 if (isalpha(line[p])){
					 used[ line[p] - 'a'] = true;
					 res += line[p];
			 }
			 else {
				  if (line[p+1] == line[p]){
						if (p > 0 && isalpha(line[p-1])){
							 after.push_back( make_pair(line[p],line[p-1]) );
							 ++p;
						}
						else {
							 before.push_back( make_pair(line[p],line[p+2]) );
							 ++p;
						}
				  }
				  else {
						res += line[p];
				  }
			 }
		}
		
		for (int i=0; i < 26; ++i) v[i] = i+1;
		int value;
		for (int i=0; i < before.size(); ++i){
			 if (before[i].first == '+') v[ before[i].second - 'a' ]++;
			 else v[ before[i].second - 'a' ]--;
		}
		value = v[res[0]-'a'];
		for (int i=1; i < res.size(); i+=2){
			 if (res[i]=='+'){
				  value += v[ res[i+1] - 'a' ];
			 }
			 else {
				  value -= v[ res[i+1] - 'a' ];
			 }
		}
		for (int i=0; i < after.size(); ++i){
			 if (after[i].first == '+') v[ after[i].second - 'a' ]++;
			 else v[ after[i].second - 'a' ]--;
		}
		cout << "    value = " << value << endl;
		for (int i=0; i < 26; ++i)
			 if (used[i]){
				  cout << "    " << (char)('a' + i) << " = " << v[i] << endl;
			 }
			 
  }

  return 0;
}