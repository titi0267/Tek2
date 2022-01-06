import Data.Maybe ()
import Data.Char (isDigit)
import Control.Monad

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

readInt :: [ Char ] -> Maybe Int
readInt [] = Nothing
readInt (x:xs)
    | x == '-' || all isDigit xs = Just (read (x:xs) :: Int)
    | otherwise = Nothing

getLineLength :: IO Int
getLineLength = do
    line <- getLine
    return $ length line

printAndGetLength :: String -> IO Int
printAndGetLength x = do
    putStrLn x
    return (myLength x)

printBox :: Int -> IO ()
printBox x = if x <= 0 then return ()
                else do
                    putStr $ concat["+",replicate (x*2-2) '-', "+\n"]
                    putStr $ unlines $ replicate (x-2) (
                        concat["|", replicate (x*2-2) ' ', "|"])
                    putStr $ concat["+",replicate (x*2-2) '-', "+\n"]

concatLines :: Int -> IO String
concatLines x
    | x <= 0 = return []
    | otherwise = do
        line <- getLine
        lines <- concatLines (x - 1)
        return (line ++ lines)

getInt :: IO ( Maybe Int )
getInt = do
    line <- getLine 
    return (readInt line)
