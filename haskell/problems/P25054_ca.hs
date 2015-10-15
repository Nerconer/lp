myLength::[Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

myMaximum::[Int] -> Int
myMaximum [x] = x
myMaximum (x1: x2: xs)  
	| x1 >= x2 = myMaximum (x1:xs)
	| otherwise = myMaximum (x2:xs)

-- average::[Int] -> Float
-- average (x:xs) = 
--	let sum = fromIntegral $ x + (average xs); len = fromIntegral $ (myLength xs) + 1
--	in (fromIntegral sum) / (fromIntegral len)


