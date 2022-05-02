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
    point :: (Float ,Float),
    color :: (Float, Float, Float )
} deriving (Show)