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
*    表达式分类:前缀表达式(PN),中缀表达式(CAN),后缀表达式(RPN)
*    PN:波兰表达式,RPN:逆波兰表达式,CAN:算术表达式
*    表达式解析可以通过建立表达式树进行,也可以利用调度场算法,以此进行表达式间的互换.
*    下述演算法可以进行PN/RPN的计算:
*    	扫描整个字符串(若是PN则从右自左扫描):
*           (1)若是数字val,则压入栈顶.
*           (2)若是二元运算符op,则依次弹出栈中两个数字 val1,val2,计算val1 op val2并压栈.
*       扫描结束后,栈顶就是结果.
*    程式简要编写,假设运算数都只是个位数字,且只包含"+","-","*","/"四则运算.
*/
const int maxn = 1000;
stack<int> stk;
int calc(char* str){
	int len = strlen(str);
	for(int i = len-1;i >=0;i--){
		if(str[i] >= '0' && str[i] <= '9')stk.push(str[i]-'0');
		else{
			int val1 = stk.top();stk.pop();
			int val2 = stk.top();stk.pop();
			int val;
			switch(str[i]){
				case '+': {val = val1 + val2;break;}
				case '-': {val = val1 - val2;break;}
				case '*': {val = val1 * val2;break;}
				case '/': {val = val1 / val2;break;}
			}
			stk.push(val);
		}
	}
	return stk.top();
}

int main(){
	while(!stk.empty())stk.pop();
	char str[maxn];
	printf("input your PN (Polish Notion).\n");
	scanf("%s",str);
	cout << "result is: " << calc(str) << endl; 
	return 0;
}


