#include<cstdio>
#include<vector>
#include<set>
#include<string>
#include<cstring>
#include<cctype>
#include<unistd.h>
#include<iostream>
using namespace std;

char cyph[100];
char line[100];
char salt[5];
char *res;

set<string> sw;
vector<string> lw;

int main(){
	int p;
	int m;
	string w;
	string t1,t2;
	
	scanf("%s",cyph);
	salt[0] = cyph[0];
	salt[1] = cyph[1];	
	salt[2] = '\0';
	
	while (scanf("%s",line) != EOF){
		p = 0;		
		m = strlen(line);
		while (p < m){
			while (p < m && !isalpha(line[p])) ++p;
			if (p < m){
				w = "";
				while (p < m && isalpha(line[p])){
					w += tolower(line[p]);
					++p;
				}
				if (w.size() > 1 && w.size() <= 5){
					sw.insert(w);
				}
			}
		}
	}
	
	lw = vector<string>(sw.begin(),sw.end());		
	//for (int i=0; i < lw.size(); ++i) cout << lw[i] << endl;
	bool found = false;
	for (int i=0; i < lw.size() && !found; ++i){
		for (int j=i; j < lw.size() && !found; ++j){
			if ((lw[i].size() + lw[j].size()) <= 7){
				t1 = lw[i] + " " + lw[j];
				t2 = lw[j] + " " + lw[i];
				t1[lw[i].size()] = '0';
				res = crypt(t1.c_str(),salt);
				if (!strcmp(res,cyph)){
					puts(t1.c_str());
					found = true;
					continue;
				}
				t2[lw[j].size()] = '0';
				res = crypt(t2.c_str(),salt);
				if (!strcmp(res,cyph)){
					puts(t2.c_str());
					found = true;
					continue;
				}				
				for (int k=1; k < 4 && !found; ++k){
					t1[lw[i].size()] = (1<<k) + '0';
					res = crypt(t1.c_str(),salt);
					if (!strcmp(res,cyph)){
						puts(t1.c_str());
						found = true;
						continue;
					}
					t2[lw[j].size()] = (1<<k) + '0';
					res = crypt(t2.c_str(),salt);
					if (!strcmp(res,cyph)){
						puts(t2.c_str());
						found = true;
						continue;					
					}				
				}
			}
		}
	}
	
	return 0;
}
