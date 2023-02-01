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
ll a[N],n,m;
struct node{
	ll maxx,minn;
	int left,right;
}tree[4*N];
void build(int root,int l,int r){//�����ĸ��ڵ㣬��ǰ���߽磬��ǰ���ұ߽� 
	tree[root].left=l;
	tree[root].right=r;
	if(l==r){
		tree[root].maxx=tree[root].minn=a[l];//l,r��� ,ֱ�Ӹ�ֵ 
		return;
	}
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
	tree[root].maxx=max(tree[lc].maxx,tree[rc].maxx);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);
}
pair<ll,ll> query(int root,int l,int r){//��ѯ���ڵ�,��ѯ����߽磬��ѯ���ұ߽� 
	if(l<=tree[root].left and r>=tree[root].right)return mk(tree[root].maxx,tree[root].minn);
	int ans=0,mid=(tree[root].left+tree[root].right)>>1;
	ll Max=-INF,Min=INF;
	if(l<=mid){
		pair<ll,ll> pi=query(lc,l,r);
		Max=max(Max,pi.fir);
		Min=min(Min,pi.sec);
	}
	if(r>mid){
		pair<ll,ll> pi=query(rc,l,r);
		Max=max(Max,pi.fir);
		Min=min(Min,pi.sec);
	}
	return mk(Max,Min);
}
void update(int root,int pos,int v){//��ǰ�������ĸ��ڵ㣬Ҫ�޸ĵ�λ�ã��޸ĵ�ֵ(����) 
	if(tree[root].left==tree[root].right){
		tree[root].minn+=v; 
		tree[root].maxx+=v;//���ֵ��ˣ��޸� 
		return;
	}
	int mid=(tree[root].left+tree[root].right)>>1;
	if(pos<=mid)update(lc,pos,v);
	else update(rc,pos,v);
	tree[root].maxx=max(tree[lc].maxx,tree[rc].maxx);
	tree[root].minn=min(tree[lc].minn,tree[rc].minn);//���ݸ���
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,n)read(a[i]);
	build(1,1,n);
	while(m--){
		int op,x,y;
		read(op,x,y);
		if(op==1)update(1,x,y);
		else{
			pair<ll,ll>pi=query(1,x,y);
			write(pi.fir-pi.sec);
			LF;
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
} 
