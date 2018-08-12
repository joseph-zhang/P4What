import qualified Data.Text as T 
import qualified Data.List as L
import Data.Char

-- my solution
minus a b = a - b 

revRot :: [Char] -> Int -> [Char]
revRot [] _ = ""
revRot strng sz
    | sz<= 0 = ""
    | otherwise = concat $ map (\x -> if sumCheck x then reverse x else rotate x) (gene strng sz)

gene :: String -> Int -> [String]
gene s n = let tsl = (map T.unpack) . (T.chunksOf n). T.pack $ s in
    if ((length . last $ tsl) == n) then tsl else (init tsl) 
                   
sumCheck :: String -> Bool
sumCheck = ((==0) . (`mod` 2)) . sum . (map $ (^3) . (`minus` 48) . ord)

rotate :: String -> String
rotate [] = []
rotate s = (++ (return . L.head $ s)) . L.tail $ s


-- a similar one
revRot :: String -> Int -> String
revRot [] _ = ""
revRot strng sz
  | sz <= 0           = ""
  | length strng < sz = ""
  | otherwise         = dothing ++ revRot (drop sz strng) sz
  where
    interest = take sz strng
    readChar = map (\ x -> read [x])
    isDiv xs = even (sum (map (^3) (readChar xs)))
    shift (x:xs) = xs ++ [x]
    dothing
      | isDiv interest = reverse interest
      | otherwise      = shift interest