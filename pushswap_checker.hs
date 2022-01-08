import System.Directory.Internal.Prelude (getArgs)
import Data.Char (isDigit)
import System.Exit
import System.Environment

myIsNeg :: Int -> Bool
myIsNeg x
    | x < 0 = True
    | otherwise = False

myLength :: [ a ] -> Int
myLength [] = 0
myLength (_:xs) = 1 + myLength xs

myNth :: [ a ] -> Int -> a
myNth [] y = error "empty list"
myNth (x:xs) y
    | y > myLength (x:xs) = error "index too large"
    | myIsNeg y = error "Index is negative"
myNth (x:xs) 0 = x
myNth (x:xs) y = myNth xs (y-1)

myDrop :: Int -> [ a ] -> [ a ]
myDrop y [] = error "empty list"
myDrop y (x:xs)
    | myIsNeg y = error "N is negative"
    | y >= myLength (x:xs) = []
myDrop 0 (x:xs) = x:xs
myDrop y (x:xs) = myDrop (y-1) xs

myFst :: (a , b) -> a
myFst (a,b) = a

mySnd :: (a , b) -> b
mySnd (a,b) = b

sa :: [ Int ] -> [ Int ]
sa [] = []
sa x = [myNth x 1] ++ [myNth x 0] ++ myDrop 2 x

sb :: [ Int ] -> [ Int ]
sb [] = []
sb x = [myNth x 1] ++ [myNth x 0] ++ myDrop 2 x
-- Concat second + first + (remove first & second)

sc :: ([Int], [Int]) -> ([Int], [Int])
sc ([],[]) = ([],[])
sc ([], b) = ([], sb $ mySnd ([], b))
sc (a, []) = (sa $ myFst (a, []) , [])
sc (a,b) =  ( sa $ myFst (a, b) , sb $ mySnd (a, b) )

pa :: ([Int], [Int]) -> ([Int], [Int])
pa ([],[]) = ([],[])
pa ([],y:ys) = ([y],myDrop 1 [y] ++ ys)
pa (x,[]) = (x,[])
pa (x,y:ys) = (y : x,myDrop 1 [y] ++ ys)

pb :: ([Int], [Int]) -> ([Int], [Int])
pb ([],[]) = ([],[])
pb ([],y) = ([],y)
pb (x:xs,[]) = (myDrop 1 [x] ++ xs, [x])
pb (x:xs,y) = (myDrop 1 [x] ++ xs, x : y)

ra :: ([Int], [Int]) -> ([Int], [Int])
ra ([],[]) = ([],[])
ra ([],y) = ([],y)
ra (x,[]) = (myDrop 1 x ++ [myNth x 0],[])
ra (x,y) = (myDrop 1 x ++ [myNth x 0],y)

rb :: ([Int], [Int]) -> ([Int], [Int])
rb ([],[]) = ([],[])
rb ([],y) = ([],myDrop 1 y ++ [myNth y 0])
rb (x,[]) = (x,[])
rb (x,y) = (x, myDrop 1 y ++ [myNth y 0])


rr :: ([Int], [Int]) -> ([Int], [Int])
rr ([],[]) = ([],[])
rr ([],y) = ([],mySnd $ rb ([],y))
rr (x,[]) = (myFst $ ra (x,[]),[])
rr (x,y) = (myFst $ ra (x,y),mySnd $ rb (x,y))

rra :: ([Int], [Int]) -> ([Int], [Int])
rra ([],[]) = ([],[])
rra ([],y) = ([],y)
rra (x,[]) = ([myNth x (myLength x-1)] ++ take (myLength x-1) x,[])
rra (x,y) = ([myNth x (myLength x-1)] ++ take (myLength x-1) x,y)

rrb :: ([Int], [Int]) -> ([Int], [Int])
rrb ([],[]) = ([],[])
rrb ([],y) = ([],[myNth y (myLength y-1)] ++ take (myLength y-1) y)
rrb (x,[]) = (x,[])
rrb (x,y) = (x,[myNth y (myLength y-1)] ++ take (myLength y-1) y)

rrr :: ([Int], [Int]) -> ([Int], [Int])
rrr ([],[]) = ([],[])
rrr ([],y) = ([],[myNth y (myLength y-1)] ++ take (myLength y-1) y)
rrr (x,[]) = ([myNth x (myLength x-1)] ++ take (myLength x-1) x,[])
rrr (x,y) = ([myNth x (myLength x-1)] ++ take (myLength x-1) x,
    [myNth y (myLength y-1)] ++ take (myLength y-1) y)

putStringInTab :: String -> [String]
putStringInTab = words

loopOnString :: [String] -> String
loopOnString [] = []
loopOnString (x:xs) = case x == [] of
    True -> []
    False -> loopOnString 
        --"sa" -> 1
        --"sb" -> 2
        --"sc" -> 3
        --"pa" -> 4
        --"pb" -> 5
        --"ra" -> 6
        --"rb" -> 7
        --"rr" -> 8
        --"rra" -> 9
        --"rrb" -> 10
        --"rrr" -> 11
        --_ -> 0

main :: IO ()
main = do
    args <- getArgs
    line <- getLine
    print line
    case (loopOnString (putStringInTab line)) of
        "sa" -> print "sa"
        _ -> print "rien"
        --0 -> print "Nop"
        --1 -> 
        --9 -> print "9"
        --3 -> print "3"
        --_ -> print "Nop"