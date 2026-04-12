% Cálculo BSR (Bit Success Rate). Uno por placa
% medidas ( medida, respuestaPUF, bit )
function BSR = BSR(medidas, num_medidas, num_respuestas_PUF, num_bits_respuesta_PUF)

    k = num_medidas;
    BSR_vec = [];

    for i=1:(k-1)
        resp_i = squeeze(medidas(i,:,:));
        for j=(i+1):k
            resp_j = squeeze(medidas(j,:,:));
            BSR_vec(end+1 : end+num_respuestas_PUF) = sum(and(resp_i, resp_j),2);
        end

    end

    BSR = sum(BSR_vec,2);
    BSR = BSR / (k*(k-1)*num_respuestas_PUF*num_bits_respuesta_PUF/2)
    
end