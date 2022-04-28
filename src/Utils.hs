module Utils
    (
        checkLength, getFileContent, imSureItsAnInt, printFile
    )where
import System.Exit

checkLength :: Int -> IO ()
checkLength size
    | size == 6 = return ()
    | otherwise = exitWith (ExitFailure 84)

getFileContent :: String -> IO String
getFileContent file = do
    content <- readFile file
    return content

printFile :: Int -> Int -> String -> IO()
printFile nbr_color converge file = do
    content <- readFile file
    putStrLn content

imSureItsAnInt :: Maybe Int -> Int
imSureItsAnInt Nothing = -1
imSureItsAnInt (Just i) = i
