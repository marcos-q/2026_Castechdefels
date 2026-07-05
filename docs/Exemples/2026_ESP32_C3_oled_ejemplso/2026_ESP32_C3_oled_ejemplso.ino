#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- CONFIGURACIÓN HARDWARE ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_SDA 3 // Pines para ESP32-C3 SuperMini
#define PIN_SCL 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Wire.begin(PIN_SDA, PIN_SCL); 

  // Iniciar pantalla
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Fallo al iniciar OLED"));
    for(;;);
  }

  display.setRotation(0); // Ajusta según cómo tengas montada la pantalla
}

void loop() {
  demoTamanos();
  delay(3000);

  demoTextoInvertido();
  delay(3000);

  demoAlineacionYVariables();
  delay(3000);

  demoMaquinaEscribir("Hola, humano. Soy tu ESP32 y estoy vivo...");
  delay(3000);

  demoScrollHardware();
  delay(4000); // Damos tiempo a ver el scroll
}

// =========================================================
// DEMO 1: Tamaños y Salto de línea automático (Wrap)
// =========================================================
void demoTamanos() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  // Tamaño 1: Ideal para mucha información (ej. logs, sensores)
  display.setTextSize(1);
  display.println("Tamano 1: Peque\xA4o"); // \xA4 es la 'ñ' en algunas fuentes
  
  // Tamaño 2: Ideal para títulos o lecturas principales
  display.setTextSize(2);
  display.println("Tamano 2");
  
  // Salto de línea automático activado (por defecto lo está)
  display.setTextSize(1);
  display.setTextWrap(true); 
  display.println("El texto largo salta de linea automaticamente para no perderse.");

  display.display();
}

// =========================================================
// DEMO 2: Texto Invertido (Ideal para menús de selección)
// =========================================================
void demoTextoInvertido() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 10);
  
  // Texto normal
  display.setTextColor(WHITE);
  display.println(" NORMAL ");
  
  display.setCursor(10, 35);
  // Texto invertido (Letras negras sobre fondo blanco)
  // Sintaxis: setTextColor(ColorTexto, ColorFondo)
  display.setTextColor(BLACK, WHITE); 
  display.println(" SELECCIONADO ");
  
  display.display();
}

// =========================================================
// DEMO 3: Formateo de Variables (Ideal para Dashboards)
// =========================================================
void demoAlineacionYVariables() {
  display.clearDisplay();
  
  // Simulamos datos de sensores
  float temperatura = 24.5;
  int bateria = 85;

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Etiqueta
  display.setCursor(0, 10);
  display.print("Temp: ");
  // Dato en grande
  display.setTextSize(2);
  display.print(temperatura, 1); // 1 decimal
  display.setTextSize(1);
  display.print(" C");

  // Barra separadora
  display.drawFastHLine(0, 32, 128, WHITE);

  // Etiqueta 2
  display.setCursor(0, 45);
  display.print("Bateria: ");
  
  // Dibujamos una pequeña "pila" y mostramos el porcentaje
  display.drawRect(60, 43, 30, 12, WHITE); // Contorno
  display.fillRect(62, 45, 20, 8, WHITE);  // Relleno simulado
  display.setCursor(95, 45);
  display.print(bateria); display.print("%");

  display.display();
}

// =========================================================
// DEMO 4: Efecto "Máquina de escribir" (Ideal para robots)
// =========================================================
void demoMaquinaEscribir(String texto) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  // Imprimimos letra por letra con un pequeño retardo
  for(int i = 0; i < texto.length(); i++) {
    display.print(texto[i]);
    display.display(); // Actualizamos la pantalla en cada letra
    delay(50);         // Velocidad de escritura
  }
}

// =========================================================
// DEMO 5: Scroll por Hardware (Animaciones sin consumir CPU)
// =========================================================
void demoScrollHardware() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  display.print("PELIGRO!");
  display.display();
  
  // El scroll lo hace el propio chip de la pantalla, el ESP32 no hace nada
  // Desplaza desde la página (fila) 3 a la 4
  display.startscrollright(0x03, 0x04); 
  
  delay(3000); // Dejamos que haga scroll un rato
  
  display.stopscroll(); // Importante detenerlo antes de escribir otra cosa
}