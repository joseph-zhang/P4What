#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
/**
*    ��λ:һ����,������ʲô����,���н���λ,ÿһλ����λ������λ.
*    ��ν��λdp,��������λ�Ͻ���dp.һ�����Ҫͳ������[le,ri]������ĳ(Щ)�������ĸ���.
*    ������λ��Ϊ�˷��㶨��״̬,��λDP�����º���������,�����ǿ����Ͻ��ö��.
*    ��Ҫ�ر�ע�����ʹ�ü��仯ʱһ��Ҫ�ж�limit�Ա�֤״̬Ψһ,��Ȼ���Ǵ��.(��ʱǰ����Ҳ��ЩӰ��)
*    һ�����Ǽ�����limit�µ�״̬��ֵ,��Ϊ��limit�����û��ô��.
*    �������������HDU2098,HDU4734,POJ3252...
*    һ�������ͳ�������������������������ĺ�:HDU4507,�������������λ������posλ��ö�ٶ��ܺϵĹ���
*    ����DP��Ϊ�������,���ԱȽ�ģʽ��,һ���ü��仯����.�����չʾ�˴��µ�����,���Ը��ݾ��������ͨ.
*/

int a[20];
LL dp[20][state];//��ͬ��Ŀ�����״̬���岻ͬ,��ΧҲ��ͬ
LL dfs(int pos,/*state����*/,bool lead,bool limit){//����ÿ���ⶼҪ�ж�ǰ����
    //�ݹ�߽磬��Ȼ�ǰ�λö�٣����λ��0����ôpos==-1˵���������ö������
	//����һ�㷵��1����ʾ��ö�ٵ�������ǺϷ��ģ���ô�������Ҫ����ö��ʱ����ÿһλ��Ҫ������Ŀ����.
   if(pos==-1) return 1;
    //�ڶ������Ǽ��仯,Ҫ����������(�ڴ�ǰ���ܲ�ͬ��Ŀ������һЩ��֦)
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
    int up=limit?a[pos]:9;//����limit�ж�ö�ٵ��Ͻ�up;
    LL ans=0;
    //��ʼ�Ա�λ(pos)ö��
    for(int i=0;i<=up;i++){
        if() ...
        else if()...
        ans+=dfs(pos-1,/*״̬ת��*/,lead && i==0,limit && i==a[pos]) //��������������ζ�������д��
        /*���ﻹ��Ƚ����,��Ҳ�Ǻ��й��ɵ�
         Ʃ��˵���ҵ�ǰ��λö�ٵ�����i��Ȼ�������Ŀ��Լ��������������.
         ��Ҫ����state��������֤i�ĺϷ��ԣ�����:
         Ҫ����λ�ϲ�����62��������,��ô����state����Ҫ����ǰһλpre,Ȼ����࣬
         ǰһλ�����6��ô����ζ�Ͳ�����2*/
    }
    //�����꣬��¼״̬
    if(!limit && !lead) dp[pos][state]=ans;
    /*�����Ӧ����ļ��仯,Ҫ����������.
	  ��Ȼ���Լ����������Ҫ����lead������lead�Ͳ��ù�*/
    return ans;
}
LL solve(LL x){
    int pos=0;
    while(x){//����λ���ֽ����
        a[pos++]=x%10;//��������ϲ�����Ϊ[0,pos),�����ߵľͰ��Լ�ϰ����������ע����λ�߽����
        x/=10;
    }
	//�տ�ʼ���λ���������Ʋ�����ǰ����ģ���Ȼ�����λ��Ҫ�ߵ�һλҪ��Ϊ0
    return dfs(pos-1/*�����λ��ʼö��*/,/*һϵ��״̬ */,true,true);
}
int main(){
    LL le,ri;
    while(~scanf("%lld%lld",&le,&ri)){
        memset(dp,-1,sizeof(dp));//��ʼ��dp����Ϊ-1,��ͬ���⻹�������Ż�
		//ע��le�ķ�Χ�Ǵ���0��,�������0��ֱ�Ӿ���solve(ri)��,�ò��ż�
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}
