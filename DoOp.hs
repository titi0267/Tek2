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
safeNth (x:_) 0 = Just x
safeNth (_:xs) y = safeNth xs (y-1)

safeSucc :: Maybe Int -> Maybe Int
safeSucc Nothing = Nothing
safeSucc (Just x) = Just (x+1)

myLookup :: Eq a => a -> [( a , b ) ] -> Maybe b
myLookup a [] = Nothing
myLookup a ((x,xs) : y)
    | x == a = Just xs
    | otherwise = myLookup a y

maybeDo :: ( a -> b -> c ) -> Maybe a -> Maybe b -> Maybe c
maybeDo func Nothing (Just b) = Nothing 
maybeDo func (Just a) Nothing = Nothing
maybeDo func Nothing Nothing = Nothing
maybeDo func (Just a) (Just b) = Just (func a b)
