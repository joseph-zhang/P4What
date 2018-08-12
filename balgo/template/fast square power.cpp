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
*    由于矩阵乘法满足结合律,所以可以进行快速幂.
*    具体的思想是分治,方法和数的快速幂完全一致,只要将数的乘法换成矩阵乘法即可.
*    此思路可进一步扩展为矩阵快速幂取模,大同小异,思想不变.
*/

const int maxn = 50,maxm = 50;
struct Matrix{
	int val[maxn][maxn];
	Matrix(){memset(val,0,sizeof(val));};
};

Matrix multi(Matrix& A,Matrix& B,int n,int m,int l){ //A(n x m),B(m x l) return C(n x l)
	Matrix C;
	for(int i = 0;i < n;i++){
		for(int k = 0;k < l;k++)
			for(int j = 0;j < m;j++)
				C.val[i][k] += A.val[i][j]*B.val[j][k];	
	}
	return C;
}
Matrix fastpow(Matrix A,int b,int n){ //要跟自己乘的话得是方阵
	Matrix R;
	for(int i = 0;i < n;i++)R.val[i][i] = 1;//初始化为单位阵
	for(;b;b>>=1){
		if(b&1)R= multi(R,A,n,n,n);
		A = multi(A,A,n,n,n);
	}
	return R;
}
int main(){
	int n,b;
	Matrix A;
	printf("your matrix's width? ");
	scanf("%d",&n);
	printf("Now give me your matrix.\n");
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			scanf("%d",&A.val[i][j]);
	printf("the power indicator is? ");
	scanf("%d",&b);	
	Matrix C = fastpow(A,b,n);
	printf("result is:\n");
	for(int i = 0;i < n;i++){
		for(int j = 0;j < n;j++)
			cout << C.val[i][j] << " ";
		cout << endl;
	}
	return 0;
}
