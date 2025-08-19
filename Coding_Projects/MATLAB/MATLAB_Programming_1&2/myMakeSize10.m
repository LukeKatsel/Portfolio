function [out] = myMakeSize10(x)
% this function takes Array x and gives it a size of 10
sizeOfx = numel(x);
size = 10;
if sizeOfx < size
    out = horzcat(x, zeros(1, size - sizeOfx));
elseif sizeOfx >= size
    out = x(1) : x(size);
end
end

