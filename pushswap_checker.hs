import System.Directory.Internal.Prelude (getArgs)
import Data.Char (isDigit)
import System.Exit
import System.Environment

-- Lib functions

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

readInt :: [ Char ] -> Maybe Int
readInt [] = Nothing
readInt ('-':xs)
    | all isDigit xs = Just ((read xs :: Int) * (-1))
    | otherwise = Nothing
readInt x
    | all isDigit x = Just (read x :: Int)
    | otherwise = Nothing

-- All ops for pushswap

sa :: ([Int],[Int]) -> ([Int],[Int])
sa ([],[]) = ([],[])
sa ([],y) = ([],y)
sa (x,[]) = case myLength x <= 1 of
    True -> (x,[])
    False -> ([myNth x 1] ++ [myNth x 0] ++ myDrop 2 x,[])
sa (x,y) = case myLength x <= 1 of
    True -> (x,y)
    False -> ([myNth x 1] ++ [myNth x 0] ++ myDrop 2 x, y)

sb :: ([Int],[Int]) -> ([Int],[Int])
sb ([],[]) = ([],[])
sb (x,[]) = (x,[])
sb ([],y) = case myLength y <= 1 of 
    True -> ([],y)
    False -> ([],[myNth y 1] ++ [myNth y 0] ++ myDrop 2 y)
sb (x,y) = case myLength y <= 1 of
    True -> (x,y)
    False -> (x, [myNth y 1] ++ [myNth y 0] ++ myDrop 2 y)

sc :: ([Int], [Int]) -> ([Int], [Int])
sc ([],[]) = ([],[])
sc ([], b) = ([], mySnd $ sb ([],b))
sc (a, []) = (myFst $ sa (a, []), [])
sc (a,b) =  (myFst $ sa (a, b),mySnd $ sb (a, b))

pa :: ([Int], [Int]) -> ([Int], [Int])
pa ([],[]) = ([],[])
pa ([],y:ys) = case myLength (y:ys) == 0 of
    True -> ([],y:ys)
    False -> ([y],myDrop 1 [y] ++ ys)
pa (x,[]) = (x,[])
pa (x,y:ys) = case myLength (y:ys) == 0 of
    True -> (x,y:ys)
    False -> (y : x,myDrop 1 [y] ++ ys)

pb :: ([Int], [Int]) -> ([Int], [Int])
pb ([],[]) = ([],[])
pb ([],y) = ([],y)
pb (x:xs,[]) = case myLength (x:xs) == 0 of
    True -> (x:xs,[])
    False -> (myDrop 1 [x] ++ xs, [x])
pb (x:xs,y) = case myLength (x:xs) == 0 of
    True -> (x:xs,y)
    False -> (myDrop 1 [x] ++ xs, x : y)

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

-- From String to list of String parsed with spaces

putStringInTab :: String -> [String]
putStringInTab = words

--Parse ops list

putListInStr :: [String] -> Bool
putListInStr [] = True
putListInStr (x:xs)
    | putListInStr xs = errorHandling x
    | otherwise = False

-- error Handling for echo command

errorHandlingR :: String -> Bool 
errorHandlingR "ra" = True
errorHandlingR "rb" = True
errorHandlingR "rr" = True
errorHandlingR "rra" = True
errorHandlingR "rrb" = True
errorHandlingR "rrr" = True
errorHandlingR _ = False

errorHandling :: String -> Bool
errorHandling str = case str of
        "sa" -> True
        "sb" -> True
        "sc" -> True
        "pa" -> True
        "pb" -> True
        _ -> errorHandlingR str

--Error handling for pushswap_checker args

intOnly :: [String] -> Bool
intOnly [] = True
intOnly (x:xs) = case readInt x of
    Nothing -> False
    Just x -> intOnly xs

--Parse echo command & call ops

chooseOpR :: String -> ([Int],[Int]) -> ([Int],[Int])
chooseOpR "ra" (x,y) = ra (x,y)
chooseOpR "rb" (x,y) = rb (x,y)
chooseOpR "rr" (x,y) = rr (x,y)
chooseOpR "rra" (x,y) = rra (x,y)
chooseOpR "rrb" (x,y) = rrb (x,y)
chooseOpR "rrr"  (x,y) = rrr (x,y)
chooseOpR _ (x,y) = ([],[])

chooseOp :: String -> ([Int],[Int]) -> ([Int],[Int])
chooseOp str (x,y) = case str of
        "sa" -> sa (x,y)
        "sb" -> sb (x,y)
        "sc" -> sc (x,y)
        "pa" -> pa (x,y)
        "pb" -> pb (x,y)
        _ -> chooseOpR str (x,y)

--Loop on list of String from echo command

lpOnStr :: [String] -> ([Int], [Int]) -> ([Int], [Int])
lpOnStr [] list = list
lpOnStr (x:xs) ([],b) = lpOnStr xs (chooseOp x ([],b))
lpOnStr (x:xs) (a,[]) = lpOnStr xs (chooseOp x (a,[]))
lpOnStr (x:xs) (a,b) = lpOnStr xs (chooseOp x (a,b))

--Cast pushswap_checker args from String list to Int list

stringToInt :: [String] -> [Int]
stringToInt =  map (read::String->Int)

--Loop on first list to check if sorted

sorted :: Ord a => ([a],[a]) -> Bool
sorted ([],[]) = True
sorted ([],y) = False
sorted ([x],[]) = True
sorted ([x],y) = False
sorted ((x:y:xs),z) = case x <= y of
    True -> sorted ((y:xs),z)
    False -> False

--Main function, ErrorHandling + do ops + check if first list sorted

main :: IO ()
main = do
    args <- getArgs
    line <- getLine
    case (putListInStr (putStringInTab line)) && intOnly args of
        True -> pure ()
        False -> exitWith (ExitFailure 84)
    case sorted (lpOnStr (putStringInTab line) (stringToInt args,[])) of
        True -> putStrLn "OK"
        False -> (putStr $ "KO: ") >>
                (print $ lpOnStr (putStringInTab line) (stringToInt args,[]))
