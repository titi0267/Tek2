import Data.Maybe ()
import Data.Char (isDigit)
import Control.Monad
import System.Directory.Internal.Prelude (getArgs)
import System.Exit
import System.Environment

myElem :: Eq a => a -> [ a ] -> Bool
myElem a [] = False
myElem a (x:xs)
    | a == x = True 
    | otherwise = myElem a xs


safeDiv :: Int -> Int -> Maybe Int
safeDiv a 0 = Nothing
safeDiv a b = Just (a `div` b)

safeMod :: Int -> Int -> Maybe Int
safeMod a 0 = Nothing
safeMod a b = Just (a `mod` b)

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
readInt ('-':xs)
    | all isDigit xs = Just (read xs :: Int)
    | otherwise = Nothing
readInt x
    | all isDigit x = Just (read x :: Int)
    | otherwise = Nothing

getLineLength :: IO Int
getLineLength = do
    line <- getLine
    return $ length line

printAndGetLength :: String -> IO Int
printAndGetLength x = putStrLn x >> return (myLength x)

printBox :: Int -> IO ()
printBox 1 = putStrLn "++"
printBox x = case x <= 0 of
    True -> return ()
    False -> do 
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

myNth :: [ a ] -> Int -> a
myNth [] y = error "empty list"
myNth (x:xs) y
    | y > myLength (x:xs) = error "index too large"
    | myIsNeg y = error "Index is negative"
myNth (x:xs) 0 = x
myNth (x:xs) y = myNth xs (y-1)

myReadInt :: [ Char ] -> Int
myReadInt [] = 0
myReadInt ('-':xs)
    | all isDigit xs = read xs :: Int
    | otherwise = 0
myReadInt x
    | all isDigit x = read x :: Int
    | otherwise = 0

main :: IO ()
main = do
    args <- getArgs
    case myLength args /= 3 || myElem (myNth args 1) ["+","-","/","*","%"] == False
        || readInt (myNth args 0) == Nothing || readInt (myNth args 2) == Nothing of 
        True  -> exitWith (ExitFailure 84)
        False  -> pure ()
    case myNth args 1 of
        "+" -> print $ myReadInt (myNth args 0) + myReadInt (myNth args 2)
        "-" -> print $ myReadInt (myNth args 0) - myReadInt (myNth args 2)
        "*" -> print $ myReadInt (myNth args 0) * myReadInt (myNth args 2)
        "/" -> case safeDiv (myReadInt (myNth args 0))  (myReadInt (myNth args 2)) of
                Nothing -> exitWith (ExitFailure 84)
                _ -> print $ myReadInt (myNth args 0) `div` myReadInt (myNth args 2)   
        "%" -> case safeMod (myReadInt (myNth args 0))  (myReadInt (myNth args 2)) of
                Nothing -> exitWith (ExitFailure 84)
                _ -> print $ myReadInt (myNth args 0) `mod` myReadInt (myNth args 2)
        _ -> exitWith (ExitFailure 84)
