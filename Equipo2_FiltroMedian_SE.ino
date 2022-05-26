/*--------------------Universidad Tecnica del Norte-----------------
 * ----------Facultad de Ingenieria en Ciencias Aplicadas----------
 * -------------Carrera de Telecomunicaciones------------
 * --------------------Sistemas Embebidos--------------
 * 
 * Integrantes: Carrion Andres, Donoso Fabricio, Quelal Rony
 * 
 */


 //----------------------------------------Filtro mediano
#define window_size 11 //Se define el tamaño de la ventana
int window[window_size]; //Se crea un vector de ese tamaño
int index = 0; //aux
int suma = 0; //aux

int medianValue;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < window_size; i++) { //lenar de ceros el vector
  }

}

void loop() {
    
    window[index] = analogRead(A0); //Leemos el valor del puerto analogico
    Serial.print(window[index]); //Mostramos en el terminal el valor leido
  
    index++; 
    if (index >= window_size) {
      index = 0;
    }
    medianValue = calcMedian(window, window_size); //Se realiza el filtrado
    Serial.print(",");
    Serial.println(String("Mediana: ")+(medianValue));//imprimimos el valor mediano
   
    delay(10);

}


int calcMedian(int vector[], int n) { //Ordenar el vector 
  for (int i = 1; i < n; ++i) { //Se realiza el ordenamiento por burbuja
    float j = vector[i];
    int h;
    for (h = i - 1; (h >= 0) && (j < vector[h]); h--) {
      vector[h + 1] = vector[h];
    }
    vector[h + 1] = j;
  }

  return vector[window_size / 2]; //tomamos el valor central 

}

void printVector (int vector[], int n) {
  for (int i = 0; i < n; i++) {
    Serial.println(vector[i]);

  }

}
