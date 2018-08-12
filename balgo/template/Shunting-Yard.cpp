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
*    波兰表达式(PN):表达式树的前缀(prefix)表示.
*    逆波兰表达式(RPN):表达式树的后缀(postfix)表示.
*    算数表达式(AN):表达式树的中缀(infix)表示.
*    运算符性质:优先级和结合性
*    Operator    Precedance    Associativity
*      阶乘          4             Right
*       *            3             Left         
*       /            3             Left
*       +            2             Left
*       -            2             Left
*/

/**
*    调度场算法(Shunting-Yard)可用于将算数表达式转换为RPN,省去了建立表达式树的麻烦.
*    具体的手段是利用stack.
*    扫描Token:
*        ->如果是运算数则加入que.
*        ->如果是运算符(O1)检查栈顶,while栈顶为运算符(O2):
*            (1)O1是左结合的,且O2优先级大于等于O1;
*            (2)O1是右结合的,且O2优先级大于O1;
*            将O2弹至que.
*        将O1压入栈.
*        ->如果是'(':将其压入栈.
*        ->如果是')':在遇到'('之前,不断将栈中op弹入que(最后舍弃'(').
*        ->如果Token已被扫完:将所有栈内余留的op弹入que.
*    结束,此时que内即存着RPN.
*    测试程式简要编写,包括四种运算符'+','-','*','/',并假设运算数只有个位数字.
*    (若不是个位数字加一个分词功能,在扫描的时候把数字分出来就行)
*/
const int maxn = 100;
vector<char> RPN;
stack<char> stk;
void ShuntingYard(char* str){
	char c;
	for(;*str;str++){
		if(*str>='0' && *str<='9'){RPN.push_back(*str);continue;}
		if(*str == '+' || *str == '-'){
			while(!stk.empty()){
				c = stk.top();
				if(c=='+'||c=='-'||c=='*'||c=='/'){RPN.push_back(c);stk.pop();}
				else break;
			}
			stk.push(*str);continue;
		}
		if(*str == '*'|| *str =='/'){
			while(!stk.empty()){
				c = stk.top();
				if(c=='*'||c=='/'){RPN.push_back(c);stk.pop();}
				else break;
			}
			stk.push(*str);continue;
		}
		if(*str == '('){stk.push('(');continue;}
		if(*str ==')'){
			while(!stk.empty()){
				c = stk.top();
				if(c!='('){RPN.push_back(c);stk.pop();}
				else break;
			}
			if(!stk.empty())stk.pop();
		}
	}
	while(!stk.empty()){RPN.push_back(stk.top());stk.pop();}
}

int main(){
	char str[maxn];
	printf("Now give me your arithmetical notion: ");
	scanf("%s",str);
	ShuntingYard(str);
	printf("The result RPN is: ");
	for(int i = 0;i < RPN.size();i++)cout << RPN[i];
	cout << endl;
	return 0;
}
