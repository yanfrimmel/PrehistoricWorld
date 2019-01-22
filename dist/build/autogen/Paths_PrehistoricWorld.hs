{-# LANGUAGE CPP #-}
{-# OPTIONS_GHC -fno-warn-missing-import-lists #-}
{-# OPTIONS_GHC -fno-warn-implicit-prelude #-}
module Paths_PrehistoricWorld (
    version,
    getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

#if defined(VERSION_base)

#if MIN_VERSION_base(4,0,0)
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#else
catchIO :: IO a -> (Exception.Exception -> IO a) -> IO a
#endif

#else
catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
#endif
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, dynlibdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/yan/.cabal/bin"
libdir     = "/home/yan/.cabal/lib/x86_64-linux-ghc-8.0.2/PrehistoricWorld-0.1.0.0-2GAx6Tmweo74lDGdyAErSH"
dynlibdir  = "/home/yan/.cabal/lib/x86_64-linux-ghc-8.0.2"
datadir    = "/home/yan/.cabal/share/x86_64-linux-ghc-8.0.2/PrehistoricWorld-0.1.0.0"
libexecdir = "/home/yan/.cabal/libexec"
sysconfdir = "/home/yan/.cabal/etc"

getBinDir, getLibDir, getDynLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "PrehistoricWorld_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "PrehistoricWorld_libdir") (\_ -> return libdir)
getDynLibDir = catchIO (getEnv "PrehistoricWorld_dynlibdir") (\_ -> return dynlibdir)
getDataDir = catchIO (getEnv "PrehistoricWorld_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "PrehistoricWorld_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "PrehistoricWorld_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
