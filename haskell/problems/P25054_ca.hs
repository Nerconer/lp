myLength :: [Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

myMaximum :: [Int] -> Int
myMaximum [x] = x
myMaximum (x1: x2: xs) 
 | x1 >= x2 = myMaximum (x1:xs)
 | otherwise = myMaximum (x2:xs)

mySum :: [Int] -> Int
mySum [x] = x
mySum (x:xs) = 
	x + mySum xs

average :: [Int] -> Float
average [] = error "Error: llista buida"
average x = 
 	(fromIntegral $ mySum x) / (fromIntegral $ myLength x)

buildPalindrome :: [Int] -> Int
buildPalindrome


