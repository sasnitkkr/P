#include<bits/stdc++.h>
using namespace std;

vector<int> computeLPS(string pat){
    int m=pat.length();
    vector<int> lps(m,0);
    lps[0]=1;
    int i=1, j=0;
    while(i<m){
        if(pat[i]==pat[j]){
            i++;
            j++;
            lps[i]=j;
        }else{
            if(j==0){
                lps[i]=0;
                i++;
            }else{
                j=lps[j-1];
            }
        }
    }
    return lps;
}

void kmp(string txt, string pat){
    int n=txt.length();
    int m=pat.length();
    vector<int> lps=computeLPS(pat);
    int i=0, j=0;
    while(i<n){
        if(txt[i]==pat[j]){
            i++;
            j++;
        }
        if(j==m){
            cout<<"pattern found at shift "<<i-j<<endl;
            j=lps[j-1];
        }
        if(i<n && txt[i]!=pat[j]){
            if(j==0){
                i++;
            }else{
                j=lps[j-1];
            }
        }
    }
}

int main(){
    string txt, pat;
    cout<<"enter string ";
    cin>>txt;
    cout<<"enter pattern ";
    cin>>pat;
    kmp(txt, pat);
}