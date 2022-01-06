import Data.Maybe ()

myElem :: Eq a => a -> [ a ] -> Bool
myElem a [] = False
myElem a (x:xs)
    | a == x = True 
    | otherwise = myElem a xs


safeDiv :: Int -> Int -> Maybe Int
safeDiv a 0 = Nothing
safeDiv a b = Just (a `div` b)

myLength :: [ a ] -> Int
myLength [] = 0
myLength (_:xs) = 1 + myLength xs

myIsNeg :: Int -> Bool
myIsNeg x
    | x < 0 = True 
    | otherwise = False

safeNth :: [ a ] -> Int -> Maybe a
safeNth [] y = Nothing
safeNth (x:xs) y
    | y > myLength (x:xs) = Nothing
    | myIsNeg y = Nothing
safeNth (x:xs) 0 = Just x
safeNth (x:xs) y = safeNth xs (y-1)