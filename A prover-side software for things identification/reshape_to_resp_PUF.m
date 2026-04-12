% medida ( placa, medida, bitPUF )
% medida ( placa, medida, respuestaPUF, bitPUF )

function [res] = reshape_to_resp_PUF(medidas,num_placas,num_medidas,num_respuestas_PUF,num_bits_PUF)

    res = zeros(num_placas,num_medidas,num_respuestas_PUF,num_bits_PUF); % num_placas x num_medidas x num_respuestas_PUF x num_bits_PUF

    for i=1:num_placas
        for j=1:num_medidas
            temp = squeeze(medidas(i,j,:,:));
            temp = reshape(temp,[num_bits_PUF,num_respuestas_PUF])';
            res(i,j,:,:) = temp;
            disp(i)
            disp(j)
        end
    end

end

