# WatchOut

Proyecto correspondiente al **Segundo Parcial de Integración Tecnológica**.

## Descripción y Justificación del Proyecto

### Identificación del Problema
**WatchOut** es un sistema de alarma que se activa cuando se detecta movimiento cerca del dispositivo y envía la información de cada activación a un panel web. Está pensado para personas que necesitan saber si alguien o algo ingresó a la zona monitoreada y desean consultar ese registro desde un panel web.

### Objetivo del Proyecto
Utilizar un sensor de movimiento para encender un LED indicador al detectar presencia en la zona de cobertura, activar un buzzer como sonido de advertencia y enviar el registro de la alarma a un panel web.

### Justificación y Presupuesto
Una alternativa comercial en Mercado Libre tiene un costo de **26.000 ARS**, pero se limita únicamente a encender una alarma al detectar movimiento. El prototipo **WatchOut** representa una diferencia de **11.705 ARS** adicionales, incorporando como valor agregado un **panel web** para visualizar las veces que se activó la alarma.

| Componente | Costo (ARS) |
| :--- | :---: |
| Placa de desarrollo Arduino Uno | $10.000 |
| LED verde | $3.100 |
| LED rojo | $4.375 |
| Buzzer | $3.201 |
| Sensor de movimiento infrarrojo pasivo PIR | $3.223 |
| Resistencias | $3.319 |
| Protoboard | $3.800 |
| Cables macho-hembra | $3.158 |
| Cables macho-macho | $3.529 |
| **Total** | **$37.705** |

---

## Lista de Componentes (Hardware)

* Placa de desarrollo **Arduino Uno R3**
* Sensor de movimiento infrarrojo pasivo **PIR (HC-SR501)**
* **Buzzer pasivo (5V)**
* **LED indicador Rojo**
* **LED indicador Verde**
* **2 Resistencias de 220 Ω** (para limitar la corriente en los LEDs)
* **Protoboard**
* **Cables jumper** de conexión (macho-macho y macho-hembra)

---

## Simulación

La simulación operativa del prototipo con los componentes clave del hardware se encuentra disponible en Tinkercad:

* **Enlace a Tinkercad:** [WatchOut - Simulación](https://www.tinkercad.com/things/ieYBKg15wEK-watchout)

---

## Componentes Digitales y Documentación

Este repositorio contempla los siguientes entregables del proyecto:

* **Código Fuente (`.ino`):** Código documentado línea por línea o por bloques (declaración de variables y librerías, configuración en `setup()`, lógica principal en `loop()` y funciones personalizadas con parámetros).
* **Diagrama de Conexiones Físicas:** Esquema visual del conexionado de los componentes al sistema y registro del proceso de armado.
* **Diagrama de Flujo (Flowchart):** Representación de la lógica de programación principal, centrada en la función `loop()` y las estructuras de decisión.
