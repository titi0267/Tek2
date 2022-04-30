module Algo
    (
        prepareAlgo
    )where

import Structures (Pixel(..), Flags(..))
import Utils (imSureItsAnInt)

arePixelsEqual :: Pixel -> Pixel -> Bool
arePixelsEqual (Pixel (a1, a2) (a3, a4, a5)) (Pixel (b1, b2) (b3, b4, b5)) =
    a1 == b1 && a2 == b2 && a3 == b3 && a4 == b4 && a5 == b5

calcDistance :: Pixel -> Pixel -> Float
calcDistance (Pixel _ (r1, g1, b1)) (Pixel _ (r2, g2, b2)) =
    sqrt(fromIntegral ((r1 - r2)^2 + (g1 - g2)^2 + (b1 - b2)^2))

checkPixelInArray :: Pixel -> [Pixel] -> Bool
checkPixelInArray pixel [] = False
checkPixelInArray pixel (pixelItem: nextPixelItem)
    | arePixelsEqual pixel pixelItem = True
    | otherwise = checkPixelInArray pixel nextPixelItem

clearAlreadySortedPixels :: [Pixel] -> [Pixel] -> [Pixel] -> [Pixel]
clearAlreadySortedPixels [] _ acc = acc
clearAlreadySortedPixels (pixel:nextPixel) sortedPixels acc
    | checkPixelInArray pixel sortedPixels =
        clearAlreadySortedPixels nextPixel sortedPixels acc
    | otherwise =
        clearAlreadySortedPixels nextPixel sortedPixels (acc ++ [pixel])

isClosestPixel :: Pixel -> [Pixel] -> Pixel -> Pixel -> Bool
isClosestPixel _ [] current best = arePixelsEqual current best
isClosestPixel pixel (head:nextHead) currentHead bestHead
    | calcDistance pixel head < calcDistance pixel bestHead =
        isClosestPixel pixel nextHead currentHead head
    | otherwise = isClosestPixel pixel nextHead currentHead bestHead

getRow :: [Pixel] -> [Pixel] -> Pixel -> [Pixel] -> [Pixel]
getRow [] _ _ acc = acc
getRow (pixel:nextPixel) heads currentHead acc
    | isClosestPixel pixel heads currentHead currentHead =
        getRow nextPixel heads currentHead (acc ++ [pixel])
    | otherwise = getRow nextPixel heads currentHead acc

addInRows :: [Pixel] -> [Pixel] -> [[Pixel]] -> [[Pixel]]
addInRows _ [] acc = acc
addInRows pixel (head: nextHead) acc = addInRows
    (clearAlreadySortedPixels pixel (getRow pixel (head : nextHead) head []) [])
    nextHead
    (acc ++ [ head : getRow pixel (head : nextHead) head []])

getFistArray :: Flags -> [Pixel] -> Int -> [Pixel] -> [[Pixel]]
getFistArray _ [] _ headArray = [headArray]
getFistArray (Flags nbr_color conv path) (pixelTab:nextPixelTab) i acc
    | i < imSureItsAnInt nbr_color = getFistArray (Flags nbr_color conv path)
    nextPixelTab (i + 1) (acc ++ [pixelTab])
    | otherwise = addInRows (pixelTab:nextPixelTab) acc []

prepareAlgo :: Flags -> [Pixel] -> IO()
prepareAlgo flags pixelTab = print (getFistArray flags pixelTab 0 [])
