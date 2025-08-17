function [nRoots, r] = myNRoots(a, b, c)
if b^2 < 4 * a * c
    nRoots = -2;
    r(1) = (-b + sqrt(b*b - 4*a*c)) / (2 * a);
    r(2) = (-b - sqrt(b*b - 4*a*c)) / (2 * a);
elseif b^2 > 4 * a * c
    nRoots = 2;
    r(1) = (-b + sqrt(b*b - 4*a*c)) / (2 * a);
    r(2) = (-b - sqrt(b*b - 4*a*c)) / (2 * a);
else
    nRoots = 1;
    r = -b / (2 * a);
end
    
end

