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
ll t,sum1[N],sum2[N],n,q,op,l,r,k;
ll lowbit(ll x){return x&(-x);}//二进制中最低位的 1在什么位置 
void add(ll l,ll r,ll k){//从l到r都加k 
	for(ll i=l;i<=n;i+=lowbit(i))sum1[i]+=k,sum2[i]+=k*l;
	for(ll i=r+1;i<=n;i+=lowbit(i))sum1[i]-=k,sum2[i]-=k*(r+1);
}
ll getsum(int x){//从1到x的前缀和 
	ll sum=0;
	for(ll i=x;i;i-=lowbit(i))sum+=(x+1)*sum1[i]-sum2[i];
	return sum;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,q);
	rep(i,1,n){
		read(t);
		add(i,i,t);
	}
	while(q--){
		read(op);
		if(op==1){
			read(l,r,k);
			add(l,r,k);
		}
		else{
			read(l,r);
			write(getsum(r)-getsum(l-1));
			LF;
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

