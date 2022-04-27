module ParseArgs
    (
        Flags(..), fillData, defaultFlags, launchCompressor
    )where

import Text.Read (readMaybe)
import System.Exit
import Utils (imSureItsAnInt, printFile)

data Flags = Flags {
    nbr_color :: Maybe Int,
    convergence :: Maybe Int,
    path :: String
} deriving (Show)

defaultFlags :: Flags
defaultFlags = Flags{nbr_color = Nothing, convergence = Just 0, path = ""}

fillData :: Maybe Flags -> [String] -> Maybe Flags
fillData (Just flags) ("-n":y:xs) = fillData (Just flags {nbr_color = readMaybe y :: Maybe Int}) xs
fillData (Just flags) ("-l":y:xs) = fillData (Just flags {convergence = readMaybe y :: Maybe Int}) xs
fillData (Just flags) ("-f":y:xs) = fillData (Just flags {path = y}) xs
fillData (Just flags) (_:y:xs) = Nothing
fillData flags [] = flags
fillData _ _ = Nothing

launchCompressor :: Flags -> IO ()
launchCompressor (Flags Nothing _ _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ Nothing _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ _ "") = exitWith (ExitFailure 84)
launchCompressor (Flags nbr_color convergence path) =
    printFile (imSureItsAnInt nbr_color)
    (imSureItsAnInt convergence)  path