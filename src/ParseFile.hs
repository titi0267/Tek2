module ParseFile
(
    fillFileData, File(..), defaultFile, endFile
)where

import Utils (imSureItsAnInt)
import Text.Read (readMaybe)

data File = File {
    point_x :: Maybe Int,
    point_y :: Maybe Int,
    color_r :: Maybe Int,
    color_g :: Maybe Int,
    color_b :: Maybe Int
} deriving (Show)

defaultFile :: File
defaultFile = (File {point_x = Nothing , point_y = Nothing,
    color_r = Nothing, color_g = Nothing, color_b = Nothing})

endFile :: File
endFile = (File {point_x = Just (-1) , point_y = Just (-1),
    color_r = Just (-1), color_g = Just (-1), color_b = Just (-1)})

fillFileData :: [File] -> String -> [File]
fillFileData file [] = file
fillFileData file ['(', v, ',', w, ')', ' ', '(', x, ',', y, ',', z, ')'] =
    file ++ [File {point_x = readMaybe [v], point_y = readMaybe [w],
    color_r = readMaybe [x], color_g = readMaybe [y],
    color_b = readMaybe [z]}]
fillFileData file ('(':v:',':w:')':' ':'(':x:',':y:',':z:')':'\n':xs) =
    fillFileData (file ++ [File {point_x = readMaybe [v], point_y = readMaybe [w],
    color_r = readMaybe [x], color_g = readMaybe [y],
    color_b = readMaybe [z]}]) xs
fillFileData file (_:_) = [defaultFile]
