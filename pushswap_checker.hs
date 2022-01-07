import System.Directory.Internal.Prelude (getArgs)

main :: IO ()
main = do
    args <- getArgs
    print args