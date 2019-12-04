#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
using namespace std;
using ll=long long;

const int N=5;
const int M=3*3*3*3*3;
int p[N]={1,3};

const int INF=0x01010101;
const int WIN_POINT = 9;

int f[M][2];

int dfs(int u,int v) {
	int &ret=f[u][v];
	if (ret!=INF) return ret;
	{
		int cnt=0;
		for (int i=0;i<N;i++) cnt+=u/p[i]%3!=0;
		if (cnt<2) return ret=0;
	}
	if (v) { //minimize
		ret = INF;
		for (int i=0;i<N;i++) {
			if (u/p[i]%3!=0) continue;
			ret = min(ret, dfs(u+2*p[i],!v)+1);
		}
		int tret = -INF;
		for (int i=0;i<N;i++) {
			if (u/p[i]%3!=0) continue;
			tret = max(tret, dfs(u+1*p[i],v)-1);
		}
		ret = min(ret, tret);
	} else { //maximize
		ret = -INF;
		for (int i=0;i<N;i++) {
			if (u/p[i]%3!=0) continue;
			ret = max(ret, dfs(u+1*p[i],!v)-1);
		}
		int tret = INF;
		for (int i=0;i<N;i++) {
			if (u/p[i]%3!=0) continue;
			tret = min(tret, dfs(u+2*p[i],v)+1);
		}
		ret = max(ret, tret);
	}
	return ret;
}

int win(int u) {
	int cnt1=0, cnt2=0;
	for (int i=0;i<N;i++) {
		int t=u%3;
		u/=3;
		if (t==0) return 0;          //gaming;
		if (t==1) {
			if (++cnt1>=5) return 1; //1win
			cnt2=0;
		}
		if (t==2) {
			if (++cnt2>=5) return 2; //2win
			cnt1=0;
		}
	}
	return 3; //draw
}


int main() {
	freopen("tab.h","w",stdout);
	for (int i=2;i<N;i++) p[i]=p[i-1]*p[1];
	memset(f,INF,sizeof f);
	for (int u=0;u<M;u++) {
		int w=win(u);
		if (w==1) f[u][0]=WIN_POINT, f[u][1]=WIN_POINT-1;  //1win
		if (w==2) f[u][0]=-WIN_POINT+1,f[u][1]=-WIN_POINT;; //2win
		if (w==3) f[u][0]=f[u][1]=0;          //draw
	}
//	set<int> S;
	printf("static const int N=%d;\n",N);
	printf("static const long long TABLE[%d][2] = {\n",M);
	for (int u=0;u<M;u++) for (int v=0;v<2;v++) {
		int t=max(-WIN_POINT,min(WIN_POINT,dfs(u,v)));
		if (t==0) printf(" 0      , ");
		else printf("%c1ll<<%2d, ",t>0?'+':'-',abs(4*t));
//		printf("%2d, ",t);
		if(u%10==9&&v==1) puts("");
//		printf("f[");
//		for (int i=N-1;i>=0;i--) printf("%d",u/p[i]%3);
//		printf("][%d]=%d\n",v,dfs(u,v));
//		S.insert(dfs(u,v));
	}
	puts("\n};");
//	for (auto t:S) printf("%d\n",t);
	
}

