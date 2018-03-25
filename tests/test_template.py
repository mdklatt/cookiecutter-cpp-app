""" Test the cpp-app Cookiecutter template.

A template project is created in a temporary directory, the application and its
test suite are built, and both are executed.

"""
from contextlib import contextmanager
from json import load
from os import chdir
from os import getcwd
from os.path import abspath
from os.path import dirname
from os.path import join
from shlex import split
from shutil import rmtree
from subprocess import check_call
from tempfile import mkdtemp

from cookiecutter.main import cookiecutter


def main():
    """ Execute the test.
    
    """
    @contextmanager
    def tmpdir():
        """ Enter a self-deleting temporary directory. """
        cwd = getcwd()
        tmp = mkdtemp()
        try:
            chdir(tmp)
            yield tmp
        finally:
            rmtree(tmp)
            chdir(cwd)
        return

    template = dirname(dirname(abspath(__file__)))
    defaults = load(open(join(template, "cookiecutter.json")))
    with tmpdir():
        cookiecutter(template, no_input=True)
        chdir(defaults["project_slug"])
        check_call(split("cmake -DCMAKE_BUILD_TYPE=Debug"))
        check_call(split("cmake --build ."))
        main_app = join(".", defaults["project_slug"])
        check_call(split("{:s} -h".format(main_app)))
        test_app = join("test", "test_{:s}".format(defaults["project_slug"]))
        check_call(split(test_app))
    return 0
    
    
# Make the script executable.

if __name__ == "__main__":
    raise SystemExit(main())
