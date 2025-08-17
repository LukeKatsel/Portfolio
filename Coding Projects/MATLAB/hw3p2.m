for i = 1 : numel(arr)
for j = 1: numel(arr)-i
if arr(j)>arr(j+1)
tempValue = arr(j);
arr(j) = arr(j+1);
arr(j+1) = tempValue;
end
end
end
