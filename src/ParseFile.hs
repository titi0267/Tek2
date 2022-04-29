module ParseFile
(
    fillFileData, Pixel(..), defaultPixel, checkPixelsValid
)where

import Utils (imSureItsAnInt)
import Text.Read (readMaybe)
import System.Exit (exitWith, ExitCode (ExitFailure))

data Pixel = Pixel {
    point :: (Maybe Int, Maybe Int),
    color :: (Maybe Int, Maybe Int, Maybe Int)
} deriving (Show)

defaultPixel :: Pixel
defaultPixel = (Pixel {point = (Nothing , Nothing),
    color = (Nothing , Nothing, Nothing)})

fillFileData :: [Pixel] -> String -> [Pixel]
fillFileData file [] = file
fillFileData file ['(', v, ',', w, ')', ' ', '(', x, ',', y, ',', z, ')'] =
    file ++ [Pixel {point = (readMaybe [v], readMaybe [w]),
    color = (readMaybe [x], readMaybe [y], readMaybe [z])}]
fillFileData file ('(':v:',':w:')':' ':'(':x:',':y:',':z:')':'\n':xs) =
    fillFileData (file ++ [Pixel {point = (readMaybe [v], readMaybe [w]),
    color = (readMaybe [x], readMaybe [y], readMaybe [z])}]) xs
fillFileData file (_:_) = [defaultPixel]


checkPixelsValid :: [Pixel] -> IO()
checkPixelsValid [] = return ()
checkPixelsValid ((Pixel (Nothing, _) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel (_, Nothing) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (Nothing, _, _)):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, Nothing , _)):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, _, Nothing )):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid (_:nextPixel) = checkPixelsValid nextPixel