from ultralytics import YOLO
import torch 


model = YOLO("C:/Users/VICTUS/OneDriveUniversidadTecnologicadelPeru/Documents/SuperPy/runs/detect/train16/weights/best.pt")
#preds = model("C:/Users/VICTUS/OneDriveUniversidadTecnologicadelPeru/Documents/SuperPy/dataset_cacao/test/images/Sana61_jpg.rf.ad93bd8d6566d7bf61941a6b257ca7aa.jpg")
#preds = model("C:/Users/VICTUS/OneDriveUniversidadTecnologicadelPeru/Documents/SuperPy/dataset_cacao/test/images")
#preds = model("C:/Users/VICTUS/OneDriveUniversidadTecnologicadelPeru/Documents/SuperPy/dataset_cacao/test/images/Fito_159_jpg.rf.7a20945b13e41798c5e16306988d3546.jpg")
preds[0].show()