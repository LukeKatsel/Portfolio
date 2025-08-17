function [indices] = myWithinTolerance(A, a, tol)
% temp holds result of |A-a|
temp = abs(A - a);
indices = [];
    for i = 1:length(temp)
        % each part of temp should be checked
         if (temp(i) < tol)
         indices(end+1) = i;
         end
    end
end



