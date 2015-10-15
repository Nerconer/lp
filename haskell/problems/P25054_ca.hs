myLength::[Int] -> Int
myLength [] = 0
myLength (x:xs) = 1 + myLength xs

myMaximum::[Int] -> Int
myMaximum [x] = x
myMaximum (x:xs) = max x (myMaximum xs)

average::[Int] -> Int
average [x] = x