function [medidas]= lee_medidas(n_med_totales, n_carpetas, ruta_ficheros, tam_memoria, bits_por_palabra)
    
    medidas = zeros(n_carpetas,n_med_totales,tam_memoria*bits_por_palabra);

    for folder=1:n_carpetas
        for k=1:n_med_totales
            ruta_file=[ruta_ficheros,'Wipy_',int2str(folder),'\',int2str(k),'.txt'];
            medidaDec=load(ruta_file);
            medidaBin=dec2bin(medidaDec);
            medidaLog=logical(medidaBin'-'0')';
            medida=medidaLog(1:tam_memoria,:);%(81921:(81921+tam_memoria-1),:);
            medida_1dim=reshape(medida',1,tam_memoria*bits_por_palabra);
            
            medidas(folder,k,:)=medida_1dim;
            disp(folder)
            disp(k)
        end
    end
end