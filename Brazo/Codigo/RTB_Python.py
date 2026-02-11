### Código para el control de un brazo robótico utilizando la biblioteca Robotics Toolbox en Python
import roboticstoolbox as rtb
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d as mplot3d

# Crear el robot utilizando el modelo de Denavit-Hartenberg

# ---------------------------------------- Definicion del manipulador ----------------------------------------
# Definir los parámetros de los eslabones del robot
l1 = 7;
l2 = 7;
l3 = 7;

# Crear los eslabones utilizando la convención de Denavit-Hartenberg
L1 = rtb.RevoluteDH(d = l1, a = 0, alpha = -np.pi/2);
L2 = rtb.RevoluteDH(d = 0, a = l2, alpha = 0, offset = 0);
L3 = rtb.RevoluteDH(d = 0, a = l3, alpha = 0); # Nota: qlim delimita el rango de movimiento de cada articulación

# Crear el robot utilizando la biblioteca Robotics Toolbox
bot = rtb.SerialLink([L1, L2, L3]);

# ---------------------------------------- Visualización del robot ----------------------------------------
#bot.teach([0, 0, 0], limits = [-1, 1, -1, 1, 0, 1]) # Mostrar la configuración del robot
# 'teach=False' evita que se creen los sliders que dan el error
ejes = [-30, 30, -30, 30, 0, 30]

bot.plot([0, 0, 0], limits = ejes, block = True)

# Título para confirmar la rotación
print("Visualizando robot... El eslabón 2 tiene un offset de 90° (pi/2)")

# Mantener la ventana abierta
plt.show()