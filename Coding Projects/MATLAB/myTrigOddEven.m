function [Q] = myTrigOddEven(M)
[m,n] = size(M); 
Q = zeros(m,n); 
for i = 1:m
    for j = 1:n
        if (mod(M(i,j),2) ==0)
            Q(i,j) = sin(M(i,j));
        else
            Q(i,j) = cos(M(i,j));
        end
    end
end
end

