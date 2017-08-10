
 clear
 clc
 lujing='C:\Users\hongrui.wang\data\sky_image\'
     
 file_name = 'sun'
 org = imread([lujing,file_name,'.jpg']);
 grab = org(:,:,1);

[row_size,column_size] = size(grab);


threhold = 252
binary = grab  > threhold;

m = binary;


[row,column] = size(m);
x_sum = 0;
y_sum = 0;
num = 0;
for j=1:row
    for k = 1:column
        if m(j,k)==1
            x_sum = x_sum + k;
            y_sum = y_sum + j;
            num = num +1;
        end
    end
end
if num ==0
    num =10^4;
end
y(1) = x_sum / num;
y(2) = y_sum / num;
position = y;


sun_x = floor(position(1));
sun_y = floor(position(2));

subplot(211)
imshow(org);
hold on
plot(sun_x,sun_y,'r+')

subplot(212)
imshow(binary);
hold on
plot(sun_x,sun_y,'r+')



