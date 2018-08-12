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
*    高斯消去(Gaussian Elimination)可用于求逆矩阵,解方程组等.
*    基本思路是先将系数矩阵化为上三角矩阵,再进行回代过程.
*    利用列主元法以提高数值稳定性.
*    设系数矩阵为可逆方阵,构成的增广矩阵为 A,有 n 行 n+1 列.A[i][n]是第i个方程右边的常数bi
*    程式运行结束后A[i][n]是第i个未知数的值。
*/
const int maxn = 50;
typedef double Matrix[maxn][maxn];
int n;
void gaussian(Matrix A,int n){
	int i,j,k,r;

	cout << endl;
	//消去过程
	for(int i = 0;i < n;i++){
		//尝试选一行r与当前行i进行交换
		for(r = i,j = i+1;j<n;j++)
			if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
		if(r!=i)for(j = 0;j <=n;j++)swap(A[i][j],A[r][j]);
		//消元
		for(j = n;j >= i;j--)
			for(k = i+1;k<n;k++)
				A[k][j] -= A[k][i]/A[i][i]*A[i][j];
	}
	//回代过程
	for(i = n-1;i >=0;i--){
		for(j = i+1;j<n;j++)
			A[i][n] -= A[j][n]*A[i][j];
		A[i][n] /= A[i][i];
	}
}

int main(){
	printf("what is the value of n(<50)? ");
	scanf("%d",&n);
	printf("Now give me your matrix.\n");
	Matrix A;
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n+1;j++)
			scanf("%lf",&A[i][j]);
	gaussian(A,n); 
	printf("Answer is:\n");
	for(int i = 0;i < n;i++)cout << A[i][n] << endl;
	return 0;
}

