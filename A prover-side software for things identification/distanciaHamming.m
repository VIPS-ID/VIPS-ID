function [distH] = distanciaHamming(vec1, vec2)

    distH = sum(xor(vec1,vec2), 2);

end