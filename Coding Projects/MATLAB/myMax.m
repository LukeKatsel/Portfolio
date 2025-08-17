function [M] = myMax(A)
% This function finds the max value in an array
M = A(1); %M starts at the first value 
for i = 2:length(A)% iterates through all values 
    if A(i)>M % if the next value is bigger, M becomes that value 
        M = A(i); 
    end
end
end
