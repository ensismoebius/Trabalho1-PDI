function S= segment_img(input_img, seg_type)

    %img received must be in gray scale
    switch seg_type
        case 'otsu' %na imagem quadrada se usar o gradiente consigo segmentar bem - real�a bordas apenas
            S= imbinarize(input_img); %as default IMBINZARIZE uses the Otsu�s Method for segmentation, if I want to know
            %the value of the treshold I can use the function GRAYTRESH
            [T, E_T]= graythresh(input_img);
            disp('Limiar: ');
            disp(T*255);
            disp('Efici�ncia do Limiar: ');
            disp(E_T);
            
        case 'watershed_no_markers' %always related to the gradient, because min regional points 'hit' with the foreground objects
            S= watershed(imgradient(input_img)); %here I have a oversegmentation (almost all points are marked as valleys, including possible noises)
            
        case 'watershed_autom_markers'
            %example of DIP - Gonzalez
            %1 - calcular o gradiente da img -- pontos m�nimos tendem a ser fundos de objeto e fundo, o watershed direto aqui
            %tende a super segmenta��o devido a ruidos, etc
                img_gradiente= imgradient(input_img);
            %2 - pegar regi�es m�nimas, tende a pegar realmente s� fundos de objetos e fundo, tirando um pouco de ru�do
            %internal_markers= imregionalmin(img_gradiente);
                internal_markers= imextendedmin(input_img, 2); %pega pontos minimos abaixo de um determinado limiar - deixa mais limpo ainda
                img_with_deep_rm_= input_img;    img_with_deep_rm(internal_markers)= 175; %sobrep�e pontos de m�nimo na img original
            %3 - pegar regi�es m�nimas externas -> fa�o a watershed da distancia dos markers internos
                external_markers_aux= watershed(bwdist(internal_markers)); %n�o vai deixar internal_markers se misturarem, criando barreiras
                %onde s�o pontos m�nimos de fundo == external markers
                external_markers= external_markers_aux==0;
            %4- modificar a imagem gradiente para ter como pontos m�nimos apenas os marcadores
                img_gradiente = imimposemin(img_gradiente, internal_markers | external_markers);
            %5 - agora posso calcular a watershed tendo os marcadores como pontos minimos na imagem gradiente
                W= watershed(img_gradiente);
                result= input_img;   result(W==0)= 255; %sobrep�e as linhas de watershed como branco na imagem original
                S= result;
            
        otherwise
            error('M�todo n�o dispon�vel na biblioteca para segmenta��o!');
    end

end