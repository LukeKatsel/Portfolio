function [y] = myChebyShevPoly1(n,x)
if n == 0
    y = ones(1,length(x));
elseif n == 1
    y = x;
else 
    y = 2.*x.*myChebyShevPoly1(n-1,x) .-
    myChebyShevPoly1(n-2,x);
end
end

    