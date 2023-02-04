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
struct Tree{ 
	int l,r,cover;//coverΪ���Ǵ�������[x,x]����x~x+1������� 
	ll len;//�������ߵĳ��ȣ��»��־��θߣ� 
}tree[N<<2];
int n,Y[N];//Y�����¼ÿ���ߵ�y���� 
struct scanline{
	ll x,uy,dy;//�ߵ�x��������y�㡢��y�������
	 int intout;//1Ϊ��ߣ�-1Ϊ�ձ�
	 bool operator<(const scanline &t)const{
	 	return x<t.x;//��x��С�������� 
	 }
}line[N];
void build(int root,int l,int r){//��һ���������� 
	tree[root]={l,r,0,0};
	if(l==r)return;
	int mid=(l+r)>>1;
	build(lc,l,mid);
	build(rc,mid+1,r);
}
void pushup(int root){
	if(tree[root].cover)tree[root].len=Y[tree[root].r+1]-Y[tree[root].l];
	else if(tree[root].l==tree[root].r)tree[root].len=0;//��֤����ɾ����
	else tree[root].len=tree[lc].len+tree[rc].len; 
}
void update(int root,int yl,int yr,int k){
	if(yl<=tree[root].l and tree[root].r<=yr){
		tree[root].cover+=k;
		pushup(root);
		return;
	}
	int mid=(tree[root].l+tree[root].r)>>1;
	if(yl<=mid)update(lc,yl,yr,k);
	if(yr>mid)update(rc,yl,yr,k);
	pushup(root);
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	rep(i,1,n){
		ll x,y,xx,yy;
		read(x,y,xx,yy);//��ʾ���½Ǻ����Ͻǵĵ������
		Y[2*i-1]=y;
		Y[2*i]=yy;
		line[2*i-1]={x,yy,y,1};
		line[2*i]={xx,yy,y,-1};
	}
	n<<=1;
	sort(Y+1,Y+1+n);
	sort(line+1,line+1+n);
	int tot=unique(Y+1,Y+1+n)-Y-1;//ȥ��
	build(1,1,tot-1);
	ll ans=0;
	rep(i,1,n){
		ans+=tree[1].len*(line[i].x-line[i-1].x);
		int yl=lower_bound(Y+1,Y+tot+1,line[i].dy)-Y,yr=lower_bound(Y+1,Y+tot+1,line[i].uy)-Y;
		update(1,yl,yr-1,line[i].intout);
	}
	write(ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
//�ߵĶ���Ϊÿ�����εĸ�
//ɨ�����㷨�����P8648 
