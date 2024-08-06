//
// Created by jerem on 4/14/2023.
//
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
long long c,n,r,m;

long long mod_bin_exp(long long x, long long y, long long n) {
    if(y==0){
        return 1;
    }
    if(y%2==0){
        return (mod_bin_exp(x,y/2,n)*mod_bin_exp(x,y/2,n)) % n;
    } else{
        return ((mod_bin_exp(x,y/2,n)*mod_bin_exp(x,y/2,n)) % n)*x % n;
    }
}

int main(){
    cin >> c;
    while(c--){
        cin >> n >> r >> m;
        vector<long long> v(n);
        for(int i=0; i<n; i++){
            cin >> v[i];
        }

        if(n<2){
            bool res = v[0]%m==r;
            if(res){
                cout << "Si" << endl;
            } else {
                cout << "No" << endl;
            }
        }

        vector<bool> restosi(m, false);
        vector<bool> restosi1(m,false);

        restosi[(v[0]+v[1])%m]=true;

        // v0 - v1 puede ser negativo y c++ me retorna negativo el modulo de un negativo.
        if((v[0]-v[1])%m<0){
            restosi[(v[0]-v[1])%m+m]=true;
        } else {
            restosi[(v[0]-v[1])%m]=true;
        }
        restosi[(v[0]*v[1])%m]=true;
        restosi[mod_bin_exp(v[0],v[1],m)]=true;

        // Funcion
        for(int i=2; i<n; i++){
            vector<long long> posicionesCambiadas;
            for(int j=0; j<restosi.size(); j++){
                if(restosi[j]){
                    restosi1[(j+v[i])%m]=true; posicionesCambiadas.push_back((j+v[i])%m);
                    if((j-v[i])%m<0){
                        restosi1[(j-v[i])%m+m]=true; posicionesCambiadas.push_back((j-v[i])%m+m);
                    } else {
                        restosi1[(j-v[i])%m]=true; posicionesCambiadas.push_back((j-v[i])%m);
                    }
                    restosi1[(j*v[i])%m]=true; posicionesCambiadas.push_back((j*v[i])%m);

                    int indice=mod_bin_exp(j,v[i],m);
                    restosi1[indice]=true; posicionesCambiadas.push_back(indice);

                    // Voy limpiando restosi.
                    restosi[j]=false;
                }
            } // restosi termina siendo un vector lleno de false.

            for(int k=0; k<posicionesCambiadas.size(); k++){
                restosi[posicionesCambiadas[k]]=true;
                restosi1[posicionesCambiadas[k]]=false; // Limpio restosi1.
            }
        }

        if(restosi[r]){
            cout << "Si" << endl;
        } else{
            cout << "No" << endl;
        }

    }
    return 0;
}