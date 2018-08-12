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
*    辛普森法(Simpson)是数值积分的一种.
*    辛普森三点公式利用区间二等分的三个点来进行积分插值,是牛顿-科特斯公式n=2时的情形.
*    可以看成是矩形法或梯形法的升级版本,把矩顶改为抛物线来逼近.
*    点取得越多精度就越高,计算量也越大. 如此一来就有了问题:取多少个点,在哪里取合适?
*    可以想见,容易近似的地方要少取几份,容易有缝隙的地方多取几份.
*    不过这样很显然对不同的被积函数都有自己的合适取法.
*    为解决这个问题,我们有自适应的方法.设定阈值,做做比较,就知道取得合不合适,用不用再多取些.
*    实现采用精度的为double,也可以调整.
*    (相关公式见图示)
*/

//设被积函数是抛物线.
double f(double x){
	return (2+x*x); 
}

//三点辛普森.f就是我们的被积函数(设成全局的)
double simpson(double x1, double x2){
	double c = x1+(x2-x1)/2.0;
	return (f(x1) + 4*f(c) + f(x2)) * (x2-x1) / 6.0;
}
//自适应的递归过程,已知区间[x1,x2]上的三点辛普森值是A
double asr(double x1, double x2, double A, double eps){
	double c = x1+(x2-x1)/2.0;
	double L = simpson(x1, c);	// dx变一半了
	double R = simpson(c, x2);	// dx变一半了
	//误差公式(关于其由来可以自行查阅资料)
	if (fabs(L+R-A) <= 15*eps)	// 面积差异足够小
		return L+R+(L+R-A)/15.0;
	// 面积差异仍太大
	return asr(x1, c, L, eps/2.0) + asr(c, x2, R, eps/2.0);//分别调整精度再继续来	
}
//在区间[a,b]上积分
double integrate(double a, double b){
	// dx初始值是b-a
	//eps根据需要自己设
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
*    #改良的版本.
*    减少了一些重复计算,递归过程多了三个参数:两端点和中点的函数值. 
*    实现起来要麻烦一些,但是更快.

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
