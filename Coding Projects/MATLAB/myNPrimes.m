function [primes] = myNPrimes(N)
primes = [2];% start prime with the first prime number
tmp = 2; % temp variable to hold the previous number 
while length(primes)<N
    tmp = tmp +1; % check next number
    prime = true; % initialize to prime
    for i = primes 
        if mod(tmp, i) == 0
            prime = false; % false if not prime 
            
        end
    end
    if prime
        primes(end + 1) = tmp; % add to list if prime
    end
end
end

