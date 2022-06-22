module RuleTest
    ( printList, parseArgs
    ) where

import System.Exit ( ExitCode(ExitFailure), exitWith, exitFailure )
import Lib (Conf (..), flags, defaultConf)
import BitPerBit (firstBit, secondBit, thirdBit, fourthBit, fifthBit, sixthBit, seventhBit, eigthBit)
import Debug.Trace (trace)
import Control.Arrow (Arrow(first))

runLines :: Conf -> Maybe Int-> Conf
runLines conf x = conf{t_lines = x}

parseArgs :: [ String ] -> Maybe Conf
parseArgs x
    | length x >= 2 = flags defaultConf x
    | otherwise = Nothing

convertInt :: Maybe Int -> Int
convertInt (Just x) = x
convertInt _ = -1

windowSize :: a -> Int -> Conf -> [ a ]
windowSize a x conf = replicate x a

--windowSize a conf = replicate (convertInt (t_window conf)) a

convertBin :: Int -> [ Int ]
convertBin 0 = [0]
convertBin y
    | y `mod` 2 == 0 = convertBin (y `div` 2) ++ [0]
    | otherwise = convertBin (y `div` 2) ++ [1]

applyDec :: Maybe Int -> Int
applyDec (Just x) = (x-1)
applyDec _ = -1

lineSize :: Conf -> Conf
lineSize conf
    | (convertInt (t_lines conf) > 0) == True = conf{t_lines = Just (applyDec (t_lines conf))}
    | otherwise = conf{t_lines = Just 0}

setLine :: Conf -> String -> String
setLine conf str
    | ((convertInt (t_lines conf)) > 0) == True = trace str ((setLine (lineSize conf) (concat [(firstBit str 1) ++ (secondBit str 1) ++ (thirdBit str 0) ++ (fourthBit str 1) ++ (sixthBit str 1) ++ (seventhBit str 1) ++ (eigthBit str 0)])))--((convertInt (t_lines conf)) > 0) == True = trace (concat [((windowSize ' ' ((convertInt (t_window conf))`div`2) conf) ++ "*")]) ((setLine (lineSize conf) x))
    | otherwise = ""

--setList :: Conf -> [String] -> Conf
--setList conf _ = setLine conf "x" a--(setLine(lineSize conf) "x")
    --case convertInt (t_lines conf) > 0 of
        --True -> (setList conf (setLine (lineSize conf)))
        --False -> print ["a"]

--findStr :: String -> Int -> Char
--findStr (x:y:z:xs) a = 
--findStr [] _ = ' '
--findStr _ _ = ' '

printList :: Conf -> IO ()
printList conf = do
    putStr (setLine conf (concat [((windowSize ' ' ((convertInt (t_window conf))`div`2) conf) ++ "*")]))
    --let sec = (setLine conf (concat [(firstBit str 1) ++ (secondBit str 1) ++ (thirdBit str 0) ++ (fourthBit str 1) ++ (sixthBit str 1) ++ (seventhBit str 1) ++ (eigthBit str 0)]))
    --putStrLn str--(setLine conf (concat [(firstBit str 1) ++ (secondBit str 1) ++ (thirdBit str 0) ++ (fourthBit str 1) ++ (sixthBit str 1) ++ (seventhBit str 1) ++ (eigthBit str 0)]))