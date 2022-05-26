/*--------------------Universidad Tecnica del Norte-----------------
 * ----------Facultad de Ingenieria en Ciencias Aplicadas----------
 * -------------Carrera de Telecomunicaciones------------
 * --------------------Sistemas Embebidos--------------
 * 
 * Integrantes: Carrion Andres, Donoso Fabricio, Quelal Rony
 * 
 */


#define tam_sin 100 //tamaño de la señal orginal
#define tam_imp 21 //tamaño del impulso

//Importar la señal 
extern double ECG[tam_sin];                  //Importamos o llamamos la señal original
extern double FiltroFir[tam_imp];                              //Importamos o llamamos la señal impulso

double output[tam_sin+tam_imp];                                       //declaramos vector de salida
double mediana_sig[tam_sin];                                       //declaramos vector de salida del suavizado 

void convolucion(double *sig_in,double *sig_out, double *imp, int sig_tam, int imp_tam);      //Llamamos definir funcion
void mediana (double *sig_in, double *mediana_sig, int sig_tam);                           //Definir funcion de suavizado 
void plot_signal(void);                                                                       //Funcion para graficar

void setup() {
  Serial.begin(9600);                                                                         //Inicializamos la comunicación serial

}

void loop() {
  convolucion((double *)&ECG[0], (double *)&output[0], (double *)&FiltroFir[0],   //Llamamos el método de convolución
                   (int) tam_sin, (int) tam_imp);
  mediana ((double *)&ECG[0], (double *)&mediana_sig[0], (int) tam_sin);              //Llamamos el método de mediana
  plot_signal();                                                                                                  //Función para gráficar  
  delay(100);                                                                                                     //Se detiene por un tiempo estimado
  SNR();                                                                                                          //Método SNR



}


/////////////////Filtro FIR Convoluvion//////////////////////////

void convolucion(double *sig_in,double *sig_out, double *imp, int sig_tam, int imp_tam){
  int i,j;
  //poner ceros a vector de salida
  for(i=0;i<(sig_tam+imp_tam);i++){       //Ciclo para convolución
    sig_out[i]=0;                         //Recorrido de la señal
  }
  for(i=0;i<sig_tam;i++){                 //Ciclo anidado
    for(j=0;j<imp_tam;j++){                 
      sig_out[i+j]=sig_out[i+j]+sig_in[i]*imp[j];   //Reeplazo de la señal
    }
  }
}



///////////////SUAVIZADO DE LA SEÑAL////////////////////////
// ---------Mediana---------//

void mediana (double *sig_in, double *mediana_sig, int sig_tam){
  int i,j,k,sig_Temp;
  double vector[5];
  for(k=0;k<sig_tam;k++){   //ciclo para la mediana
    vector[0]=sig_in[k+0];  //Cambio de la señal a la posición del vector 0
    vector[1]=sig_in[k+1];  //"                                         " 1
    vector[2]=sig_in[k+2];  //"                                         " 2
    vector[3]=sig_in[k+3];  //"                                         " 3
    vector[4]=sig_in[k+4];  //"                                         " 4
    for(i=0;i<(4);i++){     //ciclo anidado
      for(j=i+1;j<5;j++){
        if(vector[j]<vector[i]){
          sig_Temp=vector[j];   
          vector[j]=vector[i];
          vector[i]=sig_Temp;  //cambio de valores
        }
      }
    }
    mediana_sig[k]=vector[1];
  }
}

void SNR(){                                   //Método de SNR
  //Promedio señal de entrada "V1"
   float sum=0;
  for(int i=0;i<90;i++){                             //ciclos recorre el numero de datos d ela señal
      sum = sum + ECG[i];   //guarda los valores obtenidos
    }
    double promedio=sum/90;                         //divide par ael numero de datos de la señal
    double v1=((promedio*5)/1023);                  
    Serial.println(String("Valor voltaje Señal: ")+String(v1));//Imprime de forma serial el valor obtenido
    Serial.print("");

 //Promedio señal de entrada "V2"
    float sum2=0;
  for(int i=0;i<90;i++){
      sum2 = sum2 + mediana_sig[i];
    }
    double promedio2=sum2/90;                                          //divide par ael numero de datos de la señal
    float v2=(promedio2*5)/1023;
    
    Serial.println(String("Valor en voltaje del filtro: ")+String(v2)); //Imprime de forma serial el valor obtenido
    Serial.print("");

//   Metrica SNR m=20*log(v2/v1)
//    double metrica=20*log(v2/v1);                                        //
//    Serial.println(String("Valor metrica snr en dBs: ")+String(metrica));//Imprime el valor obtenid entre con relación a lo anteriores resultados
//    Serial.print("");
    
}

//Graficar mi resultado
void plot_signal(void){ 
  int i;
  for(i=0;i<tam_sin;i++){
    Serial.print(String("Senial Original: ")+String(ECG[i]+600));
    Serial.print(",");
    Serial.print(String("Senial Filtrada: ")+String(mediana_sig[i]+300));
    Serial.print(",");
    Serial.println(String("Suavizada: ")+String(output[i]));
    delay(5);
  }
}
