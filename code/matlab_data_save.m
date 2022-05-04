clear
close all
clc
delete(instrfind);
arduino = serial('com5');
set(arduino,'BaudRate',230400);
duration = 10; %in seconds
fs = 20; %in Hz
total_sample = (fs*duration) + 5;
fopen(arduino);
array = zeros(total_sample,4);
pw = 3*fs; %plot window
    for j=1:total_sample     % Trial loop
            data = fscanf(arduino)
            commas = strfind(data,',');
            array(j,1) = str2double(data(1:commas(1)-1));
            array(j,2) = str2double(data(commas(1):commas(2)-1));
            array(j,3) = str2double(data(commas(2):commas(3)-1));
            array(j,4) = str2double(data(commas(3):end));
    end
    
    % save all those 4 arrays into the related mat file.             
        
     save('test_matlab.mat','array');
     plot(array);
% Close serial port
fclose(arduino);
delete(arduino);
clear arduino;