-- my solution for this exercise
import Data.List
  
findEvenIndex :: [Int] -> Int 
findEvenIndex [] = 0
findEvenIndex lst = case produce lst of
                      Nothing -> -1
                      Just x -> x

produce :: [Int] -> Maybe Int
produce ls@(x:xs) = let sumLst = sumple ls
                        ftLst = zipWith (-) sumLst ls
                        resiLst = map (sum ls -) sumLst in
                      findIndex (\(x,y) -> x == y) (zipWith (,) ftLst resiLst)
  
sumple :: [Int] -> [Int]
sumple lst = head lst : sumples lst  

sumples :: [Int] -> [Int]
sumples [x] = []
sumples (x:xs) = let newx = x + head xs in
                   newx : sumples (newx : tail xs)
        
-- some other solutions
-- 1. Applicative
import Control.Applicative ((<$>), (<*>))
import Data.List (elemIndex)
import Data.Maybe (fromMaybe)

findEvenIndex :: [Int] -> Int
findEvenIndex = fromMaybe (-1) . elemIndex True .
  (zipWith (==) <$> scanl1 (+) <*> scanr1 (+))

-- 2. imperative
findEvenIndex :: [Int] -> Int
findEvenIndex (a:rr) = go 0 a 0 (sum rr) rr
    where go ix p l r ar
              | l == r = ix
              | null ar = -1
              | (a:as) <- ar = go (ix+1) a (p+l) (r-a) as

-- 3. simiar to mine, but much better
import Data.List (findIndex)

findEvenIndex :: [Int] -> Int
findEvenIndex arr = maybe (-1) id $ findIndex (\(a,b,_) -> a == b) $ pairs
  where pairs = scanr (\x (a,b,c) -> (a + c, b - x, x)) (0, sum arr, 0) arr
