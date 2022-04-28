module ParseFile
(
    fillFileData, Pixel(..), defaultPixel, checkPixelsValid
)where

import Utils (imSureItsAnInt)
import Text.Read (readMaybe)
import System.Exit (exitWith, ExitCode (ExitFailure))

data Pixel = Pixel {
    point_x :: Maybe Int,
    point_y :: Maybe Int,
    color_r :: Maybe Int,
    color_g :: Maybe Int,
    color_b :: Maybe Int
} deriving (Show)

defaultPixel :: Pixel
defaultPixel = (Pixel {point_x = Nothing , point_y = Nothing,
    color_r = Nothing, color_g = Nothing, color_b = Nothing})

fillFileData :: [Pixel] -> String -> [Pixel]
fillFileData file [] = file
fillFileData file ['(', v, ',', w, ')', ' ', '(', x, ',', y, ',', z, ')'] =
    file ++ [Pixel {point_x = readMaybe [v], point_y = readMaybe [w],
    color_r = readMaybe [x], color_g = readMaybe [y],
    color_b = readMaybe [z]}]
fillFileData file ('(':v:',':w:')':' ':'(':x:',':y:',':z:')':'\n':xs) =
    fillFileData (file ++ [Pixel {point_x = readMaybe [v], point_y = readMaybe [w],
    color_r = readMaybe [x], color_g = readMaybe [y],
    color_b = readMaybe [z]}]) xs
fillFileData file (_:_) = [defaultPixel]


checkPixelsValid :: [Pixel] -> IO()
checkPixelsValid [] = return ()
checkPixelsValid ((Pixel Nothing _ _ _ _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ Nothing _ _ _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ _ Nothing _ _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ _ _ Nothing _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ _ _ _ Nothing):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid (_:nextPixel) = checkPixelsValid nextPixel