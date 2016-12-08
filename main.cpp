#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
vector<string> restricciones;
vector<string> clausulas;

void createVariables(int n, int m){
    int c[n][m][4]; //variables de cada recuadro
    bool z[n][m];   //celda interior=FALSE, celda exterior=TRUE
    int aux = 1;    //auxiliar para numerar variables

    cout << "\nc(i,j), Variables, ¿celda exterior?" << endl;
    while(n+m+1+aux < n*m){
        for(int i=0; i<n ; i++){
            for(int j=0; j<m ; j++){
                c[i][j][0] = aux;          //superior  (norte)
                c[i][j][1] = n+aux;        //izquierdo (este)
                c[i][j][2] = n+m+1+aux;    //inferior  (sur)
                c[i][j][3] = n+1+aux;      //derecho   (oeste)

                if(i==0 || i==n-1 || j==0 || j==m-1) z[i][j] = true;
                else z[i][j] = false;

                printf("c(%d,%d), { %d,%d,%d,%d }, %d\n",i,j,c[i][j][0],c[i][j][1],c[i][j][2],c[i][j][3],z[i][j]);
                aux++;
            }
            aux += m+1; //paso a siguiente fila
        } 
    }

    cout << "\nFormulas (Cláusulas tipo 0)" << endl;
    char r;
    string f;
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            r = restricciones[i].at(j);
            //printf("----\nc(%d,%d) %c\n",i,j,r);
            switch(r){
                case '.':
                    break; 
                case '0':
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    for(int k=0; k<4;k++){                        
                        clausulas.push_back("-"+to_string(c[i][j][k])+" 0");
                        printf("-%d\n",c[i][j][k]);
                    }
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

                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    //printf("-%d -%d\n",c[i][j][0],c[i][j][1]);
                    //printf("-%d -%d\n",c[i][j][0],c[i][j][2]);
                    //printf("-%d -%d\n",c[i][j][0],c[i][j][3]);
                    //printf("-%d -%d\n",c[i][j][1],c[i][j][2]);
                    //printf("-%d -%d\n",c[i][j][1],c[i][j][3]);
                    //printf("-%d -%d\n",c[i][j][2],c[i][j][3]);
                    break; 
                case '2':
                    f="";
                    for(int k=0; k<4;k++) f += to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][1])+" -"+to_string(c[i][j][2])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][1])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][0])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][3])+" 0");
                    clausulas.push_back("-"+to_string(c[i][j][1])+" -"+to_string(c[i][j][2])+" -"+to_string(c[i][j][3])+" 0");

                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    //printf("-%d -%d -%d\n",c[i][j][0],c[i][j][1],c[i][j][2]);
                    //printf("-%d -%d -%d\n",c[i][j][0],c[i][j][1],c[i][j][3]);
                    //printf("-%d -%d -%d\n",c[i][j][0],c[i][j][2],c[i][j][3]);
                    //printf("-%d -%d -%d\n",c[i][j][1],c[i][j][2],c[i][j][3]);
                    break; 
                case '3':
                    f="";
                    for(int k=0; k<4;k++) f += to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);
                    f="";
                    for(int k=0; k<4;k++) f += "-"+to_string(c[i][j][k]) +" ";
                    f=f+"0";
                    clausulas.push_back(f);
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    cout << f << endl;
                    //printf("-%d -%d -%d -%d\n",c[i][j][0],c[i][j][1],c[i][j][2],c[i][j][3]);
                    break;
                case '4':
                    printf("----\nc(%d,%d) %c\n",i,j,r);
                    for(int k=0; k<4;k++){                        
                        clausulas.push_back(to_string(c[i][j][k])+" 0");
                        printf("%d\n",c[i][j][k]);
                    }
                    break;
            }
        }
    }
}

void createDimacsFile(int n, int m) {

    ofstream archivo;
    archivo.open("tmp.txt");
    archivo << "p cnf " << (n+1)*n+(m+1)*m << " " << clausulas.size() <<"\n";
    for (unsigned i = 0; i < clausulas.size(); ++i) {
        archivo << clausulas[i] << "\n";
    }
    archivo.close();
}

int main(int argc, char const *argv[]) {

    int n,m; // n-filas,m-columnas
    
    ifstream infile("example_input.txt");
    //ifstream infile(argv[1]);  //Lectura pasada a traves de stdin
    string line;
    while (getline(infile, line)) {
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

        createDimacsFile(n,m);


        // IMPRIMIR CNF
        //int num_vars = (n+1)*n+(m+1)*m;
        //int num_claus = 0;
        //ofstream myfile;
        //myfile.open ("example.cnf");
        //myfile << "p cnf " << num_vars << " " << num_claus << "\n";
        //myfile.close();
    }
 
    return 0;
}