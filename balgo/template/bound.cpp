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
*    upper_bound 和 lower_bound 是STL内置的常用演算法,思想是二分法.
*    (1)upper_bound 返回容器中 第一个大于 key 的元素的位置.
*    (2)lower_bound 返回容器中 第一个大于或等于 key 的元素的位置.
*    (3)若容器中无 key 这个元素,那么由定义知 lower_bound 和 upper_bound 返回的位置相同.
*    (4)若key比容器中所有元素都大,则返回位置 "size"(刚好越界的位置).
*/

const int maxn = 1000;
//这个算法中，first是最终要返回的位置
int lowerbound(int *array, int size, int key){
    int first = 0, middle;
    int half, len = size;

    while(len > 0) {
        half = len >> 1;
        middle = first + half;
        if(array[middle] < key){     
            first = middle + 1;          
            len = len-half-1;       //在右边子序列中查找
        }
        else len = half;       //在左边子序列（包含middle）中查找
    }
    return first;
}
int upperbound(int *array, int size, int key){
    int first = 0, middle;
    int half, len = size;

    while(len > 0){
        half = len >> 1;
        middle = first + half;
        if(array[middle] > key) len = half; //在包含last的左半边序列中查找。
        else{
            first = middle + 1;    //在右半边序列中查找。
            len = len - half - 1;
        }
    }
    return first;
}

int main(){
	int n,m;
	int array[maxn];
	while(1){
		printf("How many number? ");
		scanf("%d",&n);
		printf("Input your array:\n");
		for(int i = 0;i < n;i++)cin >> array[i];
		printf("How many times you want to query? ");
		cin >> m;
		printf("Execute your query with format:lowerbound(key) or upperbound(key).\n");
		char str[200];
		int key,result1,result2;//result1是STL的结果,result2则是手写的结果
		while(m--){
			scanf("%s",str);
			if(str[0]=='l'){
				sscanf(str,"lowerbound(%d)",&key);
				result1 = lower_bound(array,array+n,key)-array;
				result2 = lowerbound(array,n,key);
			}else{
				sscanf(str,"upperbound(%d)",&key);
				result1 = upper_bound(array,array+n,key)-array;
				result2 = upperbound(array,n,key);
			}
			printf("The reuslt position is-- STL:%d  ours:%d\n",result1,result2);
		}
		cout << endl;
	}
	return 0;
}
