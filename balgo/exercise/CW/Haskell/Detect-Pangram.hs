import Data.Char
import Data.List

-- my solution 
isPangram :: String -> Bool
isPangram str = (==) 26 $ length . nub . (map toLower) $ (filter isLetter str) 

-- clever one
isPangram :: String -> Bool
isPangram str = null $ ['a'..'z'] \\ (map toLower str)

-- similar one 
isPangram :: String -> Bool
isPangram str = all (`elem` (map toLower str)) ['a'..'z']