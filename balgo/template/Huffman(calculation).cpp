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
*    Huffman编码:将编码长度将至最小且不发生冲突.
*    子树樹葉深度總和，就是「碼表長度」
*    以频率为权重,先将各字符按照频率排序,然后迭代:
*    (1)优先聚合权重最小的两结点,可以得到最小的编码长度;
*    (2)在(1)的条件下优先聚合码表长度最小的两结点,可以进一步达成码表长度最小
*    下面的程式可计算出最优值,但不能给出Huffman树结构.
*/

int freq[8] = {4, 2, 1, 2, 3, 1, 2, 1};	// 各种字符的频率

//(1)
void optimal1(){
	// 设置为小根堆
	priority_queue<int, vector<int>, greater<int> > pq;
	// 所有樹葉丟進Priority Queue
	for (int i=0; i<8; ++i) pq.push(freq[i]);
	// 聚合N-1次就得到樹根了
	int c = 0;	// Optimal Code Tree的權重
	for (int i=0; i<8-1; ++i){
		// 聚合兩個權重最小的節點
		int a = pq.top(); pq.pop();cout << a << " ";
		int b = pq.top(); pq.pop();cout << b << endl;
		pq.push(a + b);	// 新節點丟進Priority Queue
		c += (a + b);// 計算Optimal Code Tree的權重
	}
	cout << "最小的编码长度为" << c << endl;
}

//(2)
struct Node{
	int freq;	// 各种字符频率
	int cnt;	// 结点涵盖的树叶数量
	int length;	// 结点涵盖的码长总和
};
//设置为:优先聚合权重最小且码长总和最小的两结点
bool operator<(const Node& n1, const Node& n2){
	if (n1.freq != n2.freq)
		return n1.freq > n2.freq; 
	return n1.length > n2.length;
}

void optimal2(){
	priority_queue<Node> pq;
	for (int i=0; i<8; ++i)
		pq.push((Node){freq[i], 1, 0});
	int c = 0;
	for (int i=0; i<8-1; ++i){
		Node a = pq.top(); pq.pop();
		Node b = pq.top(); pq.pop();
		pq.push((Node){
			a.freq + b.freq,
			a.cnt + b.cnt,
			a.length + b.length + a.cnt + b.cnt,
		});
		c += a.freq + b.freq;
	}

	cout << "最小的编码长度为 " << c << endl;
	cout << "此時，最小的碼表長度是" <<  pq.top().length;

}

int main(){
	optimal2();
	return 0;
}


