#include<cstdio>
#include<map>
#include<string>
#include<iostream>
using namespace std;
char line[50];
int main(){
  int n;
  int runs;
  scanf("%d",&runs);
  while (runs--){
	 map<string,int> M;
	 scanf("%d",&n);
	 while (getchar() != '\n');
	 while (n--){
		gets(line);
		M[string(line)]++;
	 }
	 map<string,int>::iterator it;
	 for (it=M.begin(); it!=M.end() ; ++it){
		cout << it->first << ' ' << it->second << '\n'; 
	 }
	 cout << '\n';
  }
  return 0;
}