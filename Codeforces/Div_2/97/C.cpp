#include<iostream>
#include<algorithm>
using namespace std;

int a[100005];

int main(){
  int n;
  int maxi,p;
  cin >> n;
  maxi = -2;
  for (int i=0; i < n; ++i){
	 cin >> a[i];
	 if (a[i] > maxi) maxi=a[i],p=i;
  }
  if (maxi == 1) a[p] = 2;
  else a[p] = 1;
  sort(a,a+n);
  for (int i=0; i < n; ++i){
	 if (i) cout << " ";
	 cout << a[i];
  }
  cout << endl;
  return 0;
}