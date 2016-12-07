#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

void createVariables(int n, int m){
    int cuadro[n][m][4]; //variables de cada recuadro
    int aux = 1;        //auxiliar para numerar variables

    cout << "\nc(i,j) = Variables" << endl;
    while(n+m+1+aux < n*m){
        for(int i=0; i<n ; i++){
            for(int j=0; j<m ; j++){
                cuadro[i][j][0] = aux;          //superior  (norte)
                cuadro[i][j][1] = n+aux;        //izquierdo (este)
                cuadro[i][j][2] = n+m+1+aux;    //inferior  (sur)
                cuadro[i][j][3] = n+1+aux;      //derecho   (oeste)

                printf("c(%d,%d) = { %d,%d,%d,%d }\n",i,j,cuadro[i][j][0],cuadro[i][j][1],cuadro[i][j][2],cuadro[i][j][3]);
                aux++;
            }
            aux += m+1; //paso a siguiente fila
        } 
    }
}

int main(int argc, char const *argv[]) {

    int n,m; // n-filas,m-columnas

    ifstream infile("example_input.txt");
    string line;
    while (getline(infile, line)) {
        vector<string> restricciones;
        istringstream ss(line);
        string token;
        int i;

        getline(ss,token,' ');
        n = stoi(token);
        getline(ss,token,' ');
        m = stoi(token);

        printf("n=%d, m=%d\nRestricciones:\n", n,m);
        i=0;
        while (getline(ss, token,' ')){
            restricciones.push_back(token);
            cout << restricciones[i] << endl;
            i++;
        }

        createVariables(n,m);
    }
 
    return 0;
}