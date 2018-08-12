#!/usr/bin/python
# -*- coding: utf-8 -*-

# Aho-Corasick automata let us match multiple patterns in a given text.

# implementation of Aho-Corasick automata in python language.
# The idea of this data structure is easy to understand,
# to describe it in a word, Aho-Corasick is just trie \times KMP

# the idea of KMP has been talked in previous sections,
# and the trie has also been implemented in both dynamic and static method in Cpp.

# In fact, The implementation in python is explicit,
# Python is a language without pointer, and we need not to manage memory by hand.

# The idea of AC automata can be splited as three stpes:
# 1). Read patterns to construct trie (succ paths);
# 2). Use BFS to construct failure paths (failure function);
# 3). go along with succ/failure paths to search multiple patterns in a given text.

# use __all__ to provide what we want.
__all__ = ["AC"]

class Node(object):
    def __init__(self):
        self.nexts = {} # a map to restore trie
        self.fail = None
        self.endOfWord = False

class AC(object):
    def __init__(self):
        self.root = Node()

    # insert a word in trie
    def insert(self, word):
        # current node
        cur = self.root
        for c in word:
            if not cur.nexts.has_key(c):
                cur.nexts[c] = Node()
            cur = cur.nexts[c]
        cur.endOfWord = True

    # build AC automata (failure paths)
    def BFS_build(self):
        que = []
        que.append(self.root)

        # isempty :: lst -> Bool
        isempty = lambda x : (len(x) == 0)

        while not isempty(que):
            tmp = que.pop()
            for k, v in tmp.nexts.items():
                if tmp == self.root:
                    tmp.nexts[k].fail = self.root
                else:
                    p = tmp.fail
                    while p is not None:
                        if p.nexts.has_key(k):
                            tmp.nexts[k].fail = p.nexts[k]
                            break
                        p = p.fail
                    if p is None:
                        tmp.nexts[k].fail = self.root
                que.append(tmp.nexts[k])

    # matching
    def match(self, text):
        cur = self.root
        res = []
        startIndex = 0
        pos = 0

        while pos < len(text):
            alph = text[pos]

            while not cur.nexts.has_key(alph) and cur != self.root:
                cur = cur.fail

            if cur.nexts.has_key(alph):
                if cur == self.root:
                    startIndex = pos
                cur = cur.nexts[alph]
            else:
                cur = self.root

            if cur.endOfWord:
                res.append((startIndex, pos))

            pos = pos + 1
        return res

if __name__ == '__main__':
    ac = AC()
    text = raw_input("input text: ")
    patterns =  raw_input("input patterns: ").split(" ")
    for p in patterns:
        ac.insert(p)

    ac.BFS_build()
    result = ac.match(text)
    if len(result) == 0:
        print 'no pattern matched'
    else:
        print result
        print 'matched %d times.' %len(result)
        print text
        for (begin, end) in result:
            print " "*begin + text[begin:end+1] + ""*(len(text) - end)
