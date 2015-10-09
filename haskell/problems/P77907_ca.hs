absValue:: Int -> Int
power:: Int -> Int -> Int
isPrime:: Int -> Bool
-- slowFib:: Int -> Int
-- quickFib:: Int -> Int



-- Valor absolut

absValue n = abs (n)


-- Potencia x^y

power x 0 = 1
power x y = 
  x * (power x (y-1))
 
 
-- Es primer x
isPrime 0 = False
isPrime n = 
  let y = div n 2
  in if y == 0 then False
    else True 


-- n-essim elem Fibonacci

slowFib 0 = 0
slowFib 1 = 1
slowFib n = 
  slowFib (n-1) + slowFib (n-2)
  
  
-- fib2 0 = (0,1)
-- fib2 n =

-- quickFib = fst * fib2
  

  
