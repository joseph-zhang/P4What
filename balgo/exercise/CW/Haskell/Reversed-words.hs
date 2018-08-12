-- note that this problem is different from reverse words (another kata)

-- my solution
reverseWords :: String -> String
reverseWords = unwords . reverse . words