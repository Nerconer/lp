
-- Valor absolut

absValue:: Int -> Int
absValue n = if n > 0 then n else (-n)


-- Potencia x^y

power:: Int -> Int -> Int
power x 0 = 1
power x y = 
  x * (power x (y-1))
 
 
-- Es primer x

isPrime:: Int -> Bool
isPrime 0 = False
isPrime 1 = False
isPrime x = not $ any divisible $ takeWhile notTooBig [2..] where
     divisible y = x `mod`y == 0
     notTooBig y = y*y <= x

-- n-essim elem Fibonacci

slowFib:: Int -> Int
slowFib 0 = 0
slowFib 1 = 1
slowFib n = 
  slowFib (n-1) + slowFib (n-2)
  
  
-- fib2 0 = (0,1)
-- fib2 n =

-- quickFib = fst * fib2
fib :: Int -> (Int, Int)
fib 0 = (0, 1)
fib n =
	let (a, b) = fib (div n 2)
	    c = a * (b * 2 - a)
	    d = a * a + b * b
	in if mod n 2 == 0
		then (c, d)
		else (d, c + d)

quickFib:: Int -> Int
quickFib n | n >= 0 = fst (fib n)
  

  
