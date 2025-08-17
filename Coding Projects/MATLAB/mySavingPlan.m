function [years] = mySavingPlan(P0,i,goal)
total = P0; % total starts as the principal
years = 0; % years starts as 0
while total < goal 
    total = total * (1 + i); % formula 
    years = years + 1; % years needs to increase 
end
end

