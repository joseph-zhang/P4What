import Data.Char
import Data.String


-- my solution
-- note that the predicate isSpace should not be used, because some characters like '\t','\n'.. can be seen as space
reverseWords :: String -> String
reverseWords s = foldl (++) "" . map reverse . wordslice $ s

-- auxiliary procedures
wordslice :: String -> [String]
wordslice s = case dropTake s  of 
                (ps, "") -> [ps]
                (ps, rs) -> ps : wordslice rs
                
spaceCount :: String -> Int
spaceCount (x:xs)
        | x == ' ' = 1 + spaceCount xs 
        | otherwise = 0

dropCount :: String -> (Int, String)
dropCount s = (spaceCount s, dropWhile (\x -> x == ' ') s)

-- actually, this similar to  => break (not . isSpace) s
-- use break to define a more simplified procedure 
dropTake :: String -> (String, String)
dropTake "" = ("", "")
dropTake all@(x:xs)
        | x == ' ' = break (not . (\x -> x == ' ')) all
        | otherwise = break (\x -> x == ' ') all


-- some other solutions, better than mine

-- note that import Data.Function
reverseWords :: String -> String
reverseWords = concatMap reverse . groupBy ((==) `on` (==' ')) 

reverseWords :: String -> String
reverseWords = concat . map reverse . split (onSublist " ")

reverseWords :: String -> String
reverseWords " " = ""
reverseWords s = unwords $ map reverse $ splitOn " " s