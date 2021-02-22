#include<bits/stdc++.h>
using namespace std;
#define maxLine 10000

vector<int>adjacencyList[maxLine+1];

void printList(int currLineNumber){
	freopen("output123.txt", "a" , stdout);
	int edgeCnt = 0;
	for(int i = 0; i < currLineNumber; i++){
		edgeCnt+=(int)adjacencyList[i].size();
	}
	cout<<edgeCnt<<"\n";
    for(int i=0;i<currLineNumber;i++){
        for(int j=0;j<adjacencyList[i].size();j++){
            cout<<i+1<<" "<<adjacencyList[i][j]+1<<"\n";
        }

    }
}
vector<string>Data;
void initializer(){
	int Size = Data.size();
	for(int i = 0;i < Size ;i++){
		string subString1 = Data[i].substr(0,2);
		string subString5 = Data[i].substr(0,1);
		if(subString1=="if"){
			adjacencyList[i].push_back(i+1);
			stack<int>st;
			for(int j = i+1;j<Size;j++){
				string  subString2 = Data[j].substr(0,2);
				string  subString3 = Data[j].substr(0,4);
				string  subString4 = Data[j].substr(0,1);
				if(subString2 == "if"){
					st.push(j);
				}
				else if(subString3 == "else"){
					st.push(j);
				}
				else if(subString4 == "}"){
					if(st.empty()){
						adjacencyList[i].push_back(j+1);
						break ;
					}
					else{
						st.pop();
					}
				}
			}
		}
		else{
			if(subString5 != "}")
				adjacencyList[i].push_back(i+1);
		}
	}
}
 
 
int main()
{
  	
  	ifstream file("code321.txt");
    string s;
    int currLineNumber = 0;
    int flag = 0;
    while(getline(file,s)){
    	if(flag==1){
    		Data.push_back(s);
    	    currLineNumber++;
    	}
    	string cmp = s.substr(0,8);
    	string cmp1 = "int main";
    	if(cmp==cmp1)flag = 1;
	}
	///cout<<currLineNumber<<"\n";
	initializer();
	printList(currLineNumber);
  	
    return 0;
}
