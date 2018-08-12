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
*    高精度(大数) 用于数太大以至于变量类型完全放不下的情况.
*    一般来说方法是模拟.
*    可以看到四则运算(加减乘除)都可以用模拟的方法.
*    加法和减法用这种方法是没什么问题,但是对于乘除法也这样搞的话就比较慢.
*    借由FFT的方法,可以快速算出多项式乘积.大数乘法可以当成是多项式乘法的特例.
*    所以高精度乘法最好用FFT来设计.
*    下面的实现将运算都封进了一个类里,方便调用.(只粗略地实现了加法)
*    对于实际的问题可以灵活地进行选用,不必死板.
*    (在实际中大数类并不是那么常用,java有自带的大数类可以用,但cpp没有...)
*/

//注意这个实现不能直接定义负数
struct BigInteger {
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger(long long num = 0) { *this = num; } // 构造函数
	BigInteger operator = (long long num) { // 为整数定义赋值
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while(num > 0);
		return *this;
	}
	BigInteger operator = (const string& str) { // 为字符串定义赋值
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;//不一定能刚好除尽
		for(int i = 0; i < len; i++) {
			int end = str.length() - i*WIDTH;
			int start = max(0, end - WIDTH);//注意最后一次可能截的不是8个
			sscanf(str.substr(start, end-start).c_str(), "%d", &x);//一定要写成end-start
			s.push_back(x);
		}
		return *this;
	}
	BigInteger operator + (const BigInteger& b) const { //定义加法
		BigInteger c;
		c.s.clear();
		int g = 0; //g用于保存多出来的量
		for(int i = 0;;i++) {
			if(g == 0 && i >= s.size() && i >= b.s.size()) break;
			int x = g;
			if(i < s.size()) x += s[i];
			if(i < b.s.size()) x += b.s[i];
			c.s.push_back(x % BASE);
			g = x / BASE;
		}
		return c;
	}
	// 偏序关系
	bool operator < (const BigInteger& b)const {
		if(s.size()!=b.s.size())return s.size() < b.s.size(); //注意两数不能有前导零
		for(int i = s.size()-1;i >=0;i--){
			if(s[i]!=b.s[i])return s[i] < b.s[i];
		}
		return false;//相等
	}
	bool operator >  (const BigInteger& b)const{return b < *this;}
	bool operator <= (const BigInteger& b)const{return !(b<*this);}
	bool operator >= (const BigInteger& b)const{return !(*this < b);}
	bool operator == (const BigInteger& b)const{return !(*this < b) && !(b < *this);}
	bool operator != (const BigInteger& b)const{return (*this < b) || (b < *this);}
};

//定义显示的方法
ostream& operator << (ostream &out, const BigInteger& x) {
	out << x.s.back();
	for(int i = x.s.size()-2; i >= 0; i--) {
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for(int j = 0; j < strlen(buf);j++) out << buf[j];
	}
	return out;
}
//定义输入的方法
istream& operator >> (istream &in, BigInteger& x) {
	string s;
	if(!(in >> s)) return in;
	x = s;
	return in;
}


int main() {
	BigInteger seq[20];
	int n;
	printf("How many numbers? ");
	scanf("%d",&n);
	printf("Now give me.\n");
	for(int i = 0;i <n;i++)cin >> seq[i];
	printf("Sorting...\n");
	sort(seq,seq+n);
	printf("the result is:\n");
	for(int i = 0;i < n;i++)
		cout << seq[i] << endl;
	return 0;
}
