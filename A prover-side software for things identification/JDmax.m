% Continuación carga_medidas

N = n_bits_respuesta_BPUF;
etaG = 10^-6;

% Cálculo BSR para cada placa
BSRs = zeros(1,n_carpetas);
for i=1:n_carpetas
    BSRs(i) = BSR( squeeze(mascara_id_reorg(i,:,:,:)), n_medidas_BPUF, n_respuestas_BPUF, n_bits_respuesta_BPUF );
end

% Se encuentra s_min para cada placa
s_mins = zeros(1, n_carpetas);

for placa=1:n_carpetas
    p_sG = BSRs(placa);
    for s_min=1:8000
        %disp(s_min)
        P_G = binocdf(s_min-1, N, p_sG);
        if P_G > etaG
            s_mins(placa) = s_min;
            break
        end
    end
end

% El BER de cada placa es su average intra JD
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

JD_max = 1 / (1 + ( min(s_mins) / max(e_maxs) ))
min(s_mins)
max(e_maxs)