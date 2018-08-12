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
*    ����ɭ��(Simpson)����ֵ���ֵ�һ��.
*    ����ɭ���㹫ʽ����������ȷֵ������������л��ֲ�ֵ,��ţ��-����˹��ʽn=2ʱ������.
*    ���Կ����Ǿ��η������η��������汾,�Ѿض���Ϊ���������ƽ�.
*    ��ȡ��Խ�ྫ�Ⱦ�Խ��,������ҲԽ��. ���һ������������:ȡ���ٸ���,������ȡ����?
*    �������,���׽��Ƶĵط�Ҫ��ȡ����,�����з�϶�ĵط���ȡ����.
*    ������������Ȼ�Բ�ͬ�ı������������Լ��ĺ���ȡ��.
*    Ϊ����������,����������Ӧ�ķ���.�趨��ֵ,�����Ƚ�,��֪��ȡ�úϲ�����,�ò����ٶ�ȡЩ.
*    ʵ�ֲ��þ��ȵ�Ϊdouble,Ҳ���Ե���.
*    (��ع�ʽ��ͼʾ)
*/

//�豻��������������.
double f(double x){
	return (2+x*x); 
}

//��������ɭ.f�������ǵı�������(���ȫ�ֵ�)
double simpson(double x1, double x2){
	double c = x1+(x2-x1)/2.0;
	return (f(x1) + 4*f(c) + f(x2)) * (x2-x1) / 6.0;
}
//����Ӧ�ĵݹ����,��֪����[x1,x2]�ϵ���������ɭֵ��A
double asr(double x1, double x2, double A, double eps){
	double c = x1+(x2-x1)/2.0;
	double L = simpson(x1, c);	// dx��һ����
	double R = simpson(c, x2);	// dx��һ����
	//��ʽ(�����������������в�������)
	if (fabs(L+R-A) <= 15*eps)	// ��������㹻С
		return L+R+(L+R-A)/15.0;
	// ���������̫��
	return asr(x1, c, L, eps/2.0) + asr(c, x2, R, eps/2.0);//�ֱ���������ټ�����	
}
//������[a,b]�ϻ���
double integrate(double a, double b){
	// dx��ʼֵ��b-a
	//eps������Ҫ�Լ���
	return asr(a, b, simpson(a, b), 1e-5);
}
int main(){
	double a,b;
	printf("Give me your interval-> ");
	scanf("%lf%lf",&a,&b);
	printf("the integrate result is %.3lf.\n",integrate(a,b));
	cout << endl;
	return 0;
}

/**
*    #�����İ汾.
*    ������һЩ�ظ�����,�ݹ���̶�����������:���˵���е�ĺ���ֵ. 
*    ʵ������Ҫ�鷳һЩ,���Ǹ���.

double simpson(double a, double b,double fa, double fb, double fc){
	return (fa + fb + 4*fc) * (b-a) / 6;
}

double asr(double a, double b, double c,
		  double fa, double fb, double fc,
		  double A, double eps){
	double d = (a+c) / 2, e = (c+b) / 2;
	double fd = f(d), fe = f(e);
	double L = simpson(a, c, fa, fc, fd);
	double R = simpson(c, b, fc, fb, fe);
	if (fabs(L+R-A) <= 15*eps)
		return L+R+(L+R-A)/15;
	return asr(a, c, d, fa, fc, fd, L, eps/2)
		 + asr(c, b, e, fc, fb, fe, R, eps/2);
}

double integrate(double a, double b){
	double c = (a + b) / 2;
	double fa = f(a), fb = f(b), fc = f(c);
	return asr(a, b, c, fa, fb, fc,
			   simpson(a, b, fa, fb, fc), 1e-3);
}
*/
