/**
*    所谓的树形DP,就是在树上进行的DP.
*    树上的DP本质和其他结构上的没差,都是多阶段决策和状态转移.
*    树形DP的基本思路:
*        (1)判断是不是树,不是的话能不能转化成树(转成有根树方便处理)
*        (2)确定状态,建树(注意建树方法)
*        (3)写状态转移方程:两种转移方向,根到叶子或叶子到根(就是递归/递推或说自顶向下/自底向上)
*    一般来说自根到叶子实现起来比较方便一些,但是递推快些.
*    但是树的性质很好,层数严格而且没有圈,因而状态不会在不同分支上重复出现,自顶向下的话就用不着记忆化.
*    若一开始不是树,有一种可能的转化是求SCC然后缩点成为二叉树.
*    下面介绍几种典型的模型.
*/

/**
*    基础方法:无根树->有根树(实际上是DFS生成树)
*    dfs建立即可,存储结构是邻接表.
*/
p[maxn];//表示新建立的有根树
void dfs(int u,int fa){  //建立以u为根的树,fa是u的老爹
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(v = fa)continue;//避免搜到老爹
		dfs(v,p[v]=u);
	}
}
void transfer(int root){ //参数是根结点编号
	p[root] = -1;
	dfs(root,-1);
}
/**
*    树的最大独立集:对n结点的无根树,选择尽量多的点使其中任意两点不相邻.
*    (有比较好的贪心方法,在实践中更加常用,但是这里我们说DP)
*    给出n-1条无向边,输出最大独立集大小
*    思路:先无根树转有根树,方便处理.每个结点有两种状态(选or不选).和已选结点相邻接的点不能选(约束).
*    设gc(i),c(i)分别为i的孙点集和子点集.
*    状态及指标d(i): 以i为根的树的最大独立集大小
*    转移方程: d(i)=max{sum(d(j)),1+sum(d(k))},j∈c,k∈gc
*    边界: d(leaf) = 1;
*    由i找gc(i)和c(i)不好弄,但是树的结构很好,一个结点的爹和爷唯一,所以实现的时候我们采用自底向上.
*/
int depth[MAXN]; //结点深度 
int p[MAXN];  
int dp[MAXN]; //dp数组  
int sumC[MAXN]; //子DP的和  
int sumS[MAXN]; //孙DP的和  
int maxdep; //最大深度  
int n;  
void dfs(int u,int fa){     
    for(int i=0;i<G[u].size();++i){
        int v=G[u][i];  
		if(v == fa) continue;
		depth[v] = depth[u]+1;
		maxdep = max(maxdep,depth[v]); 
        dfs(v,p[v]=u);   
    }  
}  
//主控过程,任选一个结点为树根,进行递推
int dp(int root){
    p[root]=-1;depth[root]=0;maxdep = 0;
    dfs(root,-1);//转成有根树
	//倒着一层层推
	for(int i = maxdep;i >=0;i--){
		for(int j = 0;j < n;j++){
			if(depth[j] == i){
				dp[j] = max(sumS[j]+1,sumC[j]);
				if(i>=1)sumC[p[j]]+=dp[j];
				if(i>=2)sumS[p[p[j]]]+=dp[j];
			}
		}
	}
    return dp[root];  
}  
/**
*    树的重心:对于无根树,设重心为根,转为有根树后其最大子树的结点数最少.
*    (删去重心后,生成的多棵树尽可能平衡,此时树的高度最小)
*    重心的意义:在对树进行分治的时候可以避免N^2的极端复杂度(从退化链的一端出发),保证NlogN的复杂度.
*/
int d[maxn]; // d[i]表示以i为根的子树的结点个数
int core = 0; //重心节点编号
int minBalance = INF; //删除重心后得到的最大子树的结点个数
void dfs(int u, int parent){
    d[u] = 1;
    int maxSubTree = 0; 
    for (int i = 0; i < tree[u].size(); i++){
        int v = tree[u][i];
        if(v == parent)continue;
        dfs(v, u);
        d[u] += d[v];
        maxSubTree = max(maxSubTree, d[v]);//求得u的最大子树的结点个数(有根树中)
    }
    maxSubTree = max(maxSubTree, N - d[u]); //与上方子树比较,求出最大子树结点个数(无根树中)
    if (maxSubTree < minBalance){
        minBalance = maxSubTree;
        core = u;
    }
}
/**
*    树的直径(树上最远点对/树的最长链)
*    因为树上两点之间有且只有一条链,因而有下列方法:
*    法一:随便找一个点u,用bfs求得u的最远点v,再用bfs求得v的最远点w,则(v,w)就是最远点对.
*        (有权图用最短路算法替换BFS即可)   
*    法二:Dp的方法.
*        状态及指标:d(i)=以i为根的子树中,根i到下方叶子的最远距离(i的高度).
*        转移方程: d(i) = max{d(j)}+1,j是i的子结点们.
*        边界: d(leaf) = 0;
*        解:对于结点i,将d(j)都求出来后,设d(j)中的值前两大的结点为u,v则d(u)+d(v)+2就是最长链长度.
*    综合两个方法,我们可以解决问题:对一颗n结点无根树,求出每个结点的最远点对.O(n)
*/
int diameter = 0;
int dfs(int u,int fa){
	int h1 = 0,h2 = 0;//最高与次高的高度
	for(int i = 0;i < G[u].size();i++){
		int v = G[u][i];
		if(v == fa)continue;
		int h = dfs(v,u)+1;
		if(h > h1){h2 = h1;h1 = h;}
		else if(h > h2)h2 = h;
	}
	diameter = max(diameter,h1+h2);
	return h1;
}

/**
*    树的独立集个数:所有合法的独立集的总数,但是要保证至少有一个点
*    独立集的限制依然要保证,然后在递推过程中用乘法原理计数.
*    每个节点维护两个值,分别表示选和不选该结点时对应子树的独立集个数.
*    u的beChoosedCount = ∏( u子结点的beAbandonCount );
*    u的beAbandonCount = ∏( u子节点beChoosedCount + u子结点的beAbandonCount)
*    下述实现假设我们已经拿到了树,采用自顶向下的方式.
*/
void dfs(int u,int pre){
	dp[u][1] = dp[u][0] = 1;
	for(int i = 0;i < tree[u].size();i++){
		int v = tree[u][i];
		if(v == pre)continue;
		dfs(v,u);
		dp[u][0] *= (dp[v][0] + dp[v][1]);
		dp[u][1] *= dp[v][0]);
	}
}

