//////////////////////TAMANO DE LAS SENALES//////////////////////////////////////////////////

#define tamano_se 100 //tamano senal 

//import signal to another .h file 
extern double flex_sensor [tamano_se];

double SNR[tamano_se];
double salida_senial[tamano_se];

////////////////////////DEFINIR LA FUNCION///////////////////////////////////////////////////

void mediana (double *se_in, double *salida_senial, int se_tamano, int filter);
void plot_senial(void);

void setup() {
  Serial.begin(9600);     //Inicializar la comunicacion serial 
}

void loop() {
  mediana ((double *)&flex_sensor[0], (double *)&salida_senial[0], (int) tamano_se,5);
  SNRsensor();
  plot_senial();
  delay(100);
}

//////////////////////////////// SUAVIZADO /////////////////////////////////////////////////

/////////////MEDIANA 
void mediana (double *se_in, double *salida_senial, int se_tamano, int filter){
  int i,j,l,k,med;
  double filtrado[filter];
  for(l=0;l<se_tamano;l++){
    for(k=0;k<filter;k++){
      filtrado[k]=se_in[l+k];
    }
    for(i=0;i<(filter-2);i++){
      for(j=i+1;j<filter-1-i;j++){
        if(filtrado[j]<filtrado[i]){
          med=filtrado[j];
          filtrado[j]=filtrado[i];
          filtrado[i]=med;
        }
      }
    }
   salida_senial[l]=filtrado[1];
  }
}


//////////////////////////RELACION SENAL A RUIDO ///////////////////////////////////////////

void SNRsensor(){
  double snr[tamano_se];
  double snr2[tamano_se];
  for(int i=0;i<tamano_se;i++){
    snr[i]=pow(flex_sensor[i],2);
    snr2[i]=pow((flex_sensor[i]-salida_senial[i]),2);
    SNR[i]=10*log(snr[i]/snr2[i]);
  }
}

/////////////////////////GRAFICAR EL RESULTADO /////////////////////////////////////////////

void plot_senial(void){       //el segundo void no necesita ningun parametro de entrada
  int i;
  for(i=0;i<tamano_se;i++){
    Serial.print(flex_sensor[i]+600);
    Serial.print(",");
    Serial.print(salida_senial[i]+10);
    Serial.print(",");
    Serial.println(SNR[i]-400);
    delay(5);
  }
}
