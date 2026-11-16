/*
  =============================================================================
  Descripción:
  Sistema de monitoreo de presencia autónomo con sensor PIR (HC-SR501).
  Al detectar intrusión, activa una sirena bitono (Buzzer Pasivo) y destellos 
  en el LED Rojo durante 5 SEGUNDOS exactos. Cumplido ese tiempo, el sistema 
  se apaga automáticamente y vuelve al estado seguro (LED Verde).
  =============================================================================
*/

// --- 1. DECLARACIÓN DE PINES Y CONSTANTES ---
const int PIN_PIR       = 2;  // Sensor de movimiento PIR
const int PIN_BUZZER    = 8;  // Pin para Buzzer Pasivo
const int PIN_LED_ROJO  = 12; // LED de Alarma
const int PIN_LED_VERDE = 13; // LED de Reposo

// --- 2. VARIABLES DE ESTADO Y TEMPORIZACIÓN ---
bool alarmaDisparada = false;

// Temporizador principal de la alarma (5 segundos)
unsigned long tiempoInicioAlarma = 0;
const unsigned long DURACION_ALARMA = 5000UL; // 5000 ms = 5 segundos

// Temporización de la sirena sin bloqueos (millis)
unsigned long ultimoCambioSirena = 0;
const unsigned long INTERVALO_SIRENA = 150; // Velocidad del bitono (ms)
bool alternarTono = false;

// Ventana de inmunidad tras apagar la alarma (evita re-disparo inmediato)
unsigned long tiempoDesarmado = 0;
const unsigned long TIEMPO_INMUNIDAD = 3000; // 3 segundos

// --- 3. FUNCIONES MODULARIZADAS ---

/**
 * Restablece la alarma al estado seguro (LED Verde ON, Buzzer OFF).
 */
void rearmarSistema() {
  alarmaDisparada = false;
  tiempoDesarmado = millis();
  noTone(PIN_BUZZER);
  digitalWrite(PIN_LED_VERDE, HIGH);
  digitalWrite(PIN_LED_ROJO, LOW);
  Serial.println("[ESTADO] Alarma finalizada. Monitoreando entorno...");
}

// --- 4. CONFIGURACIÓN INICIAL (SETUP) ---
void setup() {
  Serial.begin(9600);
  Serial.println("=== ALARMA AUTÓNOMA (5 SEGUNDOS) INICIALIZADA ===");

  pinMode(PIN_PIR, INPUT);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);

  rearmarSistema();
}

// --- 5. BUCLE PRINCIPAL (LOOP) ---
void loop() {
  int lecturaPir = digitalRead(PIN_PIR);
  unsigned long tiempoActual = millis();

  // A. Detección por Sensor PIR con inmunidad temporal
  if (lecturaPir == HIGH && !alarmaDisparada && (tiempoActual - tiempoDesarmado > TIEMPO_INMUNIDAD)) {
    alarmaDisparada = true;
    tiempoInicioAlarma = tiempoActual; // Marca de tiempo inicial
    Serial.println("[ALERTA] Movimiento detectado. Alarma encendida por 5 segundos...");
  }

  // B. Control de Alarma Temporizada y Auto-Rearme Automático
  if (alarmaDisparada) {
    // 1. Verificación: ¿Transcurrieron los 5 segundos?
    if (tiempoActual - tiempoInicioAlarma >= DURACION_ALARMA) {
      rearmarSistema();
      Serial.println("[AUTO-REARME] Transcurrieron 5s. Sistema rearmado automáticamente.");
    } else {
      // 2. Sirena bitono y destellos sin congelar la placa (sin delay)
      digitalWrite(PIN_LED_VERDE, LOW);

      if (tiempoActual - ultimoCambioSirena >= INTERVALO_SIRENA) {
        ultimoCambioSirena = tiempoActual;
        alternarTono = !alternarTono;

        if (alternarTono) {
          tone(PIN_BUZZER, 800);
          digitalWrite(PIN_LED_ROJO, HIGH);
        } else {
          tone(PIN_BUZZER, 1200);
          digitalWrite(PIN_LED_ROJO, LOW);
        }
      }
    }
  } else {
    // Estado de Reposo Seguro
    digitalWrite(PIN_LED_VERDE, HIGH);
    digitalWrite(PIN_LED_ROJO, LOW);
    noTone(PIN_BUZZER);
  }
}
