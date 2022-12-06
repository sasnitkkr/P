#include<bits/stdc++.h>
using namespace std;

#define NO_OF_CHARS 256

int getNextState(string pat, int currentState, int currentAlphabet){
    if(currentAlphabet==pat[currentState]){
        return currentState+1;
    }

    // get length of longest proper prefix that is also a suffix
    // start with the largest possible prefix
    // pat[0...currentState-1]currentAlphabet
    for(int i=currentState; i>=1; i--){
        if(currentAlphabet==pat[i-1]){
            int j;
            for(j=0; j<i; j++){
                if(pat[j]!=pat[currentState-i+1+j]){
                    break;
                }
            }
            if(j==i){
                return i;
            }
        }
    }

    return 0;
}

computeTF(string pat, vector<vector<int>>& TF){
    int m=pat.length();
    for(int i=0; i<=m; i++){
        for(int j=0; j<NO_OF_CHARS; j++){
            TF[i][j]=getNextState(pat, i, j);
        }
    }
}

void search(string txt, string pat){
    int n=txt.length();
    int m=pat.length();
    int currentState=0;
    vector<vector<int>> TF(m+1, vector<int>(NO_OF_CHARS));
    computeTF(pat, TF);
    int i;
    for(i=0; i<n; i++){
        currentState=TF[currentState][txt[i]];
        if(currentState==m){
            cout<<"Pattern Found at shift "<<i-m+1<<"\n";
        }
    }
}

int main(){
    string txt, pat;
    txt="abbababbbabbabbaba";
    pat="aba";
    search(txt, pat);
    return 0;
}