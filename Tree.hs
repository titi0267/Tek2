import Data.IntMap (showTree)
data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show)


