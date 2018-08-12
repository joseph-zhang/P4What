-- Let \phi = (1+\sqrt{5})/2 (golden ratio), the fibnumber F(n) is asymptotic to \round\phi^n/\sqrt{5} 

-- | Returns a pair of consecutive Fibonacci numbers a b,
--   where (a*b) is equal to the input, or proofs that the
--   number isn't a product of two consecutive Fibonacci 
--   numbers.

-- my solution 
productFib :: Integer -> (Integer, Integer, Bool)
productFib n
    | j1*j2 == n = (j1,j2,True)
    | otherwise = (j1,j2,False)
    where (j1,j2,_) = head . (dropWhile (\(x,y,z) -> z == False)) $ (map pjudge (tups n))

f :: [Integer]
f = 1 : 1 : zipWith (+) f (tail f)

tups ::(Integral c) =>  c -> [(Integer, Integer, c)]
tups n = zip3 f (tail f) (repeat n)

pjudge ::(Integer,Integer,Integer) -> (Integer,Integer,Bool)
pjudge (a,b,n)
    | a * b >= n = (a,b,True)
    | otherwise = (a,b,False)


-- best one, easy to understand, recursion
productFib :: Integer -> (Integer, Integer, Bool)
productFib n = go 0 1 n
  where
    go a b c
        | a * b >= c = (a, b, a * b == c)
        | otherwise = go b (a + b) c

-- some other solutions similar to mine, but some more keywords or mechanisms are used
productFib :: Integer -> (Integer, Integer, Bool)
productFib n = walk fibs
  where fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
        walk (curr : rest@(next : _))
          | curr * next >= n = (curr, next, curr * next == n)
          | otherwise        = walk rest
          
          
productFib :: Integer -> (Integer, Integer, Bool)
productFib n = (a, b, a * b == n)
where
    (a, b) = head . dropWhile ((< n) . uncurry (*)) . zip fibs $ tail fibs

