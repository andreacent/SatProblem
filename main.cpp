#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
vector<string> restricciones;
vector<string> clausulas;
vector<string> solucion;

void createVariables(int n, int m){
    int c[n][m][4]; //variables de cada recuadro
    int z[n][m];   //celda interior=FALSE, celda exterior=TRUE
    int r[n][m][n][m]; //Variables que diran la relacion r
    int aux = 1;    //auxiliar para numerar variables
    int contador = 1; //Aumenta de a uno cada valor en z
    int hiperContador = 0; //Aumenta de a uno cada valor en r
    cout << "\nc(i,j), Variables, ¿celda exterior?" << endl;

    for(int i=0; i<n ; i++){
        for(int j=0; j<m ; j++){
            c[i][j][0] = aux;          //superior  (norte)
            c[i][j][1] = n+aux;        //izquierdo (oeste)
            c[i][j][2] = n+m+1+aux;    //inferior  (sur)
            c[i][j][3] = n+1+aux;      //derecho   (este)
            z[i][j] = n*(n+1)+m*(m+1)+contador;
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < m; ++l) {
                    r[i][j][k][l] = n*(n+1)+m*(m+1)+n*m+contador+hiperContador;
                    hiperContador++;      
                }
            }
            printf("c(%d,%d), { %d,%d,%d,%d }, %d\n",i,j,c[i][j][0],c[i][j][1],c[i][j][2],c[i][j][3],z[i][j]);
            aux++;
            contador++;
        }
        aux += m+1; //paso a siguiente fila
    }

    //cout << "\nCLAUSULAS TIPO 1" << endl;
    char a;
    string f,h;
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            a = restricciones[i].at(j);
            switch(a){
                case '.':
                    break; 
                case '0':
                    for(int k=0; k<4;k++) clausulas.push_back("-"+to_string(c[i][j][k])+" 0");
                    //printf("-%d\n",c[i][j][k]);
                    break; 
                case '1':
                    f="";
                    for(int k=0; k<4;k++) f += to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][1])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][2])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][1])+" -"+to_string(c[i][j][2])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][1])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][2])+" -"+to_string(c[i][j][3])+" 0");

                    /*
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    printf("-%d -%d\n",c[i][j][0],c[i][j][1]);
                    printf("-%d -%d\n",c[i][j][0],c[i][j][2]);
                    printf("-%d -%d\n",c[i][j][0],c[i][j][3]);
                    printf("-%d -%d\n",c[i][j][1],c[i][j][2]);
                    printf("-%d -%d\n",c[i][j][1],c[i][j][3]);
                    printf("-%d -%d\n",c[i][j][2],c[i][j][3]);
                    */

                    break; 
                case '2':
                    // Clausula 'base'
                    f="";
                    for(int k=0; k<4;k++) f += to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);

                    // Clausulas 'no mas de dos'
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][1])+" -"+to_string(c[i][j][2])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][1])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][1])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][3])+" 0");

                    // Clausulas 'mas de uno' *Creo que esto va*
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][1])+" "+to_string(c[i][j][2])+" 0");
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][1])+" "+to_string(c[i][j][3])+" 0");
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][2])+" "+to_string(c[i][j][3])+" 0");
                    clausulas.push_back(to_string(c[i][j][1])+" "+to_string(c[i][j][2])+" "+to_string(c[i][j][3])+" 0");


                    /*
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    printf("-%d -%d -%d\n",c[i][j][0],c[i][j][1],c[i][j][2]);
                    printf("-%d -%d -%d\n",c[i][j][0],c[i][j][1],c[i][j][3]);
                    printf("-%d -%d -%d\n",c[i][j][0],c[i][j][2],c[i][j][3]);
                    printf("-%d -%d -%d\n",c[i][j][1],c[i][j][2],c[i][j][3]);
                    printf("%d %d %d\n",c[i][j][0],c[i][j][1],c[i][j][2]);
                    printf("%d %d %d\n",c[i][j][0],c[i][j][1],c[i][j][3]);
                    printf("%d %d %d\n",c[i][j][0],c[i][j][2],c[i][j][3]);
                    printf("%d %d %d\n",c[i][j][1],c[i][j][2],c[i][j][3]);
                    */

                    break; 
                case '3':
                    // Clausula 'base'
                    f="";
                    for(int k=0; k<4;k++) f += to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);

                    // Clausula 'no mas de 3'
                    h="";
                    for(int k=0; k<4;k++) h += "-"+to_string(c[i][j][k]) +" ";
                    h=h+"0";
                    clausulas.push_back(h);

                    // Clausulas 'mas de dos' *Creo que esto va*
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][1])+" 0");
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][2])+" 0");
                    clausulas.push_back(to_string(c[i][j][0])+" "+to_string(c[i][j][3])+" 0");
                    clausulas.push_back(to_string(c[i][j][1])+" "+to_string(c[i][j][2])+" 0");
                    clausulas.push_back(to_string(c[i][j][1])+" "+to_string(c[i][j][3])+" 0");
                    clausulas.push_back(to_string(c[i][j][2])+" "+to_string(c[i][j][3])+" 0");

                    /*
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    cout << h << endl;
                    printf("%d %d\n",c[i][j][0],c[i][j][1]);
                    printf("%d %d\n",c[i][j][0],c[i][j][2]);
                    printf("%d %d\n",c[i][j][0],c[i][j][3]);
                    printf("%d %d\n",c[i][j][1],c[i][j][2]);
                    printf("%d %d\n",c[i][j][1],c[i][j][3]);
                    printf("%d %d\n",c[i][j][2],c[i][j][3]);
                    */

                    break;
                case '4':
                    printf("----\nc(%d,%d) %c\n",i,j,a);

                    for(int k=0; k<4;k++){                        
                        clausulas.push_back(to_string(c[i][j][k])+" 0");
                        printf("%d\n",c[i][j][k]);
                    }
                    break;
            }
            // Clausulas tipo 2 (Externas)
            if (i==0) {
                clausulas.push_back(to_string(c[i][j][1])+" "+to_string(z[i][j])+" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][1])+" 0");
            }
            if (i==n-1) {
                clausulas.push_back(to_string(c[i][j][3])+" "+to_string(z[i][j])+" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][3])+" 0");   
            }
            if (j==0){
                clausulas.push_back(to_string(c[i][j][2])+" "+to_string(z[i][j])+" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][2])+" 0");
            }
            if (j==m-1){
                clausulas.push_back(to_string(c[i][j][0])+" "+to_string(z[i][j])+" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" 0");
            }
            // Clausulas tipo 2 (Internas)
            if (i!=0 && i!=n-1 && j!=0 && j!=m-1) {
                // X <=> Y === (X v ~Y)^(~X v Y)
                //(X v ~Y)
                clausulas.push_back(to_string(z[i][j])+" "+to_string(c[i][j][0])+" -"+to_string(z[i][j+1])+" 0");
                clausulas.push_back(to_string(z[i][j])+" "+to_string(c[i][j][3])+" -"+to_string(z[i+1][j])+" 0");
                clausulas.push_back(to_string(z[i][j])+" "+to_string(c[i][j][2])+" -"+to_string(z[i][j-1])+" 0");
                clausulas.push_back(to_string(z[i][j])+" "+to_string(c[i][j][1])+" -"+to_string(z[i-1][j])+" 0");

                //(~X v Y)
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" -"+to_string(c[i][j][3])+" -"+to_string(c[i][j][2])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" -"+to_string(c[i][j][3])+" "+to_string(z[i][j-1])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" "+to_string(z[i+1][j])+" -"+to_string(c[i][j][2])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" "+to_string(z[i+1][j])+" "+to_string(z[i][j-1])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" -"+to_string(c[i][j][3])+" -"+to_string(c[i][j][2])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" -"+to_string(c[i][j][3])+" "+to_string(z[i][j-1])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" "+to_string(z[i+1][j])+" -"+to_string(c[i][j][2])+" 0");
                clausulas.push_back(to_string(z[i-1][j])+" -"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" "+to_string(z[i+1][j])+" "+to_string(z[i][j-1])+" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" -"+to_string(c[i][j][3])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" -"+to_string(c[i][j][3])+" "+to_string(z[i][j-1])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" -"+to_string(z[i+1][j])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(c[i][j][0])+" "+to_string(z[i+1][j])+" "+to_string(z[i][j-1])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" -"+to_string(c[i][j][3])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" -"+to_string(c[i][j][3])+" "+to_string(z[i][j-1])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" "+to_string(z[i+1][j])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(z[i][j+1])+" "+to_string(z[i+1][j])+" "+to_string(z[i][j-1])+" -"+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i-1][j])+" -"+to_string(z[i][j])+" "+to_string(c[i][j][1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(c[i][j][0])+" -"+to_string(z[i][j+1]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(c[i][j][3])+" -"+to_string(z[i+1][j]) +" 0");
                clausulas.push_back("-"+to_string(z[i][j])+" "+to_string(c[i][j][2])+" -"+to_string(z[i][j-1]) +" 0");
            }

            // Clausulas de tipo 3
            // Aqui irian r[i][j][i][j] (las reflexivas)
            clausulas.push_back(to_string(r[i][j][i][j])+" 0");
            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < m; ++l) {
                    // Aqui irian las internas
                    //Norte - d = 0
                    if (l != 0 ) {
                        clausulas.push_back("-"+to_string(r[i][j][k][l])+" "+to_string(c[k][l][0])+" "+to_string(r[i][j][k][l-1]) +" 0");
                    }

                    //Oeste - d = 1

                    if (k != 0) {
                        clausulas.push_back("-"+to_string(r[i][j][k][l])+" "+to_string(c[k][l][1])+" "+to_string(r[i][j][k-1][l]) +" 0");
                    }

                    //Sur - d = 2
                    if (l != m-1) {
                        clausulas.push_back("-"+to_string(r[i][j][k][l])+" "+to_string(c[k][l][2])+" "+to_string(r[i][j][k][l+1]) +" 0");
                    }

                    //Este - d = 3

                    if (k != n-1){
                        clausulas.push_back("-"+to_string(r[i][j][k][l])+" "+to_string(c[k][l][3])+" "+to_string(r[i][j][k+1][l]) +" 0");
                    }
                }
            }

            // Celdas interiores alcanzables

            for (int k = 0; k < n; ++k) {
                for (int l = 0; l < m; ++l) {
                    clausulas.push_back("-"+to_string(z[i][j])+" -"+to_string(z[k][l])+" "+to_string(r[i][j][k][l])+" 0");
                }
            }
        }
    }
}

void createDimacsFile(int n, int m) {

    ofstream archivo;
    archivo.open("entradaCNF.txt");
    archivo << "p cnf " << (n+1)*n+(m+1)*m+n*m+m*n*m*n+n*(m-1)+(n-1) << " " << clausulas.size() <<"\n";
    for (unsigned i = 0; i < clausulas.size(); ++i) {
        archivo << clausulas[i] << "\n";
    }
    archivo.close();
}

bool traduceSATFile(int n, int m){
    string tipo = "SAT";
    ifstream infile("salidaCNF.txt");
    string traduccion;
    int i = 0;
    cout<<"traduccion \n";
    getline(infile, traduccion);
    if (tipo.compare(traduccion)==0) {
        while(getline(infile,traduccion,' ') && i<(n+1)*n+(m+1)*m){
            solucion.push_back(traduccion);
            cout<<traduccion<<endl;
            i++;
        }
    } else {
        cout << "No se encontro solucion \n";
        return false;
    }               
    cout<<"TAMANO " << solucion.size()<<endl;
    infile.close();
    return true;
}

void createOutputFile(string firstLine, bool sat, int n, int m) {
    ofstream output;
    output.open("output.txt",ios::app);
    output << firstLine<<"\n";
    if (!sat) {
        output<<"UNSAT \n";
    } else { 
        output << n << " " << m << " ";
        int horizontales[n+1][n];
        int verticales[m][m+1];
        int aux;
        int contador=0;
        int i=0;
        int j=0;
        bool cambio = false;
        string tmp;
        for (unsigned k = 0; k < solucion.size(); ++k) {
            tmp = solucion[k];
            string dummy = to_string(k+1);        
            if (tmp.compare(dummy)==0) {
                aux=1;
            } else{
                aux=0;
            }
    
            if (cambio) {
                // Paso al arreglo de verticales
                verticales[i][j]=aux;
            } else {
                // Paso al arreglo de horizontales
                horizontales[i][j]=aux;
            }
            contador++;
            j++;
            if (contador == n && j == m && !cambio) {
                cambio = true;
                contador = 0;
                j = 0;
            } else if (contador == m+1 && j==m+1 && cambio){
                cambio = false;
                contador = 0;
                i++;
                j = 0;
            }
        }
        // Reinicio de variables
        i=0;
        j=0;
        cambio = false;
        while(i < n+1){
            if (cambio) {
                while(j<m+1) {
                    output<<verticales[i][j];
                    j++;
                }
                output<<" ";
                j=0;
                cambio=false;
                i++;
            } else {
                while(j<n){
                    output<<horizontales[i][j];
                    j++;
                }
                cambio = true;
                j=0;
                output<<" ";
                if (i==n) {
                    output<<"\n";
                    break;
                }
            }   
        }
    }
    output.close();
}

int main(int argc, char const *argv[]) {

    int n,m; // n-filas,m-columnas
    bool resultado;
    
    ifstream infile(argv[1]);  //Lectura pasada a traves de stdin
    string line;
    while (getline(infile, line)) {
        cout<<"Comienzo de iteracion principal, esta es line: \n";
        cout<<line<<"\n";
        istringstream ss(line);
        string token;

        getline(ss,token,' ');
        n = stoi(token);
        getline(ss,token,' ');
        m = stoi(token);

        printf("n=%d, m=%d\nRestricciones:\n", n,m);
        while (getline(ss, token,' ')){
            restricciones.push_back(token);
        }

        createVariables(n,m);

        createDimacsFile(n,m);

        int status=system("minisat entradaCNF.txt salidaCNF.txt > /dev/null");
        if (status) {
            resultado=traduceSATFile(n,m);
        } else {
            cout<<"Ocurrio un error al ejecutar: \"minisat entrada.txt salida.txt > /dev/null\" \n";
            return EXIT_FAILURE;
        }

        cout<< "Aqui se llama funcion que modifica archivo salida \n";
        createOutputFile(line, resultado, n, m);
        restricciones.clear();
        clausulas.clear();
        solucion.clear();
    }
    return 0;
}