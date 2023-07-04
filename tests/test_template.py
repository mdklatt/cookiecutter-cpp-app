""" Test the Cookiecutter template.

A template project is created in a temporary directory, the application and its
test suite are built, and both are executed.

"""
from json import loads
from pathlib import Path
from shlex import split
from subprocess import check_call
from tempfile import TemporaryDirectory

from cookiecutter.main import cookiecutter


def main() -> int:
    """ Execute the test.
    
    """
    template = Path(__file__).resolve().parents[1]
    defaults = loads(template.joinpath("cookiecutter.json").read_text())
    with TemporaryDirectory() as tmpdir:
        cookiecutter(str(template), no_input=True, output_dir=tmpdir)
        name = defaults["app_name"]
        cwd = Path(tmpdir) / name
        for opts in "-DCMAKE_BUILD_TYPE=Debug", "--build":
            check_call(split(f"cmake {opts:s} ."), cwd=cwd)
        for command in f"src/{name} -h", f"tests/unit/test_{name}":
            check_call(split(f"{command:s}"), cwd=cwd)
    return 0
    
    
# Make the script executable.

if __name__ == "__main__":
    raise SystemExit(main())
