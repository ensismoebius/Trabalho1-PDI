function y= apply_HPF(input_img_read, n1, n2, n3, n4, t1)

figure(n1); imshow(input_img_read); title(t1)
PQ = paddedsize(size(input_img_read));%Determine good padding for Fourier transform

%Create a Ideal Highpass filter N% the width of the Fourier transform
D0 = 0.04*PQ(1);H = hpfilter('ideal', PQ(1), PQ(2), D0);
F=fft2(double(input_img_read),size(H,1),size(H,2));% Calculate the discrete Fourier transform of the image
LPFS_image = H.*F;% Apply the lowpass filter to the Fourier spectrum of the image
LPF_image=real(ifft2(LPFS_image));% convert the result to the spacial domain.
LPF_image=LPF_image(1:size(input_img_read,1), 1:size(input_img_read,2));% Crop the image to undo padding
figure(n2); imshow(LPF_image, []); title(t1)%Display the blurred image

% Display the Fourier Spectrum 
S1=log(1+abs(fftshift(F))); 
S2=log(1+abs(fftshift(LPFS_image)));
figure(n3); imshow(S1,[]); title(t1)
figure(n4); imshow(S2,[]); title(t1)

y= LPF_image;

end