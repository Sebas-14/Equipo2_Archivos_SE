/*--------------------Universidad Tecnica del Norte-----------------
 * ----------Facultad de Ingenieria en Ciencias Aplicadas----------
 * -------------Carrera de Telecomunicaciones------------
 * --------------------Sistemas Embebidos--------------
 * 
 * Integrantes: Carrion Andres, Donoso Fabricio, Quelal Rony
 * 
 */



#define window_size  13 //Definimos el tamaño de la ventana
int window[window_size]; //Se crea un vector de el tamaño definido
int index = 0; //Variable auxiliar
int suma = 0; //Variable auxiliar
int promedio; //Variable auxiliar


void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < window_size; i++) { //incializar el vector
    window[i] = 0;//llenado del vector de ceros
  }
}

void loop() {
  suma -= window[index]; // se resta la suma menos la ultima posicion 
  window[index] = analogRead(A0);//En la posicion 0 se lee el valor del puerto analogico
  Serial.print(window[index]); //Mostramos el valor 
  suma += window[index]; //Se añade el valor leido
  index++;
  if (index >= window_size) { // Se mueve a la siguiente posicion
    index = 0;
  }
  promedio = suma / window_size;//Se realiza el promedio suma/13
  Serial.print(",");
  Serial.println(String("promedio señal ingresada: ")+String(promedio)); //Se imprime el valor promedio 
}
