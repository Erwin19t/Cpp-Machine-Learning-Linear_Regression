/*
Programa de Regresion Lineal

Compilacion: g++ main.cpp -o Ejecutable -std=c++11
Ejecucion: ./Ejecutable
*/

#include <iostream>
#include <unistd.h>
#include <math.h>
#define Alpha 0.05

using namespace std;

double Initial_Theta(int);
double Evaluate(double, double, int);
double MSE(double, double);
double Grad_MSE(double, double, int, int);
double Relative_Error(double, double, double, double);

int main(){
    double Y[5] = {5, 6, 7, 8, 9};
    double Y_g[5] = {0};
    double Theta_ant[2];            
    double Theta_act[2];
    double mse   = 0;
    double GMSE[2] = {0};
    double Error = 100;
    int i, j;
    int Counter = 1;
 
    //Descomentar esta seccion para probar con valores iniciales aleatorios
    //Theta_ant[0] = Initial_Theta(1);
    Theta_ant[0] = 7;
    Theta_ant[1] = 9;
    sleep(1);
    //Theta_ant[1] = Initial_Theta(2);
    Theta_act[0] = Theta_ant[0];
    Theta_act[1] = Theta_ant[1];

    //Desired weights
    cout<<"Pesos deseados = [5 ; 1]"<<endl;
    //Initial weights
    cout<<"Pesos iniciales= ["<<Theta_act[0]<<" ; "<<Theta_act[1]<<"]"<<endl<<endl;

    while(Counter <= 5){
        //Se evalua la funcion y se calcula el MSE
        for(i = 0; i < 5; i++){
            Y_g[i] = Evaluate(Theta_act[0], Theta_act[1], i);
            mse = MSE(Y_g[i], Y[i]) + mse;
        }
        mse = mse/5;

        //Se calcula el Gradiente
        for(j = 0; j < 2; j++){
            for(i = 0; i < 5; i++){
                GMSE[j] = Grad_MSE(Y_g[i], Y[i], i, j) + GMSE[j];
            }
            GMSE[j] = GMSE[j]*2/5;
        }

        //Paso 5: Se calcula el nuevo vector Theta
        Theta_act[0] = Theta_ant[0] - Alpha*GMSE[0];
        Theta_act[1] = Theta_ant[1] - Alpha*GMSE[1];

        //Se calcula el Error
        Error = Relative_Error(Theta_act[0], Theta_act[1], Theta_ant[0], Theta_ant[1]);


    cout<<"Iteracion "<<Counter<<endl;
    cout<<"Error Medio Cuadratico = "<<mse<<endl;
    cout<<"Gradiente del MSE  = ["<<GMSE[0]<<" ; "<<GMSE[1]<<"]"<<endl;
    cout<<"Nuevo vector Theta = ["<<Theta_act[0]<<" ; "<<Theta_act[1]<<"]"<<endl;
    cout<<"Error = "<<Error<<endl<<endl;
    for(i = 0 ; i < 5 ; i++){
        cout<<"Y("<<i<<") = "<<Y_g[i]<<endl;
    }


        //Actualizamos el vector theta anterior,
        //aumentamos contador de iteraciones
        //y reseteamos algunas variables
        Theta_ant[0] = Theta_act[0];
        Theta_ant[1] = Theta_act[1];
        mse = 0;
        GMSE[0] = 0;
        GMSE[1] = 0; 
        Counter++;
    }
    //Chingo de Impresiones
    return 0;
}

//Paso 1: Inicializar los pesos aleatoriamente
double Initial_Theta(int id){
    double Theta;
    int Sign;
    srand(id + (int)time(NULL));
    Sign = 1 + rand()%100;
    if(Sign%2 == 0){    //Para genera numeros pseudoaleatorios positivos
        srand(id + (int)time(NULL));
        //Theta = 1 + rand()%9;
        Theta = 1 + ((rand()%(10001))/1000.00f);
    }
    else{               //Para generar numeros pseudoaleatorios negativos
        srand(id + (int)time(NULL));
        Theta = -9 + ((rand()%(-10001))/1000.00f);
    }
    return Theta;
}

//Paso 2: Evaluacioes
double Evaluate(double theta_0, double theta_1, int x){
    return theta_0 + theta_1*x;
}

//Paso 3: Calculo de Error Medio Cuadratico
double MSE(double y_g, double y){
    return pow((y_g - y),2);
}

//Paso 4: Calculo del Gradiente del MSE
double Grad_MSE(double y_g, double y, int x, int exp){
    return (y_g - y)*pow(x,exp);
}

//Paso 6: Calculo de Error Relativo (Criterio de Parada)
double Relative_Error(double theta_g0, double theta_g1, double theta_0, double theta_1){
    double Norm_act, Norm_ant, err;
    Norm_act = sqrt(pow(theta_g0, 2) + pow(theta_g1, 2));
    Norm_ant = sqrt(pow(theta_0, 2) + pow(theta_1, 2));
    err    = abs(Norm_act - Norm_ant);
    return err;
}
