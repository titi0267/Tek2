module BitPerBit
    ( firstBit, secondBit, thirdBit, fourthBit, fifthBit, sixthBit, seventhBit, eigthBit
    ) where

firstBit :: String -> Int -> String
firstBit [] _ = ""
firstBit ('*':'*':'*':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
firstBit (_:_) x = ""

secondBit :: [Char] -> Int -> String
secondBit [] _ = ""
secondBit ('*':'*':' ':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
secondBit (_:_) x = ""

thirdBit :: [Char] -> Int -> String
thirdBit [] _ = ""
thirdBit ('*':' ':'*':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
thirdBit (_:_) x = ""

fourthBit :: [Char] -> Int -> String
fourthBit [] _ = ""
fourthBit ('*':' ':' ':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
fourthBit (_:_) x = ""

fifthBit :: [Char] -> Int -> String
fifthBit [] _ = ""
fifthBit (' ':'*':'*':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
fifthBit (_:_) x = ""

sixthBit :: [Char] -> Int -> String
sixthBit [] _ = ""
sixthBit (' ':'*':' ':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
sixthBit (_:_) x = ""

seventhBit :: [Char] -> Int -> String
seventhBit [] _ = ""
seventhBit (' ':' ':'*':xs) x =
    case x == 1 of
        True -> "*"
        False -> ""
seventhBit (_:_) x = ""

eigthBit :: [Char] -> Int -> String
eigthBit [] _ = ""
eigthBit (' ':' ':' ':xs) x =
    case x == 1 of
        True -> "*"
        False -> "bim"
eigthBit (_:_) x = ""


