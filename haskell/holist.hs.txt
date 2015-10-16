-- NO CARREGUEU AQUEST ARXIU

map :: (a->b) -> [a] -> [b]
-- aplica la funció a tots el elements de la llista

--map (*2) [2,4,6,7]
--[4,8,12,14]

--map (even) [2,4,6,7]
--[True,True,True,False]

foldr :: (a -> b -> b) -> b -> [a] -> b
--rec 
--foldr f x [x1,....,xn] = -- (f x1 (f x2 ( .....(f xn (foldr f x []) )...))) 
--foldr f x [] = x
--foldr (+) 0 [3,2,(-1)]
--4

foldl::(a -> b -> a) -> a -> [b] -> a
--iter // tail recursive definition
--foldl f x [x1,....,xn] = foldl f (f ( ... (f x x1) ... ) xn) []
--foldl f x [] = x
--foldl (+) 0 [3,2,(-1)]
--4

scanr :: (a -> b -> b) -> b -> [a] -> [b]
-- retorna la llista amb tots els valors intermedis calculats pel foldr
--scanr (+) 0 [3,2,(-1)]
--[4,1,-1,0]
--Noteu que el foldr calcula amb el resultat crida recursiva.

scanl::(a -> b -> a) -> a -> [b] -> [a]
-- retorna retorna la llista amb tots els valors intermedis calculats pel foldrl
--scanl (+) 0 [3,2,(-1)]
--[0,3,5,4]
--Noteu que el foldl acumula el càlcul en el pas de paràmetres a la crida recursiva.

iterate :: (a -> a) -> a -> [a]
-- iterate f x = ----[x, (f x), (f (f x)), (f (f (f x))), ....

all::(a -> Bool) -> [a] -> Bool
-- tots els elements de la llista satisfan la propietat.

any::(a -> Bool) -> [a] -> Bool
-- algun element de la llista satisfà la propietat.

filter::(a -> Bool) -> [a] -> [a]
-- selecciona els que satisfan la propietat

dropWhile::(a -> Bool) -> [a] -> [a]
-- elimina mentre es satisfà la propietat.
--dropWhile  (even) [2,4,6,7]
--[7]

takeWhile::(a -> Bool) -> [a] -> [a]
-- es queda els elements mentre es satisfà la propietat.
--takeWhile  (even) [2,4,6,7]
--[2,4,6]

zipWith::(a -> b -> c) -> [a] -> [b] -> [c]
-- Aplica la funció als elements dos a dos de les llistes donades i
-- retorna la llista de resultats.
