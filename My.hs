import Data.Time.Format.ISO8601 (yearFormat)
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