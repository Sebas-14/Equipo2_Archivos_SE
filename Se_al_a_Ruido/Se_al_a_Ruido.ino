/*--------------------Universidad Tecnica del Norte-----------------
 * ----------Facultad de Ingenieria en Ciencias Aplicadas----------
 * -------------Carrera de Telecomunicaciones------------
 * --------------------Sistemas Embebidos--------------
 * 
 * Integrantes: Carrion Andres, Donoso Fabricio, Quelal Rony
 * 
 */




#include "datos.h"
int test[] = {50,30,20,35,25};



void setup() {
  Serial.begin(9600);
  float mean = calc_mean(ecg, 600);
  float stdrDeviation = calc_stdrDeviation(ecg, 600);
  float snr = mean / stdrDeviation;
  Serial.println("Signal To Noise Ratio : " + String(snr));
}

void loop() {
}

float calc_mean(int vector[], int n) {
  int suma = 0;
  for (int i = 0; i < n; i++) {
    suma += vector[i];
  }
  return suma / n;
}


float calc_stdrDeviation(int vector[], int n) {
  float promedio = calc_mean(vector, n);
  float sumatoria = 0;
  for (int i = 0; i < n; i++) {
    sumatoria += pow(vector[i] - promedio, 2);
  }
//  Serial.println("Suma:" + String(sumatoria));
  return sqrt(sumatoria / (n - 1));
}
