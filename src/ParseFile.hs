module ParseFile
(
    replaceBySpace, defaultPixel, checkPixelsValid, putPixelInData
)where

import Structures (Pixel(..))
import Utils (imSureItsAnInt, splitLines, splitWords)
import Text.Read (readMaybe)
import Data.Maybe
import System.Exit (exitWith, ExitCode (ExitFailure))

defaultPixel :: Pixel
defaultPixel = (Pixel {point = (-1, -1),
    color = (-1 , -1, -1)})

readInt :: String -> Float
readInt str
    | isNothing (readMaybe str :: Maybe Int) = -1
    | otherwise = fromIntegral (read str :: Int)

readShort :: String -> Float
readShort str
    | isNothing (readMaybe str :: Maybe Int) = -1
    | (read str :: Int) > 255 = -1
    | (read str :: Int) < 0 = -1
    | otherwise = fromIntegral (read str :: Int)

replaceBySpace :: String -> String
replaceBySpace [] = []
replaceBySpace (x:xs) = if x == ',' || x == '(' || x == ')'
    then ' ' : replaceBySpace xs;
    else x : replaceBySpace xs;

storePixel :: [String] -> [Pixel] -> [Pixel]
storePixel (v:w:x:y:z:xs) pixel =
    [Pixel {point = (readInt v, readInt w),
    color = (readShort x, readShort y, readShort z)}]
storePixel _ _ = []

putPixelInData :: [Pixel] -> [[String]] -> [Pixel]
putPixelInData pixel [] = [defaultPixel]
putPixelInData pixel [x] = pixel ++ storePixel x pixel
putPixelInData pixel (x:xs) = pixel ++ putPixelInData (storePixel x pixel) xs

checkPixelsValid :: [Pixel] -> IO()
checkPixelsValid [] = return ()
checkPixelsValid ((Pixel (-1, _) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel (_, -1) _):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (-1, _, _)):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, -1 , _)):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid ((Pixel _ (_, _, -1 )):nextPixel) = exitWith (ExitFailure 84)
checkPixelsValid (_:nextPixel) = checkPixelsValid nextPixel
