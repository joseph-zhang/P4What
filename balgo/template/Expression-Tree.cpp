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
*    表达式树(Expression-Tree)可用于算数表达式的parsing,其结构是二叉树.
*    表达式树的叶节点上是数字,其它节点上是运算符.
*    建树的关键是找到"最后计算的运算符",并把它置为根然后递归地建树.
*    只考虑四则运算时,若括号外有加减号,他们肯定最后计算,若没有则考虑括号外乘除号.
*    "最后计算的运算符":括号外的,优先级最低的.(右结合的选最左边,左结合的选最右边)
*    下列程式简单的实现了表达式树的建立过程.(假设运算数都是个位数值)
*/

const int maxn = 1000;
int lch[maxn],rch[maxn]; //每个节点的左右子节点编号
char op[maxn]; //节点编号到运算符的映射
int nc = 0; //节点分配计数器(1,2,3,...)

//递归建树过程范围是字符串 s:[x,y)
int build(char* s,int x,int y){
	//p用于检测括号平衡.
	//c1,c2分别用于确定括号外"最右出现"的加减号和乘除号.
	int i,c1 = -1,c2 = -1,p = 0;
	int u;
	
	//递归边界:仅有一个字符
	if(y-x == 1){
		u = ++nc;
		lch[u] = rch[u] = 0;op[u] = s[x];
		return u;
	}
	for(i = x;i < y;i++){
		switch(s[i]){
			case '(':p++;break;
			case ')':p--;break;
			case'+':case'-':if(!p) c1 = i;break;
			case'*':case'/':if(!p) c2 = i;break;
		}
	}
	if(c1 < 0)c1 = c2; //找不到括号外的加减号,就进一步考虑乘除号
	if(c1 < 0)return build(s,x+1,y-1); //括号外连乘除号也找不到,说明整个表达式被括号包围
	u = ++nc;
	lch[u] = build(s,x,c1);
	rch[u] = build(s,c1+1,y);
	op[u] = s[c1];
	return u; //将根节点编号返回
}
//印出表达式树的后序遍历(RPN表达式)
void print(int u){
	if(!u)return;
	print(lch[u]);
	print(rch[u]);
	cout << op[u];
}
int main(){
	char s[maxn];
	printf("input your arithmetic notion.\n");
	scanf("%s",s);
	printf("constructing...\n");
	int root = build(s,0,strlen(s));
	printf("RPN of your Notion: ");
	print(root);
	cout << endl;
	return 0;
}
