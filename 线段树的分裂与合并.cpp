#include<bits/stdc++.h>
using namespace std;
#define LF putchar('\n')
#define SP putchar(' ')
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define repp(i,a,b) for(register int i=(a);i>=(b);i--)
#define pill pair<int,int>
#define mem(t, v) memset((t),v,sizeof(t))
#define fir first
#define sec second
#define mk make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define lc root<<1
#define rc root<<1|1
typedef long long ll;
typedef unsigned long long ull;
template<typename T>
void read(T &x) {x=0;char ch=getchar();ll f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}x*=f;}
template<typename T, typename... Args>
void read(T &first, Args& ... args) {read(first);read(args...);}
template<typename T>
void write(T arg) {T x=arg;if(x<0) {putchar('-');x=-x;}if(x>9) {write(x/10);}putchar(x%10+'0');}
template<typename T, typename ... Ts>
void write(T arg, Ts ... args) {write(arg);if(sizeof...(args)!=0) {putchar(' ');write(args ...);}}
const ll MOD=1e9+7,N=2e5+10;
ll n,tot;//tot用于计数开了多少点 
struct nood{
	int lson,rson;
	ll val;
}tree[N*40];
void pushup(int root){//回溯时的求和 
	tree[root].val=tree[tree[root].lson].val+tree[tree[root].rson].val;
}
void update(int &root,int l,int r,int q,int x){//&root是因为有修改,x代表更改多少 
	if(!root)root=++tot;//新开一个点 
	if(l==r){
		tree[root].val+=x;
		return;
	}
	int mid=(l+r)>>1;
	if(q<=mid)update(tree[root].lson,l,mid,q,x);
	else update(tree[root].rson,mid+1,r,q,x);
	pushup(root);
}
void Merge(int &x,int y){//线段树的合并 
	if(!x||!y)x|=y;//将y赋值给x 
	else{
		tree[x].val+=tree[y].val;
		Merge(tree[x].lson,tree[y].lson);
		Merge(tree[x].rson,tree[y].rson);
	} 
}
int split(int &k,int l,int r,int x,int y){//线段树的分裂 
	int kk=++tot;//动态建一个分裂后的新树
	if(x<=l and y>=r){
		tree[kk]=tree[k];
		k=0;//删除 
	}
	else{
		int mid=(l+r)>>1;
		if(x<=mid)tree[kk].lson=split(tree[k].lson,l,mid,x,y);
		if(y>mid)tree[kk].rson=split(tree[k].rson,mid+1,r,x,y);
		pushup(kk);
		pushup(k);
	}
	return kk;//返回拆分后新树的根节点 
}
ll query(int root,int l,int r,int x,int y){
	if(x<=l and y>=r)return tree[root].val;
	int mid=(l+r)>>1;
	ll sum=0;
	if(x<=mid)sum+=query(tree[root].lson,l,mid,x,y);
	if(y>mid)sum+=query(tree[root].rson,mid+1,r,x,y);
	return sum;
}
int query_kth(int root,int l,int r,int kth){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(kth<=tree[tree[root].lson].val)return query_kth(tree[root].lson,l,mid,kth);
	else return query_kth(tree[root].rson,mid+1,r,kth-tree[tree[root].lson].val);
}
int roott[N],rcnt=1; 
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int n,m;
	read(n,m);
	rep(i,1,n){
		int x;
		read(x);
		update(roott[1],1,n,i,x);
	}
	rep(i,1,m){
		int op,p,x,y;
		read(op);
		if(op==0){
			read(p,x,y);
			roott[++rcnt]=split(roott[p],1,n,x,y);
		}
		else if(op==1){
			read(p,x);
			Merge(roott[p],roott[x]);
		}
		else if(op==2){
			read(p,x,y);
			update(roott[p],1,n,y,x);
		}
		else if(op==3){
			read(p,x,y);
			write(query(roott[p],1,n,x,y));
			LF;
		}
		else if(op==4){
			read(p,x);
			if(x>tree[roott[p]].val){
				write(-1);
				LF;
			}
			else{
				write(query_kth(roott[p],1,n,x));
				LF;
			}
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
/*
可重集的操作
0 p x y：将可重集 p 中大于等于 x 且小于等于 y 的值放入一个新的可重集中（新可重集编号为从 2 开始的正整数，是上一次产生的新可重集的编号+1）。
1 p t：将可重集 t 中的数放入可重集 p，且清空可重集 t（数据保证在此后的操作中不会出现可重集 t）。
2 p x q：在 p 这个可重集中加入 x 个数字 q。
3 p x y：查询可重集 p 中大于等于 x 且小于等于 y 的值的个数。 
4 p k：查询在 p 这个可重集中第 k 小的数，不存在时输出 -1。
*/
