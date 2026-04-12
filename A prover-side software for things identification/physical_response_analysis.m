clc
clear all
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Parámetros principales:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
n_med_totales = 200;
n_carpetas = 7;

%tam_memoria=29665; %Bytes, es el inicial
%tam_memoria=81921;%Bytes, es el inicial
tam_memoria=25593; %Bytes, es el inicial

%n_bits_respuesta_PUF = 25593*8;
n_bits_respuesta_PUF = 768;

n_respuestas_PUF = floor(tam_memoria*8/n_bits_respuesta_PUF);
tam_memoria = n_respuestas_PUF*n_bits_respuesta_PUF/8;%Es el que se va a usar

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Otros parámetros:
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ruta_ficheros = 'Measurements_ESP32\';

bits_por_palabra=8;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 0-Se realiza una lectura de las medidas.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
[medidas]= lee_medidas(n_med_totales, n_carpetas, ruta_ficheros, tam_memoria, bits_por_palabra);
 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2-Se crea una máscara con las primeras n_med_mascara medidas.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Re-organización respuestas PUF
mascara_id_reorg = reshape_to_resp_PUF(medidas,n_carpetas,n_med_totales,n_respuestas_PUF,n_bits_respuesta_PUF);
%mascara_id_reorg = not(mascara_id_reorg);

% -- Cálculo intra Hamming distance --
distHD_intra = zeros(n_carpetas, n_med_totales*(n_med_totales-1)*n_respuestas_PUF/2 );
av_HD_intra = zeros(1, n_carpetas);

for i=1:n_carpetas
    [distHD_intra(i,:), av_HD_intra(i)] = distanciaHamming_average( squeeze(mascara_id_reorg(i,:,:,:)) ,n_med_totales ,n_respuestas_PUF);
end
av_FHD_intra = av_HD_intra / n_bits_respuesta_PUF;
distFHD_intra = distHD_intra(i,:) / n_bits_respuesta_PUF;

% -- Cálculo inter Hamming distance --

av_HD_inter_vec = zeros(1, n_med_totales);
distHD_inter_vec = [];

for i=1:n_med_totales
	[distHD_inter, av_HD_inter] = distanciaHamming_average( squeeze(mascara_id_reorg(:,i,:,:)), n_carpetas, n_respuestas_PUF );
	av_HD_inter_vec(i) = av_HD_inter;
	size_distHD_inter = size(distHD_inter,2);
	distHD_inter_vec(end+1:end+size_distHD_inter) = distHD_inter;
end
av_HD_inter_total = mean(av_HD_inter_vec);
% escalado
av_FHD_inter = av_HD_inter_total / n_bits_respuesta_PUF;
distFHD_inter = distHD_inter_vec / n_bits_respuesta_PUF;

[distFHD_inter2, av_FHD_inter2] = distanciaHamming_average( squeeze(mascara_id_reorg(:,1,:,:)), n_carpetas, n_respuestas_PUF ); %Uso primera medida de cada placa

% Búsqueda de valor val
HW_vec = [];
for placa=1:n_carpetas
    for medida=1:n_med_totales
        for respuesta=1:n_respuestas_PUF
            HW_vec(end+1) = sum(mascara_id_reorg(placa,medida,respuesta,:));
        end
    end
end
%val = max(HW_vec);
val = mean(HW_vec);

%(min(distH_inter) - max(max(distH_intra,[],2)))/n_bits_respuesta_PUF
av_FHD_inter
av_av_FHD_intra = mean( av_FHD_intra )
unif = val / n_bits_respuesta_PUF
