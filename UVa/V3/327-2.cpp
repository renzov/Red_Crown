#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
int arr[26];
int flag[26];
bool bo[26];
int main()
{
string str1;
char str[100];
while(getline(cin , str1))
{
memset(flag,false,sizeof(flag));
memset(bo,false,sizeof(bo));
memset(arr,0,sizeof(arr));
memset(str,0,sizeof(str));
if(str1.size() == 0)
continue;
cout << "Expression: " << str1 << endl;
int j = 0,i = 0;
for(i = 0; i < str1.size(); i++)
{
if(str1[i] == ' ')
continue;
else
str[j++] = str1[i];
}
char s[100];
memset(s,0,sizeof(s));
int k = 0,l = 0;
if(str[0] == '-' || str[0] == '+')
{
l = 2;
s[k++] = str[0];
s[k++] = str[1];
}
for(i = l; i < j; i++)
{

if(isalpha(str[i]))
bo[str[i] - 'a'] = true;
if(isalpha(str[i]))
{
if(str[i+1] == '-' && str[i+2] == '-')
{
s[k++] = str[i];
arr[str[i] - 'a'] = str[i] - 'a' + 1;
flag[str[i] - 'a'] = str[i] - 'a';
i += 2;
}
else
if(str[i+1] == '+' && str[i+2] == '+')
{
s[k++] = str[i];
arr[str[i] - 'a'] = str[i] - 'a' + 1;
flag[str[i] - 'a'] = str[i] - 'a' + 2;
i += 2;
}

else
if(s[k - 1] == '-' && s[k - 2] == '-')
{
k -= 2;
s[k++] = str[i];
arr[str[i] - 'a'] = str[i] - 'a';
flag[str[i] - 'a'] = str[i] - 'a';
}
else
if(s[k - 1] == '+' && s[k - 2] == '+')
{
k -= 2;
s[k++] = str[i];
arr[str[i] - 'a'] = str[i] - 'a' + 2;
flag[str[i] - 'a'] = str[i] - 'a' + 2;
}
else
{
s[k++] = str[i];
arr[str[i] - 'a'] = str[i] - 'a' + 1;
flag[str[i] - 'a'] = str[i] - 'a' + 1;
}
}

else
s[k++] = str[i];
}

int value = arr[s[0] - 'a'];
for(i = 1; i < k; i+=2)
{
if(s[i] == '-')
value -= arr[s[i+1] - 'a'];
if(s[i] == '+')
value += arr[s[i+1] - 'a'];
}
cout << "    value = " << value <<endl;
for(char i = 'a'; i <= 'z'; i++)
{
if(bo[i - 'a'])
cout << "    " << i << " = " << flag[i - 'a'] << endl;
}
}
return 0 ;
}
