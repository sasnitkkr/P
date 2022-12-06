#include<bits/stdc++.h>
using namespace std;

int main(){
    string txt, pat;
    cout<<"enter string ";
    cin>>txt;
    cout<<"enter pattern ";
    cin>>pat;
    int n=txt.length();
    int m=pat.length();
    int i, j;

    for(i=0; i<n-m+1; i++){
        for(j=0; j<m; j++){
            if(txt[i+j]!=pat[j])
                break;
        }
        if(j==m)
            cout<<"Pattern found at shift "<<i<<endl;
    }
}