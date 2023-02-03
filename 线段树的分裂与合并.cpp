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
ll n,tot;//tot���ڼ������˶��ٵ� 
struct nood{
	int lson,rson;
	ll val;
}tree[N*40];
void pushup(int root){//����ʱ����� 
	tree[root].val=tree[tree[root].lson].val+tree[tree[root].rson].val;
}
void update(int &root,int l,int r,int q,int x){//&root����Ϊ���޸�,x������Ķ��� 
	if(!root)root=++tot;//�¿�һ���� 
	if(l==r){
		tree[root].val+=x;
		return;
	}
	int mid=(l+r)>>1;
	if(q<=mid)update(tree[root].lson,l,mid,q,x);
	else update(tree[root].rson,mid+1,r,q,x);
	pushup(root);
}
void Merge(int &x,int y){//�߶����ĺϲ� 
	if(!x||!y)x|=y;//��y��ֵ��x 
	else{
		tree[x].val+=tree[y].val;
		Merge(tree[x].lson,tree[y].lson);
		Merge(tree[x].rson,tree[y].rson);
	} 
}
int split(int &k,int l,int r,int x,int y){//�߶����ķ��� 
	int kk=++tot;//��̬��һ�����Ѻ������
	if(x<=l and y>=r){
		tree[kk]=tree[k];
		k=0;//ɾ�� 
	}
	else{
		int mid=(l+r)>>1;
		if(x<=mid)tree[kk].lson=split(tree[k].lson,l,mid,x,y);
		if(y>mid)tree[kk].rson=split(tree[k].rson,mid+1,r,x,y);
		pushup(kk);
		pushup(k);
	}
	return kk;//���ز�ֺ������ĸ��ڵ� 
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
���ؼ��Ĳ���
0 p x y�������ؼ� p �д��ڵ��� x ��С�ڵ��� y ��ֵ����һ���µĿ��ؼ��У��¿��ؼ����Ϊ�� 2 ��ʼ��������������һ�β������¿��ؼ��ı��+1����
1 p t�������ؼ� t �е���������ؼ� p������տ��ؼ� t�����ݱ�֤�ڴ˺�Ĳ����в�����ֿ��ؼ� t����
2 p x q���� p ������ؼ��м��� x ������ q��
3 p x y����ѯ���ؼ� p �д��ڵ��� x ��С�ڵ��� y ��ֵ�ĸ����� 
4 p k����ѯ�� p ������ؼ��е� k С������������ʱ��� -1��
*/
