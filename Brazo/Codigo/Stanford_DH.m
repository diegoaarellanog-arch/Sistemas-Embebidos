% Script para representación gráfica del brazo robótico utilizando los parámetros de Denavit-Hartenberg (DH) de Stanford.
clc
clear

q = [0*pi/180 0*pi/180 2 0*pi/180 0*pi/180 0*pi/180]; % Vector de ángulos articulares (en radianes) y desplazamientos (en unidades de longitud)
d2 = 2.5; % Desplazamiento del segundo eslabón
d4 = 3; % Desplazamiento del cuarto eslabón
d6 = 3; % Desplazamiento del sexto eslabón

figure(1)
clf
hold on

H00 = eye(4); % Matriz de transformación homogénea inicial (identidad)
H01 = DH(q(1), 0, 0, -pi/2); % Transformación del primer eslabón
H12 = DH(q(2), d2, 0, pi/2); % Transformación del segundo eslabón
H23 = DH(0, q(3), 0, 0); % Transformación del tercer eslabón (desplazamiento fijo)
H34 = DH(q(4), d4, 0, -pi/2); % Transformación del cuarto eslabón
H45 = DH(q(5), 0, 0, pi/2); % Transformación del quinto eslabón
H56 = DH(q(6), d6, 0, 0); % Transformación del sexto eslabón

H02 = H00 * H01 * H12; % Transformación del segundo eslabón respecto a la base
H03 = H02 * H23; % Transformación del tercer eslabón respecto a la base
H04 = H03 * H34; % Transformación del cuarto eslabón respecto a la base 
H05 = H04 * H45; % Transformación del quinto eslabón respecto a la base
H06 = H05 * H56; % Transformación del sexto eslabón respecto a la base

plot3([H00(1,4) H01(1,4)], [H00(2,4) H01(2,4)], [H00(3,4) H01(3,4)], 'r', 'LineWidth', 2); % Dibuja el primer eslabón
plot3([H01(1,4) H02(1,4)], [H01(2,4) H02(2,4)], [H01(3,4) H02(3,4)], 'g', 'LineWidth', 2); % Dibuja el segundo eslabón
plot3([H02(1,4) H03(1,4)], [H02(2,4) H03(2,4)], [H02(3,4) H03(3,4)], 'b', 'LineWidth', 2); % Dibuja el tercer eslabón
plot3([H03(1,4) H04(1,4)], [H03(2,4) H04(2,4)], [H03(3,4) H04(3,4)], 'c', 'LineWidth', 2); % Dibuja el cuarto eslabón
plot3([H04(1,4) H05(1,4)], [H04(2,4) H05(2,4)], [H04(3,4) H05(3,4)], 'm', 'LineWidth', 2); % Dibuja el quinto eslabón
plot3([H05(1,4) H06(1,4)], [H05(2,4) H06(2,4)], [H05(3,4) H06(3,4)], 'k', 'LineWidth', 2); % Dibuja el sexto eslabón
xlabel('X');
ylabel('Y');
zlabel('Z');
title('Brazo Robótico de Stanford');
axis equal
grid on
