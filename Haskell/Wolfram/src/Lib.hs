module Lib
    ( Conf (..)
    , flags, defaultConf
    ) where

import Data.Maybe ()
import Text.Read

data Conf = Conf {
    t_rule :: Maybe Int,
    t_start :: Maybe Int,
    t_lines :: Maybe Int,
    t_window :: Maybe Int,
    t_move :: Maybe Int,
    t_str :: [String]
} deriving (Show)

defaultConf :: Conf
defaultConf = Conf{t_rule=Nothing, t_start= Just 0, t_lines= Just 0, t_window= Just 80, t_move= Nothing, t_str=[""]}

flags :: Conf -> [ String ] -> Maybe Conf
flags conf [] = Just conf
flags cont (x:[]) = Nothing
flags conf ("--rule":"30":xs) = flags conf{t_rule = Just 30} xs
flags conf ("--rule":"90":xs) = flags conf{t_rule = Just 90} xs
flags conf ("--rule":"110":xs) = flags conf{t_rule = Just 110} xs
flags conf ("--start":y:xs) = flags conf{t_start = readMaybe y} xs
flags conf ("--lines":y:xs) = flags conf{t_lines = readMaybe y} xs
flags conf ("--window":y:xs) = flags conf{t_window = readMaybe y} xs
flags conf ("--move":y:xs) = flags conf{t_window = readMaybe y} xs
flags _ (_:_) = Nothing

