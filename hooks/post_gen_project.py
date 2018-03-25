""" Perform post-generation tasks.

This is executed in the new project directory. Before execution it is rendered 
with the template engine, so it has access to all template variables.

"""
from os import renames
from os.path import join
from shutil import rmtree
from tempfile import mkdtemp
try:
    from urllib.request import urlopen
except ImportError:  
    # Python 2 compatibilty.
    from urllib2 import urlopen
from zipfile import ZipFile


def get_gtest():
    """ Download Google Test from GitHub.
    
    Google recommends that each project maintains its own version of this
    library, compiled with the same flags as the project to avoid potential
    violations of the One-Definition Rule.
    
    """
    download = "https://github.com/google/googletest/archive/{:s}.zip"
    release = "{{ cookiecutter.googletest_release }}"
    print("downloading Google Test ({:s})".format(release))
    if release != "master":
        release = "release-{:s}".format(release)
    libroot = join("test", "lib", "gtest")
    tmproot = mkdtemp()
    try:
        # Extract the downloaded zip file to a temporary directory. ZipFile
        # requires a stream with a seek() method, so the archive must be
        # downloaded to a local file first.
        stream = open(join(tmproot, "gtest.zip"), "w+b")
        print(download.format(release))
        stream.write(urlopen(download.format(release)).read())
        archive = ZipFile(stream, mode="r")
        archive.extractall(tmproot)
        renames(join(tmproot, "googletest-{:s}".format(release)), libroot)
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
