% medidas ( n, respuestaPUF, bit respuesta )
function [JD_vec, av_JD] = distanciaJaccard_mod_average(medidas, k, num_respuestas_PUF, val)

    JD_vec = [];

    for i=1:(k-1)
        resp_i = squeeze(medidas(i,:,:));
        for j=(i+1):k
            resp_j = squeeze(medidas(j,:,:));
            JD_vec(end+1:end+num_respuestas_PUF) = distanciaJaccard_mod(resp_i, resp_j, val)';
        end
    end
    
    av_JD = sum(JD_vec,2);
    % average Jaccard distance
    av_JD = av_JD / (k*(k-1)*num_respuestas_PUF/2)

end