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
*    �߾���(����) ������̫�������ڱ���������ȫ�Ų��µ����.
*    һ����˵������ģ��.
*    ���Կ�����������(�Ӽ��˳�)��������ģ��ķ���.
*    �ӷ��ͼ��������ַ�����ûʲô����,���Ƕ��ڳ˳���Ҳ������Ļ��ͱȽ���.
*    ����FFT�ķ���,���Կ����������ʽ�˻�.�����˷����Ե����Ƕ���ʽ�˷�������.
*    ���Ը߾��ȳ˷������FFT�����.
*    �����ʵ�ֽ����㶼�����һ������,�������.(ֻ���Ե�ʵ���˼ӷ�)
*    ����ʵ�ʵ�����������ؽ���ѡ��,��������.
*    (��ʵ���д����ಢ������ô����,java���Դ��Ĵ����������,��cppû��...)
*/

//ע�����ʵ�ֲ���ֱ�Ӷ��帺��
struct BigInteger {
	static const int BASE = 100000000;
	static const int WIDTH = 8;
	vector<int> s;

	BigInteger(long long num = 0) { *this = num; } // ���캯��
	BigInteger operator = (long long num) { // Ϊ�������帳ֵ
		s.clear();
		do {
			s.push_back(num % BASE);
			num /= BASE;
		} while(num > 0);
		return *this;
	}
	BigInteger operator = (const string& str) { // Ϊ�ַ������帳ֵ
		s.clear();
		int x, len = (str.length() - 1) / WIDTH + 1;//��һ���ܸպó���
		for(int i = 0; i < len; i++) {
			int end = str.length() - i*WIDTH;
			int start = max(0, end - WIDTH);//ע�����һ�ο��ܽصĲ���8��
			sscanf(str.substr(start, end-start).c_str(), "%d", &x);//һ��Ҫд��end-start
			s.push_back(x);
		}
		return *this;
	}
	BigInteger operator + (const BigInteger& b) const { //����ӷ�
		BigInteger c;
		c.s.clear();
		int g = 0; //g���ڱ�����������
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
	// ƫ���ϵ
	bool operator < (const BigInteger& b)const {
		if(s.size()!=b.s.size())return s.size() < b.s.size(); //ע������������ǰ����
		for(int i = s.size()-1;i >=0;i--){
			if(s[i]!=b.s[i])return s[i] < b.s[i];
		}
		return false;//���
	}
	bool operator >  (const BigInteger& b)const{return b < *this;}
	bool operator <= (const BigInteger& b)const{return !(b<*this);}
	bool operator >= (const BigInteger& b)const{return !(*this < b);}
	bool operator == (const BigInteger& b)const{return !(*this < b) && !(b < *this);}
	bool operator != (const BigInteger& b)const{return (*this < b) || (b < *this);}
};

//������ʾ�ķ���
ostream& operator << (ostream &out, const BigInteger& x) {
	out << x.s.back();
	for(int i = x.s.size()-2; i >= 0; i--) {
		char buf[20];
		sprintf(buf, "%08d", x.s[i]);
		for(int j = 0; j < strlen(buf);j++) out << buf[j];
	}
	return out;
}
//��������ķ���
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
