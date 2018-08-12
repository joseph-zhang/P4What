-- | Takes a non-empty list and returns
--   both maximum and minimum value
minMax :: (Ord a) => [a] -> (a, a)
minMax xs = (minimum xs, maximum xs)

-- here is an amazing one
minMax' :: (Ord a) => [a] -> (a, a)
minMax' xs = liftA2 (,) minimum maximum