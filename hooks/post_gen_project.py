""" Perform post-generation tasks.

This is executed in the new project directory. Before execution it is rendered 
with the template engine, so it has access to all template variables.

"""
from __future__ import print_function

from os import renames
from os.path import join
from shutil import rmtree
from tempfile import mkdtemp
from urllib2 import urlopen
from zipfile import ZipFile


def get_gtest():
    """ Download the Google Test latest release from GitHub.
    
    """
    print("downloading latest Google Test release")
    url = "https://github.com/google/googletest/archive/master.zip"
    libroot = join("test", "lib", "gtest")
    tmproot = mkdtemp()
    try:
        # Extract the downloaded zip file to a temporary directory. ZipFile
        # requires a stream with a seek() method, so the archive must be
        # downloaded to a local file first.
        stream = open(join(tmproot, "gtest.zip"), "w+b")
        stream.write(urlopen(url).read())
        archive = ZipFile(stream, mode="r")
        archive.extractall(tmproot)
        ziproot = join(tmproot, "googletest-master", "googletest")
        renames(ziproot, libroot)
    finally:
        rmtree(tmproot)
    return


def main():
    """ Execute all tasks. 
    
    """
    get_gtest()
    return 0


# Make the script executable from the command line.

if __name__ == "__main__":
    raise SystemExit(main())
