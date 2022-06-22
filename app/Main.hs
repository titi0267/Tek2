module Main where

import RuleTest (printList, parseArgs)
import Lib (Conf (..), defaultConf)
import Data.Maybe
import System.Environment (getArgs)
import System.Exit ( ExitCode(ExitFailure), exitWith )

--runLines (conf@Conf { t_lines = Just x }) = Just (t_lines (Just conf))


main :: IO ()
main = do
    args <- getArgs
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