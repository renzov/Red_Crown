#include<bits/stdc++.h>
using namespace std;
#define X real()
#define Y imag()
#define EPS 1e-7L
#define eps 1e-4L
#define OO  1e+9
#define LEN(v)  (hypotl((v).Y,(v).X))
#define cross(a,b) ((conj(a)*(b)).Y)
#define cross3(a,b,c) cross(VEC(a,b),VEC(a,c))
//#define dot(a,b) ((conj(a)*(b)).X)
#define dot(a,b) (((a.X)*(b.X))+((a.Y)*(b.Y)))
#define VEC(a,b) ((b)-(a))
#define normalize(v) ((v)/LEN(v))
typedef long double ld;
typedef complex<ld> point;
bool pcmp(point a,point b)
{
    return (fabs(a.X-b.X)>EPS && a.X<b.X) || (fabs(a.X-b.X)<EPS && fabs(a.Y-b.Y)>EPS && a.Y<b.Y);
}
inline bool pointOnSegment(point a,point b,point p)
{
    return dot(VEC(a,b),VEC(a,p)) > eps && dot(VEC(b,a),VEC(b,p)) > EPS;
}
point lineIntersection(point a1,point b1 ,point a2,point b2)
{
    ld A1=a1.Y-b1.Y ,B1=b1.X-a1.X ,A2=a2.Y-b2.Y ,B2=b2.X-a2.X;
    ld C1=A1*a1.X+B1*a1.Y ,C2=A2*a2.X+B2*a2.Y ,det=A1*B2-B1*A2;
    if(fabs(det)<EPS)   return point(OO,OO);
    return point(C1*B2-B1*C2,A1*C2-C1*A2)/det;
}
void order(vector<point> &v)
{
    ld area=0;
    int sz=v.size();
    for(int i=1;i+1<sz;i++)
        area+=cross(VEC(v[0],v[i]),VEC(v[0],v[i+1]));
    if(area<-EPS)
        reverse(v.begin(),v.end());
}
int main()
{
    int n,m;
    ld x1,y1,x2,y2;
    cout<<setprecision(11)<<fixed;
    cin>>n>>m;
    vector<point> vec(n);
    map<point,int,bool(*)(point,point)> vertex(pcmp);
    for(int i=0;i<n;i++)
    {
        cin>>x1>>y1;
        vec[i]=point(x1,y1);
    }
    order(vec);
    for(int i=0;i<n;i++)
        vertex[vec[i]]=i;
    while(m--)
    {
        ld com=0;
        cin>>x1>>y1>>x2>>y2;
        point a=point(x1,y1),b=point(x2,y2);
        vector<point> inter;
        for(int i=0;i<n;i++)
            if(fabs(cross3(a,b,vec[i]))<EPS)
            {
                int j=(i-1+n)%n;
                int k=(i+1)%n;
                if(cross3(a,b,vec[j])*cross3(a,b,vec[k])<EPS)
                    inter.push_back(vec[i]);
            }
        for(int i=0;i<n;i++)
        {
            int j=(i+1)%n;
            point d=lineIntersection(vec[i], vec[j], a, b);
            if(pcmp(d,point(OO,OO)) && pointOnSegment(vec[i],vec[j],d))
                    inter.push_back(d);
        }
        sort(inter.begin(),inter.end(),pcmp);
        int sz=inter.size();
        bool f=1;
        for(int i=0;i<sz-1;i++)
        {
            bool flag=1;
            if(f)
                flag=0,com+=LEN(VEC(inter[i],inter[i+1]));
            f=!f;
            if(vertex.count(inter[i]) && vertex.count(inter[i+1]))
            {
                int a=vertex[inter[i]] ,b=vertex[inter[i+1]] ,c=b+1;
                int d=abs(a-b);
                if(d!=1 && d!=n-1) continue;
                if(a>b && b)
                {
                    c=a;
                    a=b-1;
                }
                if(c<n && a>=0)
                {
                    if(flag) com+=LEN(VEC(inter[i],inter[i+1]));
                    f = (cross3(vec[a],vec[b],vec[c])<EPS);
                }
            }
        }
        cout<<com<<endl;
    }
    return 0;
}
