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
*    数位:一个数,无论是什么进制,都有进制位,每一位进制位就是数位.
*    所谓数位dp,就是在数位上进行dp.一般就是要统计区间[le,ri]内满足某(些)条件数的个数.
*    引入数位是为了方便定义状态,数位DP做的事和搜索相似,但它是控制上界的枚举.
*    需要特别注意的是使用记忆化时一定要判断limit以保证状态唯一,不然就是错的.(有时前导零也有些影响)
*    一般我们记忆无limit下的状态的值,因为有limit的情况没那么多.
*    最基础的例子有HDU2098,HDU4734,POJ3252...
*    一类变形是统计区间内满足条件的所有数的和:HDU4507,解决方法是用数位考虑在pos位的枚举对总合的贡献
*    这类DP因为很像回溯,所以比较模式化,一般用记忆化搜索.下面就展示了大致的流程,可以根据具体问题变通.
*/

int a[20];
LL dp[20][state];//不同题目定义的状态含义不同,范围也不同
LL dfs(int pos,/*state变量*/,bool lead,bool limit){//不是每种题都要判断前导零
    //递归边界，既然是按位枚举，最低位是0，那么pos==-1说明这个数我枚举完了
	//这里一般返回1，表示你枚举的这个数是合法的，那么这里就需要你在枚举时必须每一位都要满足题目条件.
   if(pos==-1) return 1;
    //第二个就是记忆化,要有条件限制(在此前可能不同题目还能有一些剪枝)
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
    int up=limit?a[pos]:9;//根据limit判断枚举的上界up;
    LL ans=0;
    //开始对本位(pos)枚举
    for(int i=0;i<=up;i++){
        if() ...
        else if()...
        ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的
        /*这里还算比较灵活,但也是很有规律的
         譬如说，我当前数位枚举的数是i，然后根据题目的约束条件分类讨论.
         还要根据state变量来保证i的合法性，比如:
         要求数位上不能有62连续出现,那么就是state就是要保存前一位pre,然后分类，
         前一位如果是6那么这意味就不能是2*/
    }
    //计算完，记录状态
    if(!limit && !lead) dp[pos][state]=ans;
    /*这里对应上面的记忆化,要有条件限制.
	  当然如果约束条件不需要考虑lead，这里lead就不用管*/
    return ans;
}
LL solve(LL x){
    int pos=0;
    while(x){//把数位都分解出来
        a[pos++]=x%10;//个人老是喜欢编号为[0,pos),看不惯的就按自己习惯来，反正注意数位边界就行
        x/=10;
    }
	//刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位要视为0
    return dfs(pos-1/*从最高位开始枚举*/,/*一系列状态 */,true,true);
}
int main(){
    LL le,ri;
    while(~scanf("%lld%lld",&le,&ri)){
        memset(dp,-1,sizeof(dp));//初始化dp数组为-1,不同问题还可以有优化
		//注意le的范围是大于0的,如果等于0那直接就是solve(ri)了,用不着减
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}
