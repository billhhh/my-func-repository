%
%% date: 5/5/2017
%
%% Author: Congbo Ma, Hu Wang
%
%  write matrix to file

function wrt_mat_to_file( filename,source_matrix )  

fid=fopen(filename,'a');  
[x,y]=size(source_matrix);  

for i=1:x  
    for j=1:y-1  
        fprintf(fid,'%f\t',source_matrix(i,j));  
    end  
    fprintf(fid,'%f\n',source_matrix(i,y));%每一行回车\n  
end  

fclose(fid);
end  