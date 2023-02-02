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
const ll MOD=1e9+7,N=1e6+10;
ll n,cnt,a[N];
pill opt[N];
map<int,int>mp;
struct node{
	int num,left,right;
}tree[4*N];
void build(int root,int l,int r){
	tree[root].left=l;
	tree[root].right=r;
	if(l==r){
		tree[root].num=0;//权值线段树，存的是tree[l].left所出现的次数 
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].num=tree[lc].num+tree[rc].num;
}
ll query(int root,int l,int r){//查询区间[l,r]有多少个数字query(1,x+1,n) 
	if(l<=tree[root].left and tree[root].right<=r)return tree[root].num;
	int mid=(tree[root].left+tree[root].right)>>1,ans=0;
	if(l<=mid)ans+=query(lc,l,r);
	if(r>mid) ans+=query(rc,l,r);
	return ans;
}
ll query_min(int root,int l,int r,int k){//第k小的数 
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(tree[lc].num>=k)return query_min(lc,l,mid,k);
	else return query_min(rc,mid+1,r,k-tree[lc].num);
}
void update(int root,int l,int r,ll v,int k){//k为1就表示插入1个，为-1就表示删除1个 
	if(l==r){
		tree[root].num+=k;
		return;
	}
	int mid=(l+r)>>1;
	if(v<=mid)update(lc,l,mid,v,k);
	if(v>mid)update(rc,mid+1,r,v,k);
	tree[root].num=tree[lc].num+tree[rc].num;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	rep(i,1,n){
		read(opt[i].fir,opt[i].sec);//在线转离线（要离散化） 
		if(opt[i].fir==1){
			if(++mp[opt[i].sec]==1)a[++cnt]=opt[i].sec;
		}
	}
	sort(a+1,a+1+cnt);
	rep(i,1,cnt)mp[a[i]]=i;//离散化
	build(1,1,cnt);
	rep(i,1,n){
		int op=opt[i].fir,x=mp[opt[i].sec];
		if(op==1)update(1,1,cnt,x,1);//插入x 
		else if(op==2)update(1,1,cnt,x,-1);//删除一个x
		else if(op==3){
			write(query(1,0,x-1)+1);//比x小的数的个数 +1
			LF;
		}
		else if(op==4){
			write(a[query_min(1,1,cnt,opt[i].sec)]);//排名（比当前数小的数的个数+1）为opt[i].second的数 
			LF;
		}
	} 
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
//权值线段树+离散化
