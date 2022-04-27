module Main where

import Lib
import Utils (checkLength, getFileContent, imSureItsAnInt)
import ParseArgs (launchCompressor, fillData, defaultFlags, Flags(..))
import System.Environment (getArgs)
import System.Exit
import System.IO
import Control.Exception

main :: IO ()
main = do
    args <- getArgs
    checkLength (length args)
    case fillData (Just defaultFlags) args of
        Nothing -> exitWith (ExitFailure 84)
        Just flags -> launchCompressor flags