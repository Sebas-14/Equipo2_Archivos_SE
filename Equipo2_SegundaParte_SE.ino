/*--------------------Universidad Tecnica del Norte-----------------
 * ----------Facultad de Ingenieria en Ciencias Aplicadas----------
 * -------------Carrera de Telecomunicaciones------------
 * --------------------Sistemas Embebidos--------------
 * 
 * Integrantes: Carrion Andres, Donoso Fabricio, Quelal Rony
 * 
 */

float kernel[]={0.05,0.24,0.4,0.24,0.05};
float Signal [] = {
1007,975,971,961,954,944,926,931,936,931,935,923,918,912,907,911,914,913,917,898
,880,849,837,836,810,793,779,740,726,702,690,689,644,699,703,697,704,692,686,690,
678,675,644,630,640,636,652,658,657,668,669,664,675,665,666,659,660,671,661,660,
659,652,659,654,652,671,670,688,700,707,728,724,731,743,733,749,744,736,745,730,
736,732,729,743,734,726,726,716,722,712,701,709,690,686,681,668,675,665,658,668,
};

int N=90, Nk=5;
float den=0, zj=0;
double h,f,m;
double c[90];

void setup()
{
Serial.begin(9600); //Inicio de Comunicación serial
}

void loop(){
  den=0;
  for (int i = 0; i < Nk; i++){
    den=den+kernel[i];
  }
  
for (int i = 0; i < N-Nk; i++){


   Serial.println(String("Señal Original: ")+String(Signal[i+2]));//Impresion de la señal original
//   c[i]=0;
  }

 SNR();
}

void SNR(){                             //Método de SNR

//Promedio señal original v1
  float sum=0;                          //ciclos recorre el numero de datos d ela señal
  for(int i=0;i<90;i++){                    
      sum = sum + Signal[i];            //guarda los valores obtenidos
    }
     double promedio=sum/90;            //divide para el numero de datos de la señal
    double v1=((promedio*5)/1023);
    Serial.println(String("Valor voltaje Señal: ")+String(v1));   //Imprime de forma serial el valor obtenido
    Serial.print("");
    
//Promedio señal Suavizada (v2) metodo de Gauss
     double sum2=0;
  for(int i=0;i<90;i++){               
      sum2 = sum2 + Signal[i+1];
    }
   double promedio2=sum2/90;                               //divide par ael numero de datos de la señal
    float v2=(promedio2*5)/1023;
    Serial.println(String("Valor en voltaje del filtro: ")+String(v2)); //Imprime de forma serial el valor obtenido
    Serial.print("");

 //Metrica SNR m=20*log(v2/v1)
     double metrica=20*log(v2/v1);
    Serial.println(String("Valor metrica snr en dBs: ")+String(metrica)); //Imprime el valor obtenid entre con relación a lo anteriores resultados
    Serial.print("");
    
  }
  
