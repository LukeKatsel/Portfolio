function [tip] = myTipCalc(bill,party)
% myTipCalc creates a tip ammount based on # of people and bill ammount
% if and elseif statements determine what tip rate based on # of people
if (party > 11)
    tip = bill * 0.25;
elseif (party >= 8 && party < 11)
    tip = bill * 0.20;
elseif(party >= 6 && party < 8)
    tip = bill * 0.18;
elseif(party < 6) 
    tip = bill * 0.15;
    
end

end

