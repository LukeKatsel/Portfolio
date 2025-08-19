function [out] = myIsPrime(n)
out = 1; % starts as 1 
for i = 2:ceil(sqrt(n))% goes through numbers 2 to square root of n
    if mod(n,i)==0 
        out = 0; % changes to 0 if n is not prime 
    end
end
end

