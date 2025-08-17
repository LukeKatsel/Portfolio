function [row] = myPascalRow(m)
row = ones(1,m);
if m >1
    for i=2:m-1
        row(i) = myPascalRow(m-1)(i-1) + myPascalRow(m-1)(i);
    end
end
end
