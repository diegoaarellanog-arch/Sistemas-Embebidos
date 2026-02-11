import roboticstoolbox as rtb
import numpy as np
import matplotlib.pyplot as plt

# 1. DEFINICIÓN DEL ROBOT
L1 = rtb.DHLink(d=11, a=0, alpha=np.pi/2)
L2 = rtb.DHLink(d=0, a=12, alpha=0, offset=np.pi/2) # Tu rotación de 90°
L3 = rtb.DHLink(d=0, a=10, alpha=0)
bot = rtb.DHRobot([L1, L2, L3], name='Robot_Diego')

# 2. CONFIGURACIÓN GRÁFICA
ejes = [-40, 40, -40, 40, -40, 40]
env = bot.plot([0, 0, 0], limits=ejes)
plt.ion() 

def actualizar(q1, q2, q3, dt=0.05):
    bot.q = [np.radians(q1), np.radians(q2), np.radians(q3)]
    env.step(dt) 
    print(f"Tiempo: {env.sim_time:.2f}s | Q: [{q1},{q2},{q3}]", end='\r')

# 3. BUCLE DE SIMULACIÓN (CON EL BLOQUE EXCEPT CORREGIDO)
try:
    print("Simulando... Cierra la ventana para terminar.")
    while env.sim_time < 20.0:
        # Movimiento de ejemplo
        ang = 45 * np.sin(env.sim_time * 2)
        actualizar(ang, 0, 0, 0.05)
        plt.pause(0.05)
except Exception as e:
    print(f"\nSimulación finalizada o interrumpida: {e}")
finally:
    print("\nProceso terminado.")
    plt.show(block=True)