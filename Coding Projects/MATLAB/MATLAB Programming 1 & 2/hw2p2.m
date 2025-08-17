function index = Binary(array, a, b, target)
    same = floor((a + b) / 2); 
    if a > b
        index = -1;
    elseif array(same) == target
        index = same;
    elseif target < array(same)
        index = Binary(array, a, same - 1, target);     
    else
        index = Binary(array, same + 1, b, target);  
    end
end