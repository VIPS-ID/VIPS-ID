function [mascara_id]= lee_medidas_BUF(n_med_totales, n_carpetas, ruta_ficheros, tam_memoria, bits_por_palabra, n_medidas_BPUF, R_BPUF)
    
    medidas = zeros(n_med_totales,tam_memoria*bits_por_palabra);
    mascara_id=zeros(n_carpetas,n_medidas_BPUF,tam_memoria*bits_por_palabra);

    for folder=1:n_carpetas
        for k=1:n_med_totales
            ruta_file=[ruta_ficheros,'Wipy_',int2str(folder),'\',int2str(k),'.txt'];
            medidaDec=load(ruta_file);
            medidaBin=dec2bin(medidaDec);
            medidaLog=logical(medidaBin'-'0')';
            medida=medidaLog(1:tam_memoria,:);%(81921:(81921+tam_memoria-1),:);
            medida_1dim=reshape(medida',1,tam_memoria*bits_por_palabra);
            medidas(k,:)=medida_1dim;
            
            disp('medida PUF')
            disp(folder)
            disp(k)
        end
        % aplico calcula_mascara
        for x=1:n_medidas_BPUF
            % R medidas se usan para la máscara
            mascara_id(folder,x,:)=calcula_mascara(medidas,R_BPUF,x);
            
            disp('medida BUF')
            disp(folder)
            disp(x)
        end
    end
end