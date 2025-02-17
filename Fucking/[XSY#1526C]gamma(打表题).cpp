#include<bits/stdc++.h>
using namespace std;

int e[8][8];
int pos[8];

double gao(int n)
{
    int h=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i<j) h=h*2+e[pos[i]][pos[j]];
    if(n==3)
    {
        if(h==0) return 0.0;
        if(h==1) return 0.0;
        if(h==3) return 0.42139;
        if(h==7) return 0.4164803;
    }
    if(n==4)
    {
        if(h==0) return 0.0;
        if(h==1) return 0.0;
        if(h==3) return 0.42139;
        if(h==7) return 0.4164803;
        if(h==11) return 0.4208031;
        if(h==12) return 0.0;
        if(h==13) return 0.6773771;
        if(h==15) return 0.4150774;
        if(h==30) return 0.5899929;
        if(h==31) return 0.5231664;
        if(h==63) return 0.5017010;
    }
    if(n==5)
    {
        if(h==0) return 0.0000000;
        if(h==1) return 0.0000000;
        if(h==3) return 0.4214005;
        if(h==7) return 0.4164650;
        if(h==11) return 0.4208385;
        if(h==12) return 0.0000000;
        if(h==13) return 0.6773138;
        if(h==15) return 0.4150569;
        if(h==30) return 0.5900469;
        if(h==31) return 0.5231296;
        if(h==63) return 0.5016357;
        if(h==75) return 0.4270769;
        if(h==76) return 0.4213803;
        if(h==77) return 0.4478924;
        if(h==79) return 0.4242890;
        if(h==86) return 0.3929320;
        if(h==87) return 0.3994113;
        if(h==94) return 0.4812546;
        if(h==95) return 0.4088833;
        if(h==116) return 0.4163904;
        if(h==117) return 0.4901828;
        if(h==119) return 0.4353842;
        if(h==127) return 0.3832643;
        if(h==222) return 0.3804121;
        if(h==223) return 0.3925042;
        if(h==235) return 0.4192791;
        if(h==236) return 0.3616700;
        if(h==237) return 0.3710545;
        if(h==239) return 0.4479530;
        if(h==254) return 0.3591758;
        if(h==255) return 0.3698481;
        if(h==507) return 0.4458330;
        if(h==511) return 0.4246259;
        if(h==1023) return 0.3808523;
    }
    if(n==6)
    {
        if(h==0) return 0.0000000;
        if(h==1) return 0.0000000;
        if(h==3) return 0.4214029;
        if(h==7) return 0.4163907;
        if(h==11) return 0.4208321;
        if(h==12) return 0.0000000;
        if(h==13) return 0.6772946;
        if(h==15) return 0.4151320;
        if(h==30) return 0.5899923;
        if(h==31) return 0.5231549;
        if(h==63) return 0.5017284;
        if(h==75) return 0.4271694;
        if(h==76) return 0.4214335;
        if(h==77) return 0.4478524;
        if(h==79) return 0.4243862;
        if(h==86) return 0.3928705;
        if(h==87) return 0.3994147;
        if(h==94) return 0.4812697;
        if(h==95) return 0.4089018;
        if(h==116) return 0.4164836;
        if(h==117) return 0.4901441;
        if(h==119) return 0.4354414;
        if(h==127) return 0.3832947;
        if(h==222) return 0.3804368;
        if(h==223) return 0.3924780;
        if(h==235) return 0.4192805;
        if(h==236) return 0.3617473;
        if(h==237) return 0.3710604;
        if(h==239) return 0.4479171;
        if(h==254) return 0.3591157;
        if(h==255) return 0.3698490;
        if(h==507) return 0.4457437;
        if(h==511) return 0.4246857;
        if(h==1023) return 0.3808357;
        if(h==1099) return 0.4112431;
        if(h==1100) return 0.4208275;
        if(h==1101) return 0.4087889;
        if(h==1103) return 0.4115296;
        if(h==1108) return 0.6652649;
        if(h==1109) return 0.6079869;
        if(h==1110) return 0.4129416;
        if(h==1111) return 0.4275111;
        if(h==1118) return 0.4069093;
        if(h==1119) return 0.4037312;
        if(h==1140) return 0.5784144;
        if(h==1141) return 0.4946950;
        if(h==1143) return 0.3783237;
        if(h==1151) return 0.4031379;
        if(h==1182) return 0.4991599;
        if(h==1183) return 0.5025346;
        if(h==1184) return 0.0000000;
        if(h==1185) return 0.6773191;
        if(h==1187) return 0.4133685;
        if(h==1191) return 0.3933950;
        if(h==1194) return 0.4150787;
        if(h==1195) return 0.4070779;
        if(h==1196) return 0.5778063;
        if(h==1197) return 0.5007651;
        if(h==1198) return 0.5096731;
        if(h==1199) return 0.3892531;
        if(h==1214) return 0.4935427;
        if(h==1215) return 0.4554628;
        if(h==1246) return 0.4408735;
        if(h==1247) return 0.4090881;
        if(h==1259) return 0.4109331;
        if(h==1260) return 0.3836890;
        if(h==1261) return 0.4367861;
        if(h==1263) return 0.4125483;
        if(h==1268) return 0.3928512;
        if(h==1269) return 0.4432749;
        if(h==1270) return 0.3723949;
        if(h==1271) return 0.3772312;
        if(h==1278) return 0.4018813;
        if(h==1279) return 0.3816390;
        if(h==1456) return 0.5899695;
        if(h==1457) return 0.3878418;
        if(h==1459) return 0.3739191;
        if(h==1460) return 0.5232567;
        if(h==1461) return 0.4420141;
        if(h==1463) return 0.3794537;
        if(h==1465) return 0.3780744;
        if(h==1467) return 0.4106790;
        if(h==1468) return 0.3777367;
        if(h==1469) return 0.4139292;
        if(h==1471) return 0.3953657;
        if(h==1531) return 0.4063948;
        if(h==1532) return 0.3566486;
        if(h==1533) return 0.3618340;
        if(h==1535) return 0.3878307;
        if(h==1972) return 0.5017100;
        if(h==1973) return 0.4123952;
        if(h==1975) return 0.3635054;
        if(h==1983) return 0.3562832;
        if(h==2047) return 0.3783781;
        if(h==3294) return 0.4619196;
        if(h==3295) return 0.4707934;
        if(h==3306) return 0.4051563;
        if(h==3307) return 0.4022022;
        if(h==3308) return 0.4549247;
        if(h==3309) return 0.4580476;
        if(h==3310) return 0.3752182;
        if(h==3311) return 0.4317276;
        if(h==3326) return 0.4153691;
        if(h==3327) return 0.4213839;
        if(h==3440) return 0.5155274;
        if(h==3441) return 0.4645503;
        if(h==3443) return 0.3734909;
        if(h==3447) return 0.3677305;
        if(h==3448) return 0.4576293;
        if(h==3449) return 0.3749328;
        if(h==3451) return 0.3943871;
        if(h==3452) return 0.4343645;
        if(h==3453) return 0.4176025;
        if(h==3455) return 0.3682483;
        if(h==3576) return 0.4389395;
        if(h==3577) return 0.4225578;
        if(h==3578) return 0.3551206;
        if(h==3579) return 0.4118486;
        if(h==3582) return 0.3530360;
        if(h==3583) return 0.3620572;
        if(h==3873) return 0.5121914;
        if(h==3875) return 0.4549902;
        if(h==3879) return 0.3700049;
        if(h==3885) return 0.4362275;
        if(h==3887) return 0.4152965;
        if(h==3903) return 0.4202974;
        if(h==3947) return 0.3922442;
        if(h==3948) return 0.4354482;
        if(h==3949) return 0.3555411;
        if(h==3950) return 0.4160241;
        if(h==3951) return 0.4091481;
        if(h==3958) return 0.3570961;
        if(h==3959) return 0.3547658;
        if(h==3966) return 0.3552521;
        if(h==3967) return 0.3966696;
        if(h==4094) return 0.3458427;
        if(h==4095) return 0.3548140;
        if(h==7672) return 0.4315369;
        if(h==7673) return 0.4128421;
        if(h==7675) return 0.3620403;
        if(h==7679) return 0.3617178;
        if(h==7902) return 0.4046642;
        if(h==7903) return 0.4041335;
        if(h==7915) return 0.3829404;
        if(h==7916) return 0.4272808;
        if(h==7917) return 0.4103857;
        if(h==7919) return 0.3600317;
        if(h==7934) return 0.3951984;
        if(h==7935) return 0.3883746;
        if(h==8185) return 0.3987970;
        if(h==8187) return 0.3467859;
        if(h==8191) return 0.3462579;
        if(h==16350) return 0.4047068;
        if(h==16351) return 0.3864551;
        if(h==16383) return 0.3801624;
        if(h==32767) return 0.3928691;
    }
    return -1.0;
}

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                scanf("%d",e[i]+j);
        double res;
        for(int i=1;i<=n;i++) pos[i]=i;
        do{
            res=gao(n);
            if(res>-0.5) break;
        }while(next_permutation(pos+1,pos+1+n));
        printf("%.4lf\n",res);
    }
    return 0;
}

//----------------以下是打表程序----------------

/*
#include<bits/stdc++.h>
using namespace std;

int e[8][8],n;
double val[8];
double ve[8][8];
int pos[8];
bool have[40000];

int biao(int n)
{
    int h=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i<j) h=h*2+e[pos[i]][pos[j]];
    return h;
}

int main()
{
    srand(time(0));
    n=6;int m=1<<(n*(n-1)/2);
    for(int ttt=0;ttt<m;ttt++)
    {
        int res,flag=0,xx=ttt;
        memset(e,0,sizeof(e));
        for(int i=n;i>=1;i--)
            for(int j=n;j>=1;j--)
                if(i<j) e[i][j]=e[j][i]=(xx&1),xx>>=1;
        for(int i=1;i<=n;i++) pos[i]=i;
        do{
            res=biao(n);
            if(have[res]){flag=1;break;}
        }while(next_permutation(pos+1,pos+1+n));
        if(flag) continue;
        have[ttt]=1;
        int T=100000000,succ=0;
        while(T--)
        {
            for(int i=1;i<=n;i++)
                val[i]=(double)rand()/RAND_MAX;
            for(int i=1;i<=n;i++)
                for(int j=i;j<=n;j++)
                    if(e[i][j]) ve[i][j]=ve[j][i]=(double)rand()/RAND_MAX+1;
            vector<double> vals;
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                {
                    if(!e[i][j]) continue;
                    for(int k=1;k<=n;k++)
                    {
                        if(i==k||j==k||!e[j][k]) continue;
                        double xx=-ve[i][j],yy=ve[j][k];
                        double A=val[i],B=val[j],C=val[k];
                        double a=(A-B-xx/yy*(C-B))/(xx*xx-xx*yy);
                        double b=(A-B-xx*xx*a)/xx,c=B;
                        vals.push_back((a*c*4-b*b)/(a*4));
                    }
                }
            if(vals.size()==0) break;
            sort(vals.begin(),vals.end());
            int k=vals.size();
            succ+=(vals[k-(k+1)/2]>0.618);
        }
        printf("if(h==%d) return %.7lf;\n",ttt,(double)succ/100000000.0);
    }
    return 0;
}
*/