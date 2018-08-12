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
*    几何问题通常编码都比较麻烦,内容较多.
*    给出的程式只是一些很基础的几何内容,在二维下讨论.
*    先给出一些基本的几何要素,然后说几种常用二维几何算法.
*/

//点的结构
struct Point{
	double x,y;
	Point(double x_ = 0,double y_ = 0):x(x_),y(y_){}
};
typedef Point Vector //因为向量结构的实现和点的完全一致,只是名字不同,所以这样搞一下
//向量+向量=向量
Vector operator +(Vector A,Vector B){return Vector(A.x+B.x,A.y+B.y);}
//向量-向量=向量
Vector operator -(Vector A,Vector B){return Vector(A.x-B.x,A.y-B.y);}
//向量*数=向量
Vector operator *(Vector A,double p){return Vector(A.x*p,A.y*p);}
//向量/数=向量
Vector operator /(Vector A,double p){return Vector(A.x/p,A.y/p);}
//定义点的偏序关系:越靠近西南方向越小
bool operator <(const Point& a,const Point& b){
	return a.x<b.y || (a.x==b.x && a.y < b.y);
}
const double eps = 1e-10; //ε(epsilon),代表很小的数值
//dcmp用于减少精度问题
int dcmp(doouble x){ 
	if(fabs(x) < eps)return 0;
	else return x<0?-1:1;
}
//定义点的相等关系
bool operator ==(const Point& a,const Point& b){
	return (!dcmp(a.x-b.x)) && (!dcmp(a.y-b.y));
}
//向量间点积
double Dot(Vector A,Vector B){return A.x*B.x+A.y*B.y;}
//向量间叉积
double Cross(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
//向量的模(范数)
double Length(Vector A){return sqrt(Dot(A,A));}
//两向量间夹角
double Angle(Vector A,Vector B){return acos( Dot(A,B)/Length(A)/Length(B) );}
//向量间有向面积(其绝对值为所构成的三角形面积的两倍)
double Area2(Point A,Point B,Point C){return Cross(B-A,C-A);}
//向量绕起点逆时针旋转α弧度: x' = xcosα-ysinα,y'=xsinα+ycosα;
Vector Rotate(Vector A,double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
//计算向量的单位法向量,即顺时针转90°,然后归一化(调用前确保向量不为零向量)
Vector Normal(Vector A){
	double L = Length(A);
	return Vector(-A.y/L,A.x/L);
}
//直线,线段,射线的参数方程形式都是 A+(B-A)t,区别仅在于t的取值不同.
//两直线P+vt,Q+wt的交点(调用前确保有唯一交点,即Cross(v,w)非0)
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u = P-Q;
	double t = Cross(w,u)/Cross(v,w);
	return P+v*t;
}
//点到直线的距离
double DistanceToLine(Point P,Point A,Point B){
	Vector v1 = B-A,v2 = P-A;
	return fabs(Cross(v2,v2))/Length(v1); //若不取绝对值,得到的是有向距离
}
//点到线段的距离有两种情况
double DistanceToSegment(Point P,Point A,Point B){
	if(A==B)return Length(P-A);
	Vector v1 = B-A,v2 = P-A,v3 = P-B;
	if(dcmp(Dot(v1,v2)) < 0) return Length(v2);
	else if(dcmp(Dot(v1,v3)) > 0) return Length(v3);
	else return fabs(Dot(v1,v2))/Length(v1); 	
}
//线段的规范相交判定.规范相交:两线段恰有一公共点,且它不是任何一条线段的端点
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
		   c3 = Cross(b2-b1,a1-b1), c4 = Cross(b2-b1,a2,b1);
	return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
//点在线段上的判定(不含端点)
bool OnSegment(Point p,Point a1,point a2){
	return dcmp(Cross(a1-p,a2-p))==0 && dcmp(Dot(a1-p,a2-p))<0;
}
typedef Polygon vector<Point>;
//多边形有向面积(选p[0]为划分点时的程式)
double PlygonArea(Point* p,int n){
	double area = 0;
	for(int i = 1;i < n-1;i++)
		area += Cross(p[i]-p[0],p[i+1]-p[0]);
	return area/2;
}
/**
*    点在多边形内判定(转角法):
*    假设有一条从p向东的射线,统计多边形穿过射线正反多少次(绕数).
*    转完一圈后,看下绕数是否为零.
*/
int isPointInPolygon(Point p,Polygon poly){
	int wn;//绕数
	int n = poly.size():
	for(int i = 0;i < n;i++){
		if(isPointOnSegment(p,ploy[i],poly[(i+1)%n]))return -1; // 在边界上
		int k = dcmp(Cross(ploy[(i+1)%n]-ploy[i],p-ploy[i]));
		int d1 = dcmp(ploy[i].y-p.y);
		int d2 = dcmp(ploy[(i+1)%n].y-p.y);
		if(k>0 && d1<=0 && d2>0)wn++;
		if(k<0 && d2<=0 && d1>0)wn--;
	}
	if(wn) return 1; //p在多边形内部
	return 0;        //p在多边形外部
}
/**
*    点集P的凸包:有P的任意子集S,满足:S围成了凸多边形且包围P.
*                取其中面积最小的一个凸多边形称为凸包
*    计算凸包(Andrew演算法):O(nlogn)
*    求凸包就是将满足定义的子集S求出来.
*    先将点都排好序,删除重复点,得到排列p1,p2,p3,...,pn.
*    将p1,p2放入凸包,从p3开始,当新点在凸包"前进"方向左边时继续加入凸包中.
*    否则,按加入顺序依次从最近加入凸包的点删除,直到新点在"前进"方向左边.
*    重复上述过程,直到碰到pn,就求出了"下凸包".
*    再从pn开始反过来做一遍,就求出了"上凸包"。
*    下凸包和上凸包合并起来就是点集的凸包.
*/
//函数返回凸包顶点个数,S保留在点集ch内,输入为点集p,含有n个点
//程式的设计假设p中无重复点
//如果不希望有输入点落在凸包的边上,将两个 <= 改为 <
//在精度要求高时要用dcmp比较 
int Andrew(Point* p,int n,Point* ch){
	sort(p,p+n);
	int m = 0; //统计S中有多少个点
	for(int i = 0;i < n;i++){
		while(m > 1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <=0)m--;
		ch[m++] = p[i];
	}
	int k = m;
	for(int i = n-2;i>=0;i--){
		while(m>k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <=0)m--;
		ch[m++] = p[i];
	}
	if(n>1)m--;
	return m;
}
//有向直线:常用来表示半平面,其左侧二维空间即是其所代表的半平面
struct Line{
	Point P;//直线上任意一点
	Vector v;//方向向量
	double ang;//极角,即从x正半轴逆时针旋转到v所需的弧度,計算結果是在值域(-π,π]內的弧度
	Line(){}
	Line(Point p_,Vector v_):P(P_),v(v_){ang = atan2(v.y,v.x);}
	bool operator < (const Line& L)const{ //定义偏序,以备排序
		return ang < L.ang;
	}
};
/**
*    半平面交的算法和求凸包类似,不过算凸包中用的是栈型,而下属算法用的是双端队列.
*    需要注意的是有向直线排序完后,每次新加入的半平面可能会让队尾半平面变得"无用",需要删去.
*    由于极角序是环形的,新加的半平面也可能"绕了一圈"后,使队首的半平面变得"无用".
*
*
*/