syms theta1 theta2 theta4 theta5 theta6 d2 d3 d4 d6
PI = sym('pi')
T01 = DH(theta1, 0, 0, -PI/2)
T12 = DH(theta2, d2, 0, PI/2)
T23 = DH(0, d3, 0, 0)
T34 = DH(theta4, d4, 0, -PI/2)
T45 = DH(theta5, 0, 0, PI/2)
T56 = DH(theta6, d6, 0, 0)
T06 = simplify(T01*T12*T23*T34*T45*T56)