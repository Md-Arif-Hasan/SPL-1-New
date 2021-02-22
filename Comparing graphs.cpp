#include<bits/stdc++.h>
using namespace std;
#define maxLine 10000
vector<int>adj1[maxLine + 1];
vector<int>adj2[maxLine + 1];
int main()
{
    freopen("output123.txt", "r" , stdin);
    int edgeCnt1 = 0;
    cin>>edgeCnt1;
    for(int i=1;i<=edgeCnt1;i++){
    	int u,v;
    	cin>>u>>v;
    	adj1[u].push_back(v);
	}
	int edgeCnt2 = 0;
	cin>>edgeCnt2;
	for(int i = 1;i<=edgeCnt2;i++){
		int u,v;
		cin>>u>>v;
		adj2[u].push_back(v);
	}
	for(int i = 1;i<maxLine;i++){
		sort(adj1[i].begin(),adj1[i].end());
		sort(adj2[i].begin(),adj2[i].end());
	}
	int match = 0;
	for(int i =1 ;i<maxLine;i++){
		for(int j = 0;j<(int)adj1[i].size();j++){
			int pos = lower_bound(adj2[i].begin(),adj2[i].end(),adj1[i][j]) - adj2[i].begin();
			if(adj2[i][pos]==adj1[i][j])match++;
		}
	}
	int antiMatch = edgeCnt1+edgeCnt2 - match*2;
	
// 	cout <<" Total edge
	cout<<2*match<<"/"<<antiMatch<<"\n";
	int total  = (2*match + antiMatch);
	
	long long pct = (2*match*100)/total;
	cout<<"The percentage of matching : ";
	cout << pct <<"%"<<endl;
}
