from ultralytics import YOLO
import cv2

# Cargar modelo YOLO personalizado
model = YOLO("C:/Users/VICTUS/OneDriveUniversidadTecnologicadelPeru/Documents/SuperPy/runs/detect/train16/weights/best.pt")

# Dirección IP del ESP32-CAM conectado a tu red local
esp = "http://10.30.158.60:81/stream"  # Asegúrate de que esta IP es la correcta http://10.30.158.60:81/stream

# Inicializar la cámara (0 es el índice por defecto)
cap = cv2.VideoCapture(esp)

# Verificar si la cámara se abrió correctamente
if not cap.isOpened():
    print("Error: No se pudo acceder a la cámara.")
    exit()

# Procesar en tiempo real
while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Aplicar el modelo al frame
    results = model.predict(source=frame, conf=0.80, verbose=False)

    # Dibujar las detecciones sobre el frame
    annotated_frame = results[0].plot()

    # Mostrar resultado
    cv2.imshow("Deteccion en tiempo real", annotated_frame)

    # Presiona 'q' para salir
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar recursos
cap.release()
cv2.destroyAllWindows()
