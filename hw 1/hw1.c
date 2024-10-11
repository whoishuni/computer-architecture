{\rtf1\ansi\ansicpg950\cocoartf2818
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <stdio.h>\
#include <stdlib.h>\
\
#define MAX_NODES 6400000 \
\
typedef struct TrieNode \{\
    int next[2];\
\} TrieNode;\
\
TrieNode trie[MAX_NODES];\
int nodeCount;\
\
void insert(int num, int maxBit) \{\
    int curr = 0; // root node index\
    for (int i = maxBit; i >= 0; i--) \{\
        int bit = (num >> i) & 1;\
        if (!trie[curr].next[bit]) \{\
            trie[nodeCount].next[0] = trie[nodeCount].next[1] = 0;\
            trie[curr].next[bit] = nodeCount++;\
        \}\
        curr = trie[curr].next[bit];\
    \}\
\}\
\
int searchMaximumXOR(int num, int maxBit) \{\
    int curr = 0; // root node index\
    int maxXor = 0;\
    for (int i = maxBit; i >= 0; i--) \{\
        int bit = (num >> i) & 1;\
        int toggledBit = bit ^ 1;\
        if (trie[curr].next[toggledBit]) \{\
            maxXor |= (1 << i);\
            curr = trie[curr].next[toggledBit];\
        \} else \{\
            curr = trie[curr].next[bit];\
        \}\
    \}\
    return maxXor;\
\}\
\
int findMaximumXOR(int* nums, int numsSize)\{\
    if (numsSize < 2)\
        return 0;\
    \
    // Find the maximum number to determine the number of bits needed\
    int maxNum = nums[0];\
    for (int i = 1; i < numsSize; i++) \{\
        if (nums[i] > maxNum)\
            maxNum = nums[i];\
    \}\
\
    // Calculate the maximum bit position\
    int maxBit = 0;\
    while ((maxNum >> maxBit) > 0)\
        maxBit++;\
    maxBit--;\
\
    nodeCount = 1; // reset node count\
    // Initialize the root node\
    trie[0].next[0] = trie[0].next[1] = 0;\
\
    int maxXor = 0;\
\
    insert(nums[0], maxBit);\
\
    for (int i = 1; i < numsSize; i++) \{\
        int num = nums[i];\
        int currentXor = searchMaximumXOR(num, maxBit);\
        if (currentXor > maxXor)\
            maxXor = currentXor;\
        insert(num, maxBit);\
    \}\
\
    return maxXor;\
\}\
}