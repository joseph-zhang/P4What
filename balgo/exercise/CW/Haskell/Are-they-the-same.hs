import Data.List (sort)

comp :: [Integer] -> [Integer] -> Bool
comp as bs = sort (map (^2) as) == sort bs