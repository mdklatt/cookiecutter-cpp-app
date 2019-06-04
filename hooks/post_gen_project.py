""" Perform post-generation tasks.

This is executed in the new project directory. Before execution it is rendered 
with the template engine, so it has access to all template variables.

"""
from pathlib import Path
from tempfile import TemporaryDirectory
from urllib.request import urlopen
from zipfile import ZipFile


def get_googletest():
    """ Download Google Test from GitHub.
    
    Google recommends that each project maintains its own version of this
    library, compiled with the same flags as the project to avoid potential
    violations of the One-Definition Rule.
    
    """
    release = "{{ cookiecutter.googletest_release }}"
    download = f"https://github.com/google/googletest/archive/{release:s}.zip"
    print(f"downloading Google Test ({release:s})")
    if release != "master":
        release = f"release-{release:s}"
    libroot =  Path("test", "lib", "gtest")
    libroot.mkdir(parents=True, exist_ok=True)
    with TemporaryDirectory() as tmpdir:
        # Extract the downloaded zip file to a temporary directory. ZipFile
        # requires a stream with a seek() method, so the archive must be
        # downloaded to a local file first.
        file = Path(tmpdir, "googletest.zip")
        file.write_bytes(urlopen(download).read())
        archive = ZipFile(file.open("r+b"), mode="r")
        archive.extractall(tmpdir)
        Path(tmpdir, f"googletest-{release:s}").replace(libroot)
    return


def main() -> int:
    """ Execute all tasks. 
    
    """
    get_googletest()
    return 0


# Make the script executable from the command line.

if __name__ == "__main__":
    raise SystemExit(main())
