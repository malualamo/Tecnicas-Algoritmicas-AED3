//
// Created by malen on 15/4/2023.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
vector<pair<int,int>> v;
vector<int> posiciones;

bool comp(pair<int, int> p1, pair<int, int> p2){
    return (p1.second < p2.second);
}

int main(){
    cin >> n;
    v.resize(n+1);
    posiciones.resize(2*n+1,-1);

    for(int i=1; i<=n; i++){
        cin >> v[i].first >> v[i].second;
        // Voy ordenando el vector posiciones, en caso de colisiones me quedo con la franja mas chica.
        if(posiciones[v[i].second]==-1){
            posiciones[v[i].second]=i;
        } else{
            if(v[posiciones[v[i].second]].first<v[i].first){
                posiciones[v[i].second]=i;
            }
        }
    }

    // Recorro el vector posiciones y me voy quedando las posiciones que no se solapen.
    int max=-1;
    vector<int> res;
    for(int i=1; i<= 2*n; i++){
        if(posiciones[i]!=-1){
            if(v[posiciones[i]].first >= max){
                max=v[posiciones[i]].second;
                res.push_back(posiciones[i]);
            }
        }
    }
    cout << res.size() << endl;
    for(int i=0; i<res.size(); i++){
        cout << res[i] << " ";
    }
    return 0;
};