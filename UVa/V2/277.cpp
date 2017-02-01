#include<string>
#include<vector>
#include<iostream>
#include<cstdlib>
#include<map>
using namespace std;

int main(){
  string line;
  string styleCode,styleName,ext,price,desc;
  string itemDesc,itemId;
  int runs;
  int p;
  
  cin >> runs;
  getline(cin,line);
  getline(cin,line);

  while (runs--){
		cout << "Item Id,Item Desc,Item Price" << endl;
		map<string,string> H;
		while (getline(cin,line)){
			 if (line.size() == 0) break;
			 p = 0;
			 styleCode = "";
			 while (line[p] != ','){	styleCode += line[p];	++p;	}
			 ++p;
			 styleName = "";
			 while (line[p] != ','){	styleName += line[p];	++p;	}
			 ++p;
			 desc = "";
			 while (p < line.size() && line[p] != ','){	desc += line[p];	++p;	}
			 ++p;
			 ext = "";
			 while (p < line.size() && line[p] != ','){	ext += line[p];	++p;	}
			 ++p;
			 price = "";
			 while (p < line.size()){	price += line[p];	++p;	 }
			 
			 while (styleCode.size() < 3) styleCode = '0' + styleCode;
			 if (H.find(styleCode) == H.end()) H[styleCode] = styleName;
			 
			 itemId = styleCode + desc;
			 if (itemId.size() > 13) continue;
			 if (styleName == "") styleName = H[styleCode];
			 if (styleName == "") continue;
			 itemDesc = styleName;
			 if (ext != "") itemDesc += ('-' + ext);
			 itemDesc = itemDesc.substr(0,30);
			 cout << itemId << "," << itemDesc << ",";
			 if (price == "") cout << "0.00" << endl;
			 else {
				  p = atoi(price.c_str());
				  cout << p/100 << ".00" << endl;
				  //if ((p%100) < 10) cout << '0';
				  //cout << "00" << endl; 
			 }
		}
		if (runs) cout << endl;
  }

  return 0;
}