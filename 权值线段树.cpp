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
ll n,m,t;
map<int,int>a;
struct node{
	int num,left,right;
}tree[4*N];
void build(int root,int l,int r){
	tree[root].left=l;
	tree[root].right=r;
	if(l==r){
		tree[root].num=a[l];//权值线段树，存的是tree[l].left所出现的次数 
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].num=tree[lc].num+tree[rc].num;
}
ll query_min(int root,int l,int r,int k){//k是从小到大第k个数 
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(tree[lc].num>=k)return query_min(lc,l,mid,k);
	else return query_min(rc,mid+1,r,k-tree[lc].num);
}
ll query_max(int root,int l,int r,int k){//k是从大到小第k个数 
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(tree[rc].num>=k)return query_max(rc,mid+1,r,k);
	else return query_max(lc,l,mid,k-tree[rc].num);
}
ll query_num(int root,int l,int r,int k){//k的出现次数 
	if(l==r)return tree[root].num;
	int mid=(l+r)>>1;
	if(k<=mid)return query_num(lc,l,mid,k);
	else return query_num(rc,mid+1,r,k);
}
void update(int root,int l,int r,ll v){
	if(l==r){
		tree[root].num++;
		return;
	}
	int mid=(l+r)>>1;
	if(v<=mid)update(lc,l,mid,v);
	if(v>mid)update(rc,mid+1,r,v);
	tree[root].num=tree[lc].num+tree[rc].num;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,n){
		read(t);
		a[t]++;
	}
	build(1,1,N);
	while(m--){
		int op,x;
		read(op,x);
		if(op==1){
			write(query_min(1,1,N,x));
			LF;
		}
		else if(op==2){
			write(query_max(1,1,N,x));
			LF;
		}
		else if(op==3){
			write(query_num(1,1,N,x));
			LF;
		}
		else update(1,1,N,x);
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
//权值线段树 
