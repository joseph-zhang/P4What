
/**
*    LIS(最长上升子序列)和LCS(最长公共子序列)经常被用来作为DP的例子展示.
*    LIS是基础DP的好例子,也有许多变形问题,主要是掌握其转移方程的形式.
*    子序列:序列当中从左到右挑取一些字元所构成的新序列.(注意和子串区分)
*    这里主要给出DP的解法,同时给出一些其他的解.
*	 程式简要编写,主要为了体现出思想.
*/

/**
*    找出LIS的长度:DP O(n^2)
*    length(n) =  max  { length(i) + 1 : if s[i] < s[n] }  0≤i≤n-1
*    length(n)是以位置n为结尾的LIS长度.
*/
int s[5];		// sequence
int length[5];	// 第 x 格的值為 s[0...x] 的 LIS 長度

void LIS(){
	// 初始化。每一個數字本身就是長度為一的 LIS。
	for (int i=0; i<5; i++) length[i] = 1;

	for (int i=0; i<5; i++)
		// 找出 s[i] 能接在哪些數字後面，
		// 若是可以接，長度就增加。
		for (int j=0; j<i; j++)
			if (s[j] < s[i])
				length[i] = max(length[i], length[j] + 1);

	// length[] 之中最大的值即為 LIS 的長度。
	int n = 0;
	for (int i=0; i<5; i++)
		n = max(n, length[i]);
	cout << "LIS的長度是" << n;
}
/**
*    找出LIS的长度:Robinson-Schensted-Knuth Algorithm,思想是贪心.O(nlogn)
*	 利用贪心的思想,充分发掘上升的潜力.
*    注意执行完后只能得到LIS的长度,v中的序列不是LIS
*/
int LIS(vector<int>& s){
	// 不得不判斷的特例
	if (s.size() == 0) return 0;

	// 先放入一個數字，免得稍後 v.back() 出錯。
	vector<int> v;
	v.push_back(s[0]);

	for (int i = 1; i < s.size(); ++i){
		int n = s[i];
		if (n > v.back())
			v.push_back(n);
		else
			*lower_bound(v.begin(), v.end(), n) = n;
	}
	return v.size();
}
/**
*    找出一个LIS:只要建立一个pre数组记录是有那个位置接续的.
*    方法仍然是DP,这次我们采用另一种转移方程.
*/
int s[5];
int length[5];
int prev[5]; // prev[x] 記錄 s[x] 是接在哪個數字後面
void LIS(){
	for (int i=0; i<5; i++) length[i] = 1;
	memset(pre,-1,sizeof(pre));
	
	for (int i=0; i<5; i++){
		for (int j=i+1; j<5; j++)
			if (s[i] < s[j])
				if (length[i] + 1 > length[j]){
					length[j] = length[i] + 1;
					// s[j] 接在 s[i] 後面
					prev[j] = i;
				}
	}
	int n = 0, pos = 0;
	for (int i=0; i<5; i++){
		if (length[i] > n){
			n = length[i];
			pos = i;
		}
	}
	trace(pos);	// 印出一個LIS
}
void trace(int i){
	if (prev[i] != -1) trace(prev[i]);
	cout << seq[i] << ' ';
}

/**
*    找出LIS的长度:DP O(NL)
*    这个方法是把LIS的長度設計於狀態當中,作為狀態的其中一個維度,狀態本身儲存LIS的結尾數字。
*    总体思想是运用Robinson-Schensted-Knuth Algorithm的概念.
*    f(n, l) =  min( f(n-1, l), s[n] ) :if f(n-1, l-1) < s[n] 
*    f(n, l): 第0項到第n項，長度為l的上升子序列,其中最小的結尾數值.
*    下述实现中使用了滚动数组以提高效率,避免了二维阵列.
*/
const int N = 10;
int s[N+1];
int array[N+1];	// 滚动数组用

int LIS(){
	for (int i=1; i<=N; ++i) array[i] = INF;
	array[0] = -INF;

	int n = 0;	// 目前LIS的長度
	for (int i=1; i<=N; ++i){
		if (array[n] < s[i]) n++;	// LIS增長了
		for (int j=n; j>0; --j)	// 算至目前的LIS長度即可
			if (array[j-1] < s[i])
				array[j] = min(array[j], s[i]);
	}
	return n;
}

