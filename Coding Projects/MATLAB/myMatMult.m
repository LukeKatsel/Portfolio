function [M] = myMatMult(P,Q)
[p,n] = size(Q);
[m,p] = size(P);
M = zeros(m,n); % start M as an matrix filled with zeros

for i = 1:m
    for j = 1:n
        for k = 1:p
            M(i,j) = M(i,j) + P(i,k) * Q(k,j); % this is the actual calculation
        end
    end
end
end

