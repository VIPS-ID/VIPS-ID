function [distJ] = distanciaJaccard_mod(vec1,vec2,val)
% Espera vectores de la forma vec( respuestasPUF, bitsPUF )
% La salida es un vector con respuestasPUF valores
    distH = distanciaHamming(vec1,vec2);
    distJ = distH ./ (distH + (2*val - distH) ./ 2);
end