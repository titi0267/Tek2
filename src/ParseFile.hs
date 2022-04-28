module ParseFile
(
    fillFileData, File(..)
)where

import Utils (getFileContent, imSureItsAnInt)
import Text.Read (readMaybe)

data File = File {
    point_x :: Maybe Int,
    point_y :: Maybe Int,
    color_r :: Maybe Int,
    color_g :: Maybe Int,
    color_b :: Maybe Int
} deriving (Show)

fillFileData :: Maybe [File] -> String -> Maybe [File]
fillFileData (Just (file:filex)) ('(':v:',':w:')':' ':'(':x:',':y:',':z:'\n':xs) =
    fillFileData (Just [file {point_x = readMaybe [v], point_y = readMaybe [w],
    color_r = readMaybe [x], color_g = readMaybe [y],
    color_b = readMaybe [z]}]) xs
fillFileData (Just file) (x:_) = fillFileData (Just [file {point_x = Nothing,
    point_y = Nothing, color_r = Nothing, color_g = Nothing, color_b = Nothing}]) xs
fillFileData file [] = Nothing
fillFileData Nothing (_:_) = Nothing
