import cv2
import requests
import numpy as np
from ultralytics import YOLO
import time

# Cargar modelo YOLO
model = YOLO("C:/Users/VICTUS/Aleutp/Documents/SuperPy/runs/detect/train16/weights/best.pt")

# URL de captura de imagen (NO /stream, sino /jpg)
url = "http://192.168.137.202/capture"  # O usa /jpg según cómo lo configuraste

while True:
    try:
        # Tomar imagen JPEG desde el ESP32
        response = requests.get(url, timeout=1)
        img_array = np.frombuffer(response.content, dtype=np.uint8)
        frame = cv2.imdecode(img_array, cv2.IMREAD_COLOR)

        if frame is not None:
            # Procesar con YOLO
            results = model.predict(source=frame, conf=0.8, verbose=False)
            annotated = results[0].plot()

            # Mostrar resultados
            cv2.imshow("YOLOv8 - ESP32-CAM", annotated)

        # Salir con 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    except Exception as e:
        print(f"Error al capturar frame: {e}")
        time.sleep(0.5)

cv2.destroyAllWindows()
