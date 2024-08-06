#include <iostream>
#include <vector>

using namespace std;

int n, numMagico, kesimo, contK=1, flag=0;

void cuadradosMagicos(vector<vector<int>>& M, vector<int>& v, int i, int j, int sumaFilaActual, vector<int>& sumaColumnas, vector<int>& sumaDiagonales){
    if(contK>kesimo){
        return;
    }
    if(i==n && j==n){
        if(contK==kesimo){
            for(int i1=0; i1<M.size(); i1++){
                for(int j1=0; j1<M.size(); j1++){
                    cout << M[i1][j1] << " ";
                }
                cout << endl;
            }
            flag=1;
            contK++;
        } else {
            contK++;
        }
    } else{
        for(int k=0; k<v.size(); k++){
            if(v[k] != 0){
                v[k]=0; // Do. (1)
                if(i>n-1 || i<0 || j>n-1 || j<0){
                    cout << i << " " << j << endl;
                }
                M[i][j]=k+1; // Do. (2)
                if(sumaFilaActual+k+1<=numMagico && sumaColumnas[j]+k+1<=numMagico ){ // Si mi fila actual o mi columna supera el numero magico no hago nada.
                    sumaColumnas[j]+=k+1; // Do. (3)
                    if(j==n-1){
                        if(sumaFilaActual+k+1 == numMagico){
                            if(i==n-1){ // Estoy en la primer diagonal.
                                if(sumaColumnas[j] == numMagico && sumaDiagonales[0]+k+1 == numMagico){
                                    // No cambio sumaDiagonales ya que se que se cumple y luego en el caso base no lo chequeo.
                                    cuadradosMagicos(M, v,i+1,n, 0, sumaColumnas, sumaDiagonales); //ponemos j=n para el caso base
                                }
                            } else{
                                if(i==0){ // Estamos en la segunda diagonal.
                                    sumaDiagonales[1] += k+1;
                                    cuadradosMagicos(M, v,i+1,0, 0, sumaColumnas, sumaDiagonales);
                                    sumaDiagonales[1] -= k+1;
                                } else{ // No estamos en una diagonal.
                                    cuadradosMagicos(M, v,i+1,0, 0, sumaColumnas, sumaDiagonales);
                                }
                            }
                        }
                    } else {
                        // Do
                        if(j==i){ // Estoy en la diagonal 1.
                            sumaDiagonales[0] += k+1;
                        }
                        if(j==n-1-i){ // Estoy en la diagonal 2.
                            sumaDiagonales[1] += k+1;

                        }

                        if(sumaDiagonales[0] <= numMagico && sumaDiagonales[1] <= numMagico) {
                            if(i==n-1 && j==0){
                                if(sumaDiagonales[1]==numMagico){
                                    cuadradosMagicos(M, v, i, j + 1, sumaFilaActual + k + 1, sumaColumnas,
                                                     sumaDiagonales);
                                }
                            } else {
                                cuadradosMagicos(M, v, i, j + 1, sumaFilaActual + k + 1, sumaColumnas,
                                                 sumaDiagonales);//SACO EL CANT+=
                            }
                        }

                        // Undo.
                        if(j==i){ // Estoy en la diagonal 1.
                            sumaDiagonales[0] -= k+1;
                        }
                        if(j==n-1-i){ // Estoy en la columna 2.
                            sumaDiagonales[1] -= k+1;
                        }
                    }
                    sumaColumnas[j]-=k+1; // Undo(3).
                }
                M[i][j]=0; // Undo. (2)
                v[k]=1; // Undo. (1)
            }
        }
    }
}


int main(){
    cin >> n;
    cin >> kesimo;

    numMagico=(n*(n*n+1))/2;

    vector<vector<int>> M;
    vector<int> m(n,0);
    for(int i=0; i<n; i++){
        M.push_back(m); // Matriz que representa el cuadrado magico.
    }

    vector<int> v(n*n, 1);
    vector<int> sumaDiagonales(2,0);

    cuadradosMagicos(M,v,0,0,0,m, sumaDiagonales);
    if(flag==0){
        cout << -1;
    }
    return 0;
};
