module Structures
(
    Flags(..), Pixel(..)
)where

data Flags = Flags {
    nbr_color :: Maybe Int,
    convergence :: Maybe Float,
    path :: String
} deriving (Show)

data Pixel = Pixel {
    point :: (Int, Int),
    color :: (Int, Int, Int)
} deriving (Show)