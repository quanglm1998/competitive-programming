#include<bits/stdc++.h>
using namespace std;
int n,p,k, a[200010],sum[200010];
int get(int pos){
    if(pos<0) return 0;
    int ans=0;
    while(pos >= k-1){
        ans+=a[pos];
        pos=pos-k;
    }
    if(pos>=0) ans+=sum[pos];
    return ans;
}
int main(){
    int t; cin>>t;
    while(t--){
        int ans;
        cin>>n>>p>>k;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        sort(a,a+n);
        for(int i=0;i<n;i++){
            if(i==0) sum[0]=a[0];
            else{
                sum[i]=a[i]+sum[i-1];
            }
        }
        int l=0;
        int r=(n-n%k)/k;
        int mid;
        while(l<=r){
            mid=(l+r)>>1;
            if(get(mid*k-1)<=p){
                ans=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        l=ans*k-1;
        r=(ans+1)*k-2;
        // cout<<r<<" "<<get(r)<<endl;
        while(l<=r){
            mid=(l+r)>>1;
            if(get(mid)<=p){
                ans=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        cout<<ans+1<<endl;


        }
}