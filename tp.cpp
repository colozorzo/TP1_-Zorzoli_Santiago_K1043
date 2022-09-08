#include <iostream>
#include <fstream>

using namespace std;

const int dprod {5};
const int dclie {8};

void ordenar_doble(float vec[], const int dim, string vpos[]){//usando algoritmo de selección
	int min;
    for (int i = 0; i < dim-1; i++){
        min=i;
        for ( int j = i+1; j < dim; j++){
            if (vec[j]<vec[min]){    
				min = j;
            }        
        }
        //intecambia i y min
        swap(vec[i],vec[min]); 
        swap(vpos[i],vpos[min]);
    }
}

void may_vec (float vec[dclie], int dim, int& max){
    int maux/*maximo auxiliar*/ = vec[0];
    for (int i = 0; i < dim; i++){
        if ( vec[i] > maux){
            maux = vec[i];
            max = i;
        }
    }
}

int main(int argc, char const *argv[])
{
    string clie [dclie] ;
    string prod [dprod] ;    
    float sumpesos [dclie][dprod];//se usa en el punto 1 y para almacenar los kg x producto y cliente
    float distprod [dclie][dprod];//se usa en el punto 2 y para almacenar los km x producto y cliente
    float cantpesos[dclie]{0,0,0,0,0,0,0,0};//se usa en el punto 2 y para almacenar la cantidad de productos con mas de 13000kg por cliente
    int cantviajes [dprod]{0,0,0,0,0};//se usa en el punto 3 y para almacenar la cantidad de viajes x producto 
    
    //carga de datos
    
    ifstream archilec;
    archilec.open("Datos.txt");
    
    if (!archilec) {
        cout << "No se puedo abrir el archivo de datos" << endl;
        return 1;
    }
    
    int iclie, iprod;
    float peso, dist;
    
    while (archilec >> iclie >> iprod >> peso >> dist) {
        sumpesos[iclie][iprod] += peso;
        distprod[iclie][iprod] += dist;
        cantviajes[iprod]++;
    }
    archilec.close();

    archilec.open("Nombres.txt");

    if (!archilec) {
        cout << "No se puedo abrir el archivo de datos" << endl;
        return 1;
    }
    
    for (int i = 0; i < 8; i++){
        archilec >> clie[i];
    }
    for (int i = 0; i < 5; i++){
    
    archilec >> prod[i];
    }
    archilec.close();
  
    //punto 1
    
    cout<<"Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: "<<endl;
    
    for (int i = 0; i < dclie; i++){//revisa cada uno de los productos x cliente, y si tiene mas de 13000kg aumenta la cantidad 
        cout<<clie[i]<<": ";
        for (int j = 0; j < dprod; j++){
            if (sumpesos[i][j] > 13000){
            cout<<prod[j]<<" ";
            cantpesos[i]++;
            }
        }
        cout<<endl;
    }

    //punto 2

    int maxpesos {0};//se usapara conseguir el numero donde esta almacenado el cliente del anterior punto
    float distaux[dprod];//se usa para conseguir los km de los productos del anterior punto
    
    may_vec(cantpesos,dclie,maxpesos);
    for (int i = 0; i < dprod; i++)
    {
        distaux[i]=distprod[maxpesos][i];
    }
   
    ordenar_doble(distaux,dprod,prod);//ordena de forma ascendente
    cout<<"\nListado de Km recorridos por tipo de producto (ascendente):"<<endl;
    for (int i = 0; i < dprod; i++)
    {
        cout<<prod[i]<<": "<<distaux[i]<<endl;
    }
        
    //punto 3
    
    int maxkm {0};//se usa para averiguar el producto con mayor cantidad de km del anterior punto
    
    may_vec(distaux,dprod,maxkm);
    cout<<"\nCantidad de entregas para el tipo de producto "<<prod[maxkm]<<": "<<cantviajes[maxkm];
    return 0;
}

