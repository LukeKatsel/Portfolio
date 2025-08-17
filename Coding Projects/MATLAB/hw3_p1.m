function sorted = Quick_Sort(a)

n=length(a);

if n<2
sorted = a;
return;
end

x1 = [];
x2 = [];

for i = 1:n-1

if a(i)>a(n)
x1 = [x1 a(i)];
else
x2 = [x2 a(i)];
end
end

sorted = [Quick_Sort(x1) a(n) Quick_Sort(x2)];

end