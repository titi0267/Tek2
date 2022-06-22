module Main where

<<<<<<< HEAD
import RuleTest (printList, parseArgs)
import Lib (Conf (..), defaultConf)
import Data.Maybe
import System.Environment (getArgs)
import System.Exit ( ExitCode(ExitFailure), exitWith )

--runLines (conf@Conf { t_lines = Just x }) = Just (t_lines (Just conf))

=======
import Utils (checkLength, imSureItsAnInt)
import ParseArgs (launchCompressor, fillData, defaultFlags)
import System.Environment (getArgs)
import System.Exit
import System.IO
>>>>>>> ImgCompressor

main :: IO ()
main = do
    args <- getArgs
<<<<<<< HEAD
    let conf = (parseArgs args)
    case conf of
        Nothing -> exitWith (ExitFailure 84)
        Just conf -> printList conf
    --print (printList ())
    case conf of
        Nothing -> exitWith (ExitFailure 84)
        Just conf -> print (t_lines conf)
    print args
    --print (t_lines conf)
=======
    checkLength (length args)
    case fillData (Just defaultFlags) args of
        Nothing -> exitWith (ExitFailure 84)
        Just flags -> launchCompressor flags
>>>>>>> ImgCompressor
