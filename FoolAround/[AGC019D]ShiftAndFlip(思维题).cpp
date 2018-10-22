#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int A[N<<2],B[N<<2];
int sa[N<<2],sb[N<<2];
int nxl[N<<2],nxr[N<<2];
char ss1[N],ss2[N];
int len,ans=INT_MAX;
int R[N<<2];

void xi_jin_ping_is_good()
{
    nxl[0]=-1;nxr[3*len-1]=3*len;
    for(int i=1;i<3*len;i++) nxl[i]=B[i]?i:nxl[i-1];
    for(int i=3*len-2;i>=0;i--) nxr[i]=B[i]?i:nxr[i+1];
    for(int k=0;k<len;k++)
    {
        int cnt=0,dafa=INT_MAX,mxr=0;
        memset(R,0,sizeof(R));
        for(int i=len;i<2*len;i++)
        {
            if(A[i]==B[i+k]) continue;
            cnt++;R[i-nxl[i]]=max(R[i-nxl[i]],nxr[i]-i-k);
        }
        if(cnt==0){ans=min(ans,k);continue;}
        for(int i=len-1;i>=0;i--)
            dafa=min(dafa,mxr+i),mxr=max(mxr,R[i]);
        ans=min(ans,cnt+k+dafa*2);
    }
}

int main()
{
    scanf("%s",ss1);len=strlen(ss1);scanf("%s",ss2);
    for(int i=0;i<len;i++) A[i]=A[i+len]=A[i+2*len]=ss1[i]-'0';
    for(int i=0;i<len;i++) B[i]=B[i+len]=B[i+2*len]=ss2[i]-'0';
    sa[0]=A[0];sb[0]=B[0];
    for(int i=1;i<3*len;i++) sa[i]=sa[i-1]+A[i],sb[i]=sb[i-1]+B[i];
    if(!sb[len-1]&&sa[len-1]) return puts("-1"),0;
    xi_jin_ping_is_good();
    reverse(A,A+3*len);
    reverse(B,B+3*len);
    xi_jin_ping_is_good();
    printf("%d\n",ans);
    return 0;
}