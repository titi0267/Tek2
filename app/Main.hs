module Main where

import Utils (checkLength, imSureItsAnInt)
import ParseArgs (launchCompressor, fillData, defaultFlags)
import System.Environment (getArgs)
import System.Exit
import System.IO

main :: IO ()
main = do
    args <- getArgs
    checkLength (length args)
    case fillData (Just defaultFlags) args of
        Nothing -> exitWith (ExitFailure 84)
        Just flags -> launchCompressor flags
