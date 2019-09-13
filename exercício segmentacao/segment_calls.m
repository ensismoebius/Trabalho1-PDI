img_data= imread('D:/Hiago/Acadêmico/PÓS GRADUAÇÃO/Disciplinas/2º SEMESTRE - 2019/Processamento de Imagens Digitais/Trabalhos/MatLab - Transformada/imagem_base.jpg')
img_data= imresize(img_data, [256, 256]); %resizing
figure(1); imshow(img_data); title('Imagem Original');
img_data = rgb2gray(img_data); 

%generating image with gray squares------------------------------------------------------------------------------
    img_sq= uint8(zeros(256:256));
    color= 100; x=1; y=1;
    for i=1:4
        for j=1:4
            img_sq(x:x+63, y:y+63)= color;
            y= y+64; color= color+10;
        end
        x= x+64; y=1;
    end
    figure(2); imshow(img_sq); title('Imagem Original ');
%----------------------------------------------------------------------------------------------------------------


%calls for methods of segmentation-------------------------------------------------------------------------------
    IMG_OTSU= segment_img(img_data, 'otsu');
    figure(3); imshow(IMG_OTSU); title('Imagem Segmentada por Otsu');

    IMG_WAT_NO_MARKERS= segment_img(img_data, 'watershed_no_markers');
    figure(4); imshow(IMG_WAT_NO_MARKERS, []); title('Imagem Segmentada por Watershed sem Marcadores');

    IMG_WAT_AUT_MARKERS= segment_img(img_data, 'watershed_autom_markers');
    figure(5); imshow(IMG_WAT_AUT_MARKERS); title('Imagem Segmentada por Watershed com Marcadores');
%-----------------------------------------------------------------------------------------------------------------


%morphologic operations after segmentation------------------------------------------------------------------------
    %morphological filter = opening + closing
    ES= strel('square', 3);
    IMG_FILTERED= imopen(IMG_OTSU, ES);
    IMG_FILTERED= imclose(IMG_FILTERED, ES);
    figure(7); imshow(IMG_FILTERED, []); title('Imagem após Filtro Morfológico (A+F)');
%-----------------------------------------------------------------------------------------------------------------