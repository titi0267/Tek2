module Utils
    (
        checkLength, imSureItsAnInt, printFile, splitWords, splitLines
    )where
import System.Exit

checkLength :: Int -> IO ()
checkLength size
    | size == 6 = return ()
    | otherwise = exitWith (ExitFailure 84)

printFile :: Int -> Int -> String -> IO()
printFile nbr_color converge file = do
    content <- readFile file
    putStrLn content

imSureItsAnInt :: Maybe Int -> Int
imSureItsAnInt Nothing = -1
imSureItsAnInt (Just i) = i

splitWords :: String -> [String]
splitWords pixel = words pixel

splitLines :: String -> [String]
splitLines content = lines content
