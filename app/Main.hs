module Main where

import Lib
import System.Environment (getArgs)
import System.Exit
import Text.Read (readMaybe)
import System.IO
import Control.Exception

data Flags = Flags {
    nbr_color :: Maybe Int,
    convergence :: Maybe Int,
    path :: String
} deriving (Show)

getFileContent :: String -> IO String
getFileContent file = do
    content <- readFile file
    return content

imSureItsAnInt :: Maybe Int -> Int
imSureItsAnInt Nothing = -1
imSureItsAnInt (Just i) = i

defaultFlags :: Flags
defaultFlags = Flags{nbr_color = Nothing, convergence = Just 0, path = ""}

fillData :: Maybe Flags -> [String] -> Maybe Flags
fillData (Just flags) ("-n":y:xs) = fillData (Just flags {nbr_color = readMaybe y :: Maybe Int}) xs
fillData (Just flags) ("-l":y:xs) = fillData (Just flags {convergence = readMaybe y :: Maybe Int}) xs
fillData (Just flags) ("-f":y:xs) = fillData (Just flags {path = y}) xs
fillData (Just flags) (_:y:xs) = Nothing
fillData flags [] = flags
fillData _ _ = Nothing

computeCompressor :: Int -> Int -> String -> IO()
computeCompressor nbr_color converge file = do
    content <- readFile file
    putStrLn content

launchCompressor :: Flags -> IO ()
launchCompressor (Flags Nothing _ _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ Nothing _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ _ "") = exitWith (ExitFailure 84)
launchCompressor (Flags nbr_color convergence path) =
    computeCompressor (imSureItsAnInt nbr_color)
    (imSureItsAnInt convergence)  path

checkLength :: Int -> IO ()
checkLength size
    | size == 6 = return ()
    | otherwise = exitWith (ExitFailure 84)

main :: IO ()
main = do
    args <- getArgs
    checkLength (length args)
    case fillData (Just defaultFlags) args of
        Nothing -> exitWith (ExitFailure 84)
        Just flags -> launchCompressor flags