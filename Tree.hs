data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show)

addInTree :: Ord a => a -> Tree a -> Tree a
addInTree a Empty = (Node Empty a Empty)
addInTree a (Node left b right) =  case a < b of
    True -> (Node (addInTree a left) b right)
    False -> (Node left b (addInTree a right))

class Functor f where
    fmap :: f -> Tree a -> Tree a

