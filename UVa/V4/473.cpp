#include<cstdio>
#include<cstring>
#include<cctype>
#include<iostream>
using namespace std;

long long maximum(long long a,long long b){
	return (a > b)? a:b;
}

long long last[1000][1000];
long long act[1000][1000];

int read_int(){
	int r = 0;
	char c;
	while (!isdigit(c=getchar()));
	r = c-'0';
	while (isdigit(c=getchar())){
		r *= 10;
		r += (c-'0');
	}
	return r;
}

long long read_long(){
	long long r = 0;
	char c;
	while (!isdigit(c=getchar()));
	r = c-'0';
	while (isdigit(c=getchar())){
		r *= 10;
		r += (c-'0');
	}
	return r;
}


int main(){

	int n,m,t;
	int runs;
	long long w;
	
	runs = read_int();
	while (runs--){
		n = read_int();
		t = read_int();
		m = read_int();
		
		for (int i=0; i <= m; ++i)
			for (int j=0; j <= t; ++j)
				last[i][j] = 0;
		
		for (int i=1; i <= n; ++i){
			 
			 w = read_long();
			 
			 if (w <= t){
			 
				for (int j=0; j < m; ++j){
					 for (int k=0; k <= t; ++k){
						  act[j][k] = last[j][k];
						  if (w <= k){
							 act[j][k] = maximum( act[j][k] , 1 + last[j][ k - w ] );
						  }
						  else if (j > 0){
							 act[j][k] = maximum( act[j][k] , 1 + last[j-1][ t - w ] );
						  }
					 }
				}
				
				for (int j=0; j < m; ++j){
					 for (int k=0; k <= t; ++k){
						  last[j][k] = act[j][k];
					 }
				}
				
			 }
		}
		cout << last[m-1][t] << endl;
		if (runs) cout << endl;
	}

	return 0;
}