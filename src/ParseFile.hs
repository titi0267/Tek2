module ParseFile
(
    fillFileData, Pixel(..), defaultPixel, checkPixelsValid
)where

import Utils (imSureItsAnInt)
import Text.Read (readMaybe)
import Data.Maybe
import System.Exit (exitWith, ExitCode (ExitFailure))

data Pixel = Pixel {
    point :: (Int, Int),
    color :: (Int, Int, Int)
} deriving (Show)

defaultPixel :: Pixel
defaultPixel = (Pixel {point = (-1, -1),
    color = (-1 , -1, -1)})

readShort :: String -> Int
readShort str
    | isNothing (readMaybe str :: Maybe Int) = -1
    | (read str :: Int) > 255 = -1
    | (read str :: Int) < 0 = -1
    | otherwise = read str :: Int

fillFileData :: [Pixel] -> String -> [Pixel]
fillFileData file [] = file
fillFileData file ['(', v, ',', w, ')', ' ', '(', x, ',', y, ',', z, ')'] =
    file ++ [Pixel {point = (readShort [v], readShort [w]),
    color = (readShort [x], readShort [y], readShort [z])}]
fillFileData file ('(':v:',':w:')':' ':'(':x:',':y:',':z:')':'\n':xs) =
    fillFileData (file ++ [Pixel {point = (readShort [v], readShort [w]),
    color = (readShort [x], readShort [y], readShort [z])}]) xs
fillFileData file (_:_) = [defaultPixel]


checkPixelsValid :: [Pixel] -> IO()
checkPixelsValid [] = return ()
checkPixelsValid ((Pixel (-1, _) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel (_, -1) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (-1, _, _)):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, -1 , _)):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, _, -1 )):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid (_:nextPixel) = checkPixelsValid nextPixel