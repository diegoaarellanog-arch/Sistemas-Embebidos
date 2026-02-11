clc;
l1 = 7;
l2 = 7;
l3 = 7;

L1 = Revolute('d', l1, 'a', 0, 'alpha', -pi/2);
L2 = Revolute('d', 0, 'a', l2, 'alpha', 0, 'offset', 0);
L3 = Revolute('d', 0, 'a', l3, 'alpha', 0);
%, 'qlim', [0, 7]

bot = SerialLink([L1 L2 L3]);

ejes = [-20 20 -20 20 0 25];
bot.plot([0 0 0], 'workspace', ejes, 'noname');