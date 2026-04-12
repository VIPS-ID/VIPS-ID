% Calcula HD_max respuesta PUF

N = n_bits_respuesta_BPUF;
etaG = 10^-6;

% El BER de cada placa es su average intra FHD
% Se encuentra e_max para cada placa
e_maxs = zeros(1,n_carpetas);
for placa=1:n_carpetas
    p_eG = av_FHD_intra(placa);
    for e_max=1:1000
        P_G = 1 - binocdf(e_max, N, p_eG);
        if P_G < etaG
            e_maxs(placa) = e_max;
            break
        end
    end
end

HD_max_PUF = max(e_maxs)
P_err = binocdf(HD_max, N, av_FHD_inter)
log2(1/P_err)