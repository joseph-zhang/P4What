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
#include<complex> 
#define PI acos(-1.0) 
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;

/**
*    FFT是计算DFT的有效方法,一种实现是蝶形算法,由Cooley和Tukey提出.
*    具体的原理在信号分析中已经说的很详细了,下面就给出 基2-FFT 的程式.
*    拿到DFT后利用卷积定理就可以得到两个序列的卷积.过程很简单.
*    (注意在算之前先补零成为2的幂次个点,同时注意卷积的长度是 n1+n2-1)
*/

typedef complex<double> CD;
// Cooley-Tukey的FFT算法,迭代实现.inverse = false时计算IFFT
inline void FFT(vector<CD> &a, bool inverse) {
	int n = a.size(); //要计算的是n点DFT
	// 原地快速 位逆序置换(Bit Reversal)
	for(int i = 0, j = 0; i < n; i++) {
		if(j > i) swap(a[i], a[j]);
		int k = n;
		while(j & (k >>= 1)) j &= ~k;
		j |= k;
	}
	double pi = inverse ? -PI : PI;
	//合并(或说是可以分裂)lb(N)次
	for(int step = 1; step < n; step <<= 1) {
		// 我们要把相邻两个“step点DFT”(E和O)合并为一个“2*step点DFT”
		double alpha = pi / step;  //旋转因子 ω = e^(-2πj/2step) = e^(-πj/(2step/2))
		// 为求高效，我们并不是依次执行各个完整的DFT合并，而是枚举下标k
		// 对于一个下标k，执行所有DFT合并中该下标对应的蝶形操作，即通过E[k]和O[k]计算X[k]
		for(int k = 0; k < step; k++) {
			// 计算omega^k. 这个方法效率低，但如果用每次乘omega的方法递推会有精度问题。
			// 有更快更精确的递推方法，为了清晰起见这里略去(数论变换)
			CD omegak = exp(CD(0, alpha*k)); 
			for(int Ek = k; Ek < n; Ek += step << 1) { // Ek是某次DFT合并中E[k]在序列中的下标
				int Ok = Ek + step;    // Ok是该DFT合并中O[k]在序列中的下标,其上要乘旋转因子
				CD t = omegak * a[Ok]; // 蝶形操作：x1 * omega^k
				a[Ok] = a[Ek] - t;     // 蝶形操作：y1 = x0 - t
				a[Ek] += t;            // 蝶形操作：y0 = x0 + t
			}
		}
	}
	if(inverse)for(int i = 0; i < n; i++) a[i] /= n; 
}

// 用FFT实现的快速卷积(多项式乘法)
inline vector<double> operator * (const vector<double>& v1, const vector<double>& v2) {
	int s1 = v1.size(), s2 = v2.size(), S = 2;
	while(S < s1 + s2) S <<= 1;
	vector<CD> a(S,0), b(S,0); // 把FFT的输入长度补成2的幂，不小于v1和v2的长度之和
	for(int i = 0; i < s1; i++) a[i] = v1[i];
	FFT(a, false); //A = DFT(a)
	for(int i = 0; i < s2; i++) b[i] = v2[i];
	FFT(b, false); //B = DFT(b)
	for(int i = 0; i < S; i++) a[i] *= b[i];
	FFT(a, true); //IDFT(AB)
	vector<double> res(s1 + s2 - 1); //卷积的长度
	for(int i = 0; i < s1 + s2 - 1; i++) res[i] = a[i].real(); // 虚部均为0
	return res;
}

int main(){
	vector<double> v1,v2;
	int n1,n2;
	printf("how many number in your sequence v1 and v2? ");
	scanf("%d%d",&n1,&n2);
	printf("Input your v1 sequence.\n");
	for(int i = 0;i < n1;i++){
		double tmp;
		cin >> tmp;
		v1.push_back(tmp);
	}
	printf("Ok,and input your v2 sequence.\n");
	for(int i = 0;i < n2;i++){
		double tmp;
		cin >> tmp;
		v2.push_back(tmp);
	}
	printf("Calculating...\n");
	vector<double> res;
	res = v1*v2; //算卷积
	printf("convolution of v1 and v2:\n");
	for(int i = 0;i < res.size();i++){
		cout << res[i] << " ";
	}
	cout << endl;
	return 0;
}
