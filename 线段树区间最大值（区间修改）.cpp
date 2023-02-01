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
const ll MOD=1e9+7,N=1e6+10;
ll a[N],n,m;
struct node{
	ll maxx,lazy;
	int left,right;
}tree[4*N];
void build(int root,int l,int r){//建树的根节点，左当前树边界，当前树右边界 
	tree[root].left=l;
	tree[root].right=r;
	if(l==r){
		tree[root].maxx=a[l];//l,r相等 ,直接赋值 
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].maxx=max(tree[lc].maxx,tree[rc].maxx);
}
void spread(int root){//将p子树的lazy下放 
	int la=tree[root].lazy;
	if(la){
		tree[lc].maxx+=la;
		tree[lc].lazy+=la;
		tree[rc].maxx+=la;
		tree[rc].lazy+=la;
		tree[root].lazy=0;
	}
}
ll query(int root,int l,int r){//查询根节点,查询的左边界，查询的右边界 
	if(l<=tree[root].left and r>=tree[root].right)return tree[root].maxx;
	spread(root);
	ll ans=-LINF,mid=(tree[root].left+tree[root].right)>>1;
	if(l<=mid)ans=max(ans,query(lc,l,r));
	if(r>mid)ans=max(ans,query(rc,l,r));
	return ans;
}
void update(int root,int l,int r,ll v){//当前左右树的根节点，要修改的l与r，修改的值 
	if(l<=tree[root].left and r>=tree[root].right){
		tree[root].maxx+=v;//二分到了，修改 
		tree[root].lazy+=v;//lazy标记 
		return;
	}
	spread(root);
	int mid=(tree[root].left+tree[root].right)>>1;
	if(l<=mid)update(lc,l,r,v);
	if(r>mid) update(rc,l,r,v);
	tree[root].maxx=max(tree[lc].maxx,tree[rc].maxx);//回溯更改
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,n)read(a[i]);
	build(1,1,n);
	while(m--){
		int op,l,r,v;
		read(op);
		if(op==1){
			read(l,r,v);
			update(1,l,r,v);
		}
		else{
			read(l,r);
			write(query(1,l,r));
			LF;
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
