# Helper library for Simba SCons builds.
import os
import sys

sys.path.append( './lib' )
import revlib

VERSION_INC = 'inc/version.h'
TARGET_NAME = 'explore'

env = Environment()

if not env.GetOption( 'clean' ):
    revlib.getRevisionString( os.path.abspath( '.' ), VERSION_INC )

clean_files = []
clean_files.append( '.sconsign.dblite' )
clean_files.append( 'results.xml' )
clean_files.append( 'bin/core' )
clean_files.append( 'doc/html' )
clean_files.append( 'doc/latex' )
clean_files.append( VERSION_INC )
env.Clean( 'default', clean_files )

env.ParseConfig( 'sdl-config --cflags --libs' )
env.Append( CPPFLAGS = [ '-g', '-Wall',  '-Wextra', '-Werror', '-Wfatal-errors' ] )
env.Append( CPPPATH = [ '/usr/include/freetype2' ] )
env.Append( CPPPATH = [ 'inc' ] )
env.Append( LIBS = [ 'GL' ] )
env.Append( LIBS = [ 'ftgl' ] )
env.Append( LIBS = [ 'config' ] )
env.Append( LIBS = [ 'noise' ] )
env.Append( LIBS = [ 'gomp' ] )
env.Append( LIBS = [ 'm' ] )

files = Glob( 'src/*.cpp' )

target_path = 'bin/%s' % TARGET_NAME
env.Program( target = target_path, source = files )

#if not env.GetOption( 'clean' ):
#    doxycmd = 'cd doc; doxygen Doxyfile'
#    os.system( doxycmd )
