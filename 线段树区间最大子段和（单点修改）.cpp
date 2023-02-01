#include<bits/stdc++.h>
using namespace std;
#define LF putchar('\n')
#define SP putchar(' ')
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define repp(i,a,b) for(register int i=(a);i>=(b);i--)
#define pair<int,int> pill
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
const ll MOD=1e9+7,N=5e5+10;
ll a[N],n,m;
struct Tree{
	ll sum,ls,rs,ans;//区间和，mid以左的最大子段和，mid以右的最大子段和，最大子段和 
	int left,right;
}tree[4*N];
void pushup(int root){//函数内重复书写部分，可增强可读性（维护子段和） 
	Tree L=tree[lc],R=tree[rc];
	tree[root].sum=L.sum+R.sum;
	tree[root].ls=max(L.ls,L.sum+R.ls);
	tree[root].rs=max(R.rs,R.sum+L.rs);
	tree[root].ans=max(L.rs+R.ls,max(L.ans,R.ans));
}
void build(int root,int l,int r){//建树的根节点，左当前树边界，当前树右边界 
	tree[root].left=l;
	tree[root].right=r;
	if(l==r){
		tree[root].sum=tree[root].ls=tree[root].rs=tree[root].ans=a[l];//l,r相等 ,直接赋值 
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	pushup(root);
}
Tree query(int root,int l,int r){//查询根节点,查询的左边界，查询的右边界 
	if(l<=tree[root].left and r>=tree[root].right)return tree[root];
	int mid=(tree[root].left+tree[root].right)>>1;
	if(l>mid)return query(rc,l,r);
	if(r<=mid)return query(lc,l,r);
	Tree L,R,res;
	L=query(lc,l,mid);
	R=query(rc,mid+1,r);
	res.sum=L.sum+R.sum;
	res.ls=max(L.ls,L.sum+R.ls);
	res.rs=max(R.rs,R.sum+L.rs);
	res.ans=max(L.rs+R.ls,max(L.ans,R.ans));
	return res;
}
void update(int root,int pos,ll v){//当前左右树的根节点，要修改的l与r，修改的值 
	if(tree[root].left==tree[root].right){
		tree[root].sum=tree[root].ls=tree[root].rs=tree[root].ans=v;//二分到了，修改 
		return;
	}
	int mid=(tree[root].left+tree[root].right)>>1;
	if(pos<=mid)update(lc,pos,v);
	if(pos>mid) update(rc,pos,v);
	pushup(root);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	rep(i,1,n)read(a[i]);
	build(1,1,n);
	read(m);
	while(m--){
		int op,x,y;
		read(op,x,y);
		if(op==0)update(1,x,y);
		else{
			write(query(1,x,y).ans);
			LF;
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
