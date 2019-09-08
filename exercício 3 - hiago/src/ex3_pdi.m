img_data= imread('D:/Hiago/Acadêmico/PÓS GRADUAÇÃO/Disciplinas/2º SEMESTRE - 2019/Processamento de Imagens Digitais/Trabalhos/MatLab - Transformada/imagem_base.jpg')
img_data= imresize(img_data, [256, 256]); %resizing
figure(1); imshow(img_data); title('Imagem Original');

%-------------------------------------------------------------------------------cutting image into 4 halves
[rows, columns, numberOfColorChannels] = size(img_data);
img_upper_left = img_data(1:round(rows/2), 1:round(columns/2), :);
img_upper_right = img_data(1:round(rows/2), round(columns/2)+1:end, :);
img_lower_left = img_data(round(rows/2)+1:end, 1:round(columns/2), :);
img_lower_right = img_data(round(rows/2)+1:end, round(columns/2)+1:end, :);
%-------------------------------------------------------------------------------cutting image into 4 halves

%------------------------------------------------------------------------------saving the channels of colors
%ch1= img_data(:,:,1); ch2= img_data(:,:,2); ch3= img_data(:,:,3); 
%ch_upper_left_1= img_upper_left(:,:,1); ch_upper_left_2= img_upper_left(:,:,2); ch_upper_left_3= img_upper_left(:,:,3); %saving the channels of colors
%ch_upper_right_1= img_upper_right(:,:,1); ch_upper_right_2= img_upper_right(:,:,2); ch_upper_right_3= img_upper_right(:,:,3); %saving the channels of colors
%ch_lower_left_1= img_lower_left(:,:,1); ch_lower_left_2= img_lower_left(:,:,2); ch_lower_left_3= img_lower_left(:,:,3); %saving the channels of colors
%ch_lower_right_1= img_lower_right(:,:,1); ch_lower_right_2= img_lower_right(:,:,2); ch_lower_right_3= img_lower_right(:,:,3); %saving the channels of colors
%------------------------------------------------------------------------------saving the channels of colors

%---------------------------------------------------------------------converting everything from RGB to GRAY
img_data= rgb2gray(img_data);
img_upper_left = rgb2gray(img_upper_left);
img_upper_right = rgb2gray(img_upper_right);
img_lower_left = rgb2gray(img_lower_left);
img_lower_right = rgb2gray(img_lower_right);
figure(2); imshow(img_data); title('Imagem em Níveis de Cinza');
%---------------------------------------------------------------------converting everything from RGB to GRAY


%----------------------------------------------------------------getting the Fourier Transform of Original Image
img_fourier= fft2(img_data);
figure(3); imshow(log(abs(fftshift(img_fourier))), []); title('Imagem no Domínio de Fourier Centralizada');
%----------------------------------------------------------------getting the Fourier Transform of Original Image


%-----------------------------------------------------------------------------applying filters in the blocks
block_1= apply_LPF(img_upper_left, 4,5,6,7, 'Quadrante Superior Esquerdo');
block_2 = apply_LPF(img_upper_right, 8,9,10,11, 'Quadrante Superior Direito');
block_3 = apply_LPF(img_lower_left, 12,13,14,15, 'Quadrante Inferior Esquerdo');
block_4 = apply_LPF(img_lower_right, 16,17,18,19, 'Quadrante Inferior Direito');
%-----------------------------------------------------------------------------applying filters in the blocks


%-----------------------------------------------------------------------------------reconstructing the image
first_half= cat(2, block_1, block_2);
last_half= cat(2, block_3, block_4);
img_recovered= vertcat(first_half, last_half); 
figure(100); imshow(img_recovered, []); title('Imagem Reconstruída');
figure(101); imshow((log(abs(fftshift(fft2(img_recovered))))), []); title('Espectro da Imagem Reconstruída');
%-----------------------------------------------------------------------------------reconstructing the image

