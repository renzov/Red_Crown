#include<map>
#include<iostream>
using namespace std;

struct elem {
  int B;
  int C[ 15 ];
  int L[ 15 ];
  int U[ 15 ];
  int D;
  int S;
};

void calculate(elem &e){
  int sum;
  e.C[ e.D ] = e.S;
  sum = e.C[ e.D ]*e.L[ e.D ];
  for (int i=e.D - 1; i >= 1; --i){
		e.C[i] = e.C[i+1]*( e.U[i+1] - e.L[i+1] + 1);
		sum += e.C[i]*e.L[i];
  }
  e.C[0] = e.B - sum;
}

int main(){
  
  int N,R;
  string name;
  elem e;
  cin >> N >> R;

  map<string,elem> hash;

  for (int i=0;  i < N; ++i){
	 cin >> name;
	 cin >> e.B >> e.S >> e.D;
	 for (int j=1; j <= e.D; ++j){
		cin >> e.L[j] >> e.U[j];
	 }
	 calculate(e);
	 hash[ name ] = e;
  }
  int res,d;
  for (int i=0; i<R; ++i){
	 cin >> name;
	 e = hash[ name ];
	 cout << name << "[";
	 res = e.C[0];
	 for (int j=1; j <= e.D; ++j ){
		if (j > 1) cout << ", ";
		cin >> d;
		res += e.C[j]*d;
		cout << d;
	 }
	 cout << "] = " << res << endl;
  }
  
  return 0;
}