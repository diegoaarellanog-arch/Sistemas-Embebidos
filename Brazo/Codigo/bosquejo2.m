% Ejemplo: Robot de 2 eslabones (RR)
L1 = Link('d', 0, 'a', 1, 'alpha', 0);
L2 = Link('d', 0, 'a', 1, 'alpha', 0);
robot = SerialLink([L1 L2], 'name', 'MiRobot');
T = robot.fkine([pi/4, pi/2])
plot(robot.fkine([pi/4, pi/2]), 'workspace', [-2 2 -2 2 -0.5 2], 'scale', 0.5);