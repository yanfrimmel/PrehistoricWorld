{-# OPTIONS_GHC -Wall                 #-}
{-# LANGUAGE ForeignFunctionInterface #-}
 
module AI where

import Foreign.C
 
fibonacci :: Int -> Int
fibonacci n = fibs !! n
    where fibs = 0 : 1 : zipWith (+) fibs (tail fibs)
 
fibonacci_hs :: CInt -> CInt
fibonacci_hs = fromIntegral . fibonacci . fromIntegral
 
foreign export ccall fibonacci_hs :: CInt -> CInt