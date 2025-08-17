function [h] = mySplitFunction(f, g, a, b, x)
% this outputs f(x) if x <= a and g(x) i x >= b
if x >= b
    h = g(x);
elseif x <= a
    h = f(x);
else 
    h = 0;
end

end

