module Algo
    (
        prepareAlgo
    )where

import Structures (Pixel(..), Flags(..))
import Utils (imSureItsAnInt, imSureItsAnFloat)
import Data.List (genericLength)
import System.Random

arePixelsEqual :: Pixel -> Pixel -> Bool
arePixelsEqual (Pixel (a1, a2) (a3, a4, a5)) (Pixel (b1, b2) (b3, b4, b5)) =
    a1 == b1 && a2 == b2 && a3 == b3 && a4 == b4 && a5 == b5

calcDistance :: Pixel -> Pixel -> Float
calcDistance (Pixel _ (r1, g1, b1)) (Pixel _ (r2, g2, b2)) =
    sqrt((r1 - r2)^2 + (g1 - g2)^2 + (b1 - b2)^2)

getPixelHead :: [Pixel] -> Int -> Int ->
    ([Pixel], [Pixel]) -> ([Pixel], [Pixel])
getPixelHead [] _ _  (front, tab) = (front, tab)
getPixelHead (pixel:nextPixel) index i (front, tab)
    | index == i = getPixelHead nextPixel index (i + 1) (pixel : front, tab)
    | otherwise = getPixelHead nextPixel index (i + 1) (front, pixel : tab)

getRandomHeads :: [Int] -> ([Pixel], [Pixel]) -> ([Pixel], [Pixel])
getRandomHeads [] (front, tab) = (front, tab)
getRandomHeads (index:nextIndex) (front, tab) =
    getRandomHeads nextIndex ((head first) : front, second)
    where (first, second) = getPixelHead tab index 0 ([], [])

isClosestPixel :: Pixel -> [Pixel] -> Pixel -> Pixel -> Bool
isClosestPixel _ [] current best = arePixelsEqual current best
isClosestPixel pixel (head:nextHead) currentHead bestHead
    | calcDistance pixel head < calcDistance pixel bestHead =
        isClosestPixel pixel nextHead currentHead head
    | otherwise = isClosestPixel pixel nextHead currentHead bestHead

getRow :: [Pixel] -> [Pixel] -> Pixel -> ([Pixel], [Pixel]) -> ([Pixel], [Pixel])
getRow [] _ _ acc = acc
getRow (pixel:nextPixel) heads currentHead (acc, other)
    | isClosestPixel pixel heads currentHead currentHead =
        getRow nextPixel heads currentHead (pixel : acc, other)
    | otherwise = getRow nextPixel heads currentHead (acc, pixel : other)

addInRows :: [Pixel] -> [Pixel] -> [[Pixel]] -> [[Pixel]]
addInRows _ [] acc = acc
addInRows pixel (head: nextHead) acc =
    addInRows second nextHead ((head : first) : acc)
    where (first, second) = getRow pixel (head : nextHead) head ([], [])

getFistArray :: ([Pixel], [Pixel]) -> [[Pixel]]
getFistArray (front, tab) = addInRows tab front []

getColor :: Int -> Pixel -> Float
getColor 1 (Pixel _ (r, g, b)) = r
getColor 2 (Pixel _ (r, g, b)) = g
getColor 3 (Pixel _ (r, g, b)) = b
getColor _ _= 0

getMidsOfRaw :: [Pixel] -> Pixel
getMidsOfRaw tab =
    Pixel (0, 0) (sum (map (getColor 1) tab) / fromIntegral (length tab),
    sum (map (getColor 2) tab) / fromIntegral (length tab),
    sum (map (getColor 3) tab) / fromIntegral (length tab))

getMidsOfAll :: [[Pixel]] -> [Pixel] -> [Pixel]
getMidsOfAll pixelTab acc = foldl (\ acc pixelTab ->
    getMidsOfRaw pixelTab : acc) acc pixelTab

hasConverged :: [[Pixel]] -> Maybe Float -> Bool
hasConverged [] conv = True
hasConverged ((secondHead:nextHead):secondNext) conv
    | calcDistance secondHead (getMidsOfRaw (secondHead:nextHead))
    <= imSureItsAnFloat conv =
        hasConverged secondNext conv
    | otherwise = False
hasConverged _ conv = False

checkConverged :: [[Pixel]] -> Maybe Float -> (Bool, [[Pixel]])
checkConverged newTab conv
    | hasConverged newTab conv
        = (True, newTab)
    | otherwise = (False, newTab)

printRaw :: [Pixel] -> Bool -> IO()
printRaw [] _ = return ()
printRaw ((Pixel _ (r, g, b)):nextPixel) True =
    putStrLn "--" >> print (round r, round g, round b) >> putStrLn "-"
    >> printRaw nextPixel False
printRaw (Pixel (x, y) (r, g, b):nextPixel) isFirst =
    (putStr . show $ (round x, round y)) >> putStr " "  >>
    print (round r, round g, round b) >> printRaw nextPixel isFirst

printResult :: [[Pixel]] -> IO()
printResult
    = foldr (\ pixelTab -> (>>) (printRaw pixelTab True)) (return ())

getRandomIndexes :: Int -> Int -> [IO Int] -> IO [Int]
getRandomIndexes 0 _ acc = sequence (reverse acc)
getRandomIndexes k len acc =
    getRandomIndexes (k - 1) (len - 1) (randomRIO(0, len) : acc)

algoLoop :: Maybe Float -> [Pixel] -> [[Pixel]] -> IO()
algoLoop conv basePixels sortedPixels =
    case checkConverged
        (addInRows basePixels (getMidsOfAll sortedPixels []) []) conv of
        (True, tab) -> printResult tab
        (False, tab) -> algoLoop conv basePixels tab

prepareAlgo :: Flags -> [Pixel] -> IO()
prepareAlgo (Flags nbr_color conv path) pixelTab = do
    randomNbrs <-
        (getRandomIndexes (imSureItsAnInt nbr_color)
        ((length pixelTab) - 1) [])
    algoLoop conv pixelTab
        (getFistArray (getRandomHeads randomNbrs ([], pixelTab)))