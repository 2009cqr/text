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
const ll MOD=1e9+7,N=1e5+10;
ll n,tot,maxx=1e7;//tot用于计数开了多少点 
struct nood{
	int lson,rson;
	ll num;
}tree[N<<2];
void update(int &root,int l,int r,int val,int k){//&root是因为有修改,k代表删除或增加 
	if(!root)root=++tot;//新开一个点 
	if(l==r){
		tree[root].num+=k;
		if(tree[root].num<0)tree[root].num=0;
		return;
	}
	int mid=(l+r)>>1;
	if(val<=mid)update(tree[root].lson,l,mid,val,k);
	else update(tree[root].rson,mid+1,r,val,k);
	tree[root].num=tree[tree[root].lson].num+tree[tree[root].rson].num;
}
ll query(int root,int l,int r,int x,int y){ 
	if(!root)return 0;
	if(x<=l and r<=y)return tree[root].num;
	ll ans=0,mid=(l+r)>>1;
	if(x<=mid)ans+=query(tree[root].lson,l,mid,x,y);
	if(y>mid)ans+=query(tree[root].rson,mid+1,r,x,y);
	return ans;
}
ll query_kth(int root,int l,int r,int k){//排名为k的数(排名定义为比当前数小的数的个数+1 ) 
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(tree[tree[root].lson].num>=k)return query_kth(tree[root].lson,l,mid,k);
	else return query_kth(tree[root].rson,mid+1,r,k-tree[tree[root].lson].num);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int ans=0,root=0,last=0;
	read(n);
	rep(i,1,n){
		int op,x;
		read(op,x);
		x=x^last;//强制在线 
		if(op==1)update(root,1,maxx*2,x+maxx,1);
		else if(op==2)update(root,1,maxx*2,x+maxx,-1);
		else if(op==3)last=query(root,1,maxx*2,1,x+maxx-1)+1;
		else if(op==4)last=query_kth(root,1,maxx*2,x)-maxx;
		if(op==3 or op==4)ans=ans^last;
	}
	write(ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

