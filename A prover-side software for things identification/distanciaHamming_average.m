% medidas ( n, respuestaPUF, bit respuesta )
function [HD_vec, av_HD] = distanciaHamming_average(medidas, k, num_respuestas_PUF)

    HD_vec = [];

    for i=1:(k-1)
        resp_i = squeeze(medidas(i,:,:));
        for j=(i+1):k
            resp_j = squeeze(medidas(j,:,:));
            HD_vec(end+1:end+num_respuestas_PUF) = distanciaHamming(resp_i, resp_j)';
        end
    end
    
    av_HD = sum(HD_vec,2);
    % average Hamming distance
    av_HD = av_HD / (k*(k-1)*num_respuestas_PUF/2)

end