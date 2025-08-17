function [N] = myNChoosek(n,k)
if n == k
    N = 1;
elseif k == 1
    N = n;
else
    N = myNchoose(n-1, k) + myNChoose (n-1, k-1);
end 
end