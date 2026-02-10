function M = DH(theta, d, a, alpha)
    % Convertimos las rotaciones 3x3 a transformaciones 4x4
    Rz = r2t(rotz(theta)); 
    Rx = r2t(rotx(alpha));
    T = transl(a, 0, d); % Esta ya es 4x4
    
    % Ahora todas son 4x4 y se pueden multiplicar
    M = Rz * T * Rx;
end