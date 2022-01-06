import Data.Maybe ()

myElem :: Eq a => a -> [ a ] -> Bool
myElem a [] = False
myElem a (x:xs)
    | a == x = True 
    | otherwise = myElem a xs


safeDiv :: Int -> Int -> Maybe Int
safeDiv a 0 = Nothing
safeDiv a b = Just (a `div` b)
