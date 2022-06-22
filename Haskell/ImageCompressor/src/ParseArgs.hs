module ParseArgs
    (
        fillData, defaultFlags, launchCompressor
    )where

import Text.Read (readMaybe)
import System.Exit
import Algo (prepareAlgo)
import Structures (Flags(..))
import Utils (imSureItsAnInt, printFile, splitLines, splitWords)
import ParseFile
    (
        replaceBySpace, defaultPixel,
        checkPixelsValid, putPixelInData
    )


defaultFlags :: Flags
defaultFlags = Flags{nbr_color = Nothing, convergence = Just 0, path = ""}

checkNbrColorValid:: Flags -> Int -> IO()
checkNbrColorValid (Flags color _ _) pixelLen
    | imSureItsAnInt color > pixelLen = exitWith (ExitFailure 84)
    | otherwise = return ()

fillData :: Maybe Flags -> [String] -> Maybe Flags
fillData (Just flags) ("-n":y:xs) =
    fillData (Just flags {nbr_color = readMaybe y :: Maybe Int}) xs
fillData (Just flags) ("-l":y:xs) =
    fillData (Just flags {convergence = readMaybe y :: Maybe Float}) xs
fillData (Just flags) ("-f":y:xs) = fillData (Just flags {path = y}) xs
fillData (Just flags) (_:y:xs) = Nothing
fillData flags [] = flags
fillData _ _ = Nothing

computeCompressor :: Flags -> IO ()
computeCompressor (Flags nbr_color convergence path) = do
    content <- readFile path
    let pixels = putPixelInData [] $ map x (splitLines content)
    checkPixelsValid pixels
    checkNbrColorValid  (Flags nbr_color convergence path) (length pixels)
    prepareAlgo (Flags nbr_color convergence path) pixels
    where
        x = splitWords . replaceBySpace

launchCompressor :: Flags -> IO ()
launchCompressor (Flags Nothing _ _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ Nothing _) = exitWith (ExitFailure 84)
launchCompressor (Flags _ _ "") = exitWith (ExitFailure 84)
launchCompressor flags = computeCompressor flags