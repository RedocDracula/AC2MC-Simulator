#include <bits/stdc++.h>
#define inchar			getchar
#define outchar(x)		putchar(x)
#define ll long long int
#define SP outchar(' ')
#define LN outchar('\n')
using namespace std;

template<typename T> void inpos(T &x){x=0;register T c=inchar();while(((c<48)||(c>57))&&(c!='-'))c=inchar();bool neg=0; if(c=='-')neg=1;for(;c<48||c>57;c=inchar());for(;c>47&&c<58;c=inchar())x=(x<<3)+(x<<1)+(c&15);if(neg)x=-x;}
template<typename T> void outpos(T n){if(n<0){outchar('-');n*=-1;}char snum[65];int i=0;do{snum[i++]=n%10+'0';n/=10;}while(n);i=i-1;while(i>=0)outchar(snum[i--]);}
inline void instr(char *str){register char c=0;register int i=0;while(c<33)c=inchar();while(c!='\n'&&c!=' '&&c!=EOF){str[i]=c;c=inchar();++i;}str[i]='\0';}


int main () {
	// bitset <32 >
	int k = 2;	
}