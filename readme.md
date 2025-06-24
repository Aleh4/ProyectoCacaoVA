# Sistema de Detección de Plagas en Cacao mediante Visión Artificial

Este repositorio contiene la implementación de un sistema para la detección de plagas (Moniliasis y Phytophthora) en frutos de cacao, utilizando modelos de inteligencia artificial basados en YOLOv8. El sistema es de uso libre y de código abierto.

---

## Tabla de Contenidos

- [Requisitos del sistema](#requisitos-del-sistema)
- [Instalación](#instalación)
- [Ejecución con cámara local (PC)](#ejecución-con-cámara-local-pc)
- [Ejecución con ESP32-CAM](#ejecución-con-esp32-cam)
- [Créditos](#créditos)
- [Licencia](#licencia)

---

## Requisitos del sistema

- Python 3.8 o superior
- OpenCV, ultralytics y otras dependencias (ver `requirements.txt`)
- Archivo de pesos del modelo (`best.pt`)
- Cámara local o módulo ESP32-CAM

---

## Recomendación
    -Genera un entorno virtual para no crear conflicto con otros proyectos, ejecutando el siguiente código:
    python -m venv venv
    source venv/bin/activate  # Linux/Mac
    venv\Scripts\activate     # Windows
    pip install -r requirements.txt

---

## Instalación

1. Clona este repositorio:
   ```bash
   git clone https://github.com/Aleh4/ProyectoCacaoVA.git
   cd ProyectoCacaoVA
   ```
2. Instala las dependencias necesarias:
   ```bash
   pip install -r requirements.txt
   ```
3. Descarga el archivo de pesos `best.pt` y colócalo en la carpeta correspondiente (por ejemplo, `train16/`).

---

## Ejecución con cámara local (PC)

1. Abre y edita el archivo `PruebaDeVideoLocal.py`.
2. En la línea donde se carga el modelo, actualiza la ruta del archivo de pesos:
   ```python
   model = YOLO("ruta/completa/al/archivo/best.pt")
   ```
3. Ejecuta el script:
   ```bash
   python PruebaDeVideoLocal.py
   ```
   El sistema utilizará la cámara local y mostrará la detección de plagas en tiempo real.

---

## Ejecución con ESP32-CAM

1. Carga el script `CameraWebServer.ino` en tu ESP32-CAM utilizando Arduino IDE.  
   > **Nota:** Asegúrate de instalar la librería para ESP32.
2. Configura la red WiFi en el archivo:
   ```cpp
   const char *ssid = "TU_SSID";
   const char *password = "TU_PASSWORD";
   ```
3. Una vez cargado, la cámara tendrá una IP asignada en tu red local, por ejemplo:  
   `http://10.30.158.60:81/stream`
4. Abre `PruebaVideoEsp.py` y actualiza la variable `esp` con la dirección IP de tu cámara.
5. Ejecuta el script:
   ```bash
   python PruebaVideoEsp.py
   ```
   Ahora el sistema procesará el video transmitido desde la ESP32-CAM.

---

## Créditos

Desarrollado por Aleh4.  
Proyecto para la detección temprana de plagas Moniliasis y Phytophthora en cacao usando visión artificial.

---

## Licencia

Este proyecto es de acceso público y open source. Consulta el archivo [LICENSE](LICENSE) para más detalles.

---

```