module ParseFile
(
    fillFileData, Pixel(..), defaultPixel, checkPixelsValid
)where

import Utils (imSureItsAnInt)
import Text.Read (readMaybe)
import Data.Maybe
import System.Exit (exitWith, ExitCode (ExitFailure))

data Pixel = Pixel {
    point :: (Maybe Int, Maybe Int),
    color :: (Maybe Int, Maybe Int, Maybe Int)
} deriving (Show)

defaultPixel :: Pixel
defaultPixel = (Pixel {point = (Nothing , Nothing),
    color = (Nothing , Nothing, Nothing)})

readShort :: String -> Maybe Int
readShort str
    | isNothing (readMaybe str :: Maybe Int) = Nothing
    | (read str :: Int) > 255 = Nothing
    | (read str :: Int) < 0 = Nothing
    | otherwise = Just (read str :: Int)

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
checkPixelsValid ((Pixel (Nothing, _) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel (_, Nothing) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (Nothing, _, _)):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, Nothing , _)):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, _, Nothing )):nextPixel) =
    exitWith (ExitFailure 84)
checkPixelsValid (_:nextPixel) = checkPixelsValid nextPixel