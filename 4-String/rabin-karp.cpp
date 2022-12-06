#include<bits/stdc++.h>
using namespace std;

#define d 256

void search(string txt, string pat, int p){

    int n=txt.length();
    int m=pat.length();
    int txt_hash=0;
    int pat_hash=0;
    int i, j;
    int high_power=1;

    for(i=1; i<=m-1; i++){
        high_power=(high_power*d)%p;
    }

    // first window
    for(i=0; i<m; i++){
        txt_hash=(txt_hash*d+txt[i])%p;
        pat_hash=(pat_hash*d+pat[i])%p;
    }

    for(i=0; i<=n-m; i++){
        if(txt_hash==pat_hash){
            for(j=0; j<m; j++){
                if(txt[i+j]!=pat[j])
                    break;
            }
            if(j==m)
                cout<<"pattern found at index "<<i<<endl;
        }
        if(i+m<n){
            txt_hash= ((txt_hash-txt[i]*high_power)*d+txt[i+m])%p;
            if(txt_hash<0){
                txt_hash=txt_hash+p;
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
    search(txt, pat, INT_MAX);
    return 0;
}