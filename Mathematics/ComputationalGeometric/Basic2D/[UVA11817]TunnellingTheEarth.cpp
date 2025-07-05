#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int main()
{
    int t;
    double r=6371009;
    double lat1,lng1,lat2,lng2,x1,x2,y1,y2,z1,z2,d,d2;
    cin>>t;
    while(t--)
    {
        cin>>lat1>>lng1>>lat2>>lng2;
        lat1=lat1/180 * M_PI;
        lat2=lat2/180 * M_PI;
        lng1=lng1/180 * M_PI;
        lng2=lng2/180 * M_PI;
        x1 = r*cos(lat1)*cos(lng1);
        y1 = r*cos(lat1)*sin(lng1);
        z1 = r*sin(lat1);
        x2 = r*cos(lat2)*cos(lng2);
        y2 = r*cos(lat2)*sin(lng2);
        z2 = r*sin(lat2);
        d=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
        d2 = 2*asin(d/2/r)*r;
        cout<<(long long)(d2-d+0.5)<<endl;
    }
	return 0;
}
