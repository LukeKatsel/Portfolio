function [response] = myNukeAlarm(s1, s2, s3)
% this function simulates a nuclear sensor that outputs alarm! if more than
% 10 degrees off
if abs(s1 - s2) > 10 || abs(s2 - s3) > 10 || abs(s1 - s3) > 10 
    response = 'alarm!'; 
else
    response = 'normal';
end
end

