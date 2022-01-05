import Data.Time.Format.ISO8601 (yearFormat)
import Distribution.Simple.Utils (xargs)
mySucc :: Int -> Int 
mySucc x = x + 1

myIsNeg :: Int -> Bool
myIsNeg x
    | x < 0 = True 
    | otherwise = False

myAbs :: Int -> Int
myAbs x 
    | myIsNeg x = -x
    | otherwise = x

myMin :: Int -> Int -> Int
myMin x y
    | x < y = x
    | otherwise = y

myMax :: Int -> Int -> Int
myMax x y
    | x > y = x
    | otherwise = y

myTuple :: a -> b -> (a , b)
myTuple a b = (a, b)

myTruple :: a -> b -> c -> (a , b , c)
myTruple a b c = (a,b,c)

myFst :: (a , b ) -> a
myFst (a,b) = a

mySnd :: (a , b ) -> b
mySnd (a,b) = b

mySwap :: (a , b ) -> (b , a )
mySwap (a,b) = (b,a)

myHead :: [ a ] -> a
myHead [] = error "empty list"
myHead (x:xs) = x

myTail :: [ a ] -> [ a ]
myTail [] = error "empty list"
myTail (x:xs) = xs

myLength :: [ a ] -> Int
myLength [] = 0
myLength (_:xs) = 1 + myLength xs

myNth :: [ a ] -> Int -> a
myNth [] y = error "empty list"
myNth (x:xs) y
    | y > myLength (x:xs) = error "index too large"
    | myIsNeg y = error "Index is negative"
myNth (x:xs) 0 = x
myNth (x:xs) y = myNth xs (y-1)

myTake :: Int -> [ a ] -> [ a ]
myTake y [] = error "empty list"
myTake y (x:xs)
    | y >= myLength (x:xs) = x:xs
    | myIsNeg y = error "N is negative"
myTake 0 (x:xs) = []
myTake y (x:xs) = x: myTake (y-1) xs

myDrop :: Int -> [ a ] -> [ a ]
myDrop y [] = error "empty list"
myDrop y (x:xs)
    | myIsNeg y = error "N is negative"
    | y >= myLength (x:xs) = []
myDrop 0 (x:xs) = x:xs
myDrop y (x:xs) = myDrop (y-1) xs

myAppend :: [ a ] -> [ a ] -> [ a ]
myAppend [] x = x
myAppend (x:xs) y = x : myAppend xs y

myReverse :: [ a ] -> [ a ]
myReverse [] = []
myReverse (x:xs) = myAppend (myReverse xs) [x]