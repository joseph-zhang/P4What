-- my solution
find_shortest :: String -> Integer
find_shortest s = toInteger $ minimum $ (map length) $ words s

-- another one
find_shortest :: String -> Integer
find_shortest = fromIntegral . minimum . map length . words