tribonacci :: Num a => (a, a, a) -> Int -> [a]
tribonacci _ 0 = []
tribonacci (i,j,k) n = take n f where
                 f = i : j : k : zipWith ( + ) f  ( zipWith ( + ) ( tail f) (tail ( tail f )))

-- simple recursively solution
tribonacci :: Num a => (a, a, a) -> Int -> [a]
tribonacci _ 0 = []
tribonacci (a, b, c) n = a : tribonacci (b, c, a+b+c) (n-1)

-- better than the first one
tribonacci :: Num a => (a, a, a) -> Int -> [a]
tribonacci (a, b, c) n = take n tribs
    where tribs = [a, b, c] ++ zipWith3 (\x y z -> x + y + z) tribs (tail tribs) (tail $ tail tribs)