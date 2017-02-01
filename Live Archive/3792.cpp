#include<iostream>
#include<string>
using namespace std;
string num;
string cmp;
int n;

long long solve(int pos,int rel){
	if (pos >= n) return rel;
	if (num[pos]=='?'){
		if (rel > 0){
			return (long long)10*solve(pos+1,rel);
		}
		else {
			int dig = cmp[pos] - '0';
			if (dig == 9) return solve(pos+1,rel);
			return solve(pos+1,rel) + (long long)(9 - dig)*solve(pos+1,1);
		}
	}
	else {
		if (rel > 0) return solve(pos+1,rel);
		if (rel==0){
			if (cmp[pos] > num[pos]) return 0;
			return solve(pos+1,cmp[pos] < num[pos]);
		}
	}
}

int main(){
	cin >> num;
	while (num != "#"){
		cin >> cmp;
		n = num.size();
		long long res = solve(0,0);
		cout << res << "\n";
		cin >> num;
	}
	return 0;
}