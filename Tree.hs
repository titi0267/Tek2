data Tree a = Empty | Node (Tree a) a (Tree a)
    deriving (Show)

addInTree :: Ord a => a -> Tree a -> Tree a
addInTree a Empty = (Node Empty a Empty)
addInTree a (Node left b right) =  case a < b of
    True -> (Node (addInTree a left) b right)
    False -> (Node left b (addInTree a right))

instance Functor Tree where
    fmap f Empty = Empty
    fmap f (Node left a right) = Node (fmap f left) (f a) (fmap f right)

listToTree :: Ord a => [a] -> Tree a
listToTree [] = Empty
listToTree x = foldr addInTree Empty x

treeToList :: Tree a -> [a]
treeToList Empty = []
treeToList (Node left a right) = treeToList left ++ [a] ++ treeToList right


