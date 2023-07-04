""" Test the Cookiecutter template.

A template project is created in a temporary directory, the application and its
test suite are built, and both are executed.

"""
import pytest
from cookiecutter.generate import generate_context
from cookiecutter.main import cookiecutter
from pathlib import Path
from shlex import split
from subprocess import run


@pytest.fixture(scope="session")
def template() -> Path:
    """ The template under test.

    """
    return Path(__file__).resolve().parents[1]


@pytest.fixture(scope="session")
def tmpdir(tmp_path_factory) -> Path:
    """ Session test directory.

    """
    # Replace builtin `tmpdir` to provide session scope.
    return tmp_path_factory.mktemp("test_template")


@pytest.fixture(scope="session")
def context(template) -> dict:
    """ Template context for testing.

    """
    context = generate_context(template.joinpath("cookiecutter.json"))
    return context["cookiecutter"]


@pytest.fixture(scope="session")
def project(tmpdir, template, context) -> Path:
    """ Create a test project from the Cookiecutter template.

    """
    cookiecutter(str(template), no_input=True, output_dir=tmpdir, extra_context=context)
    return tmpdir / context["app_name"]


def test_project(project):
    """ Verify that the project was created correctly.

    """
    # Just a basic sanity test.
    assert len(list(project.iterdir())) == 7
    return


def test_build(project, context):
    """ Verify that the application builds.

    """
    for command in "cmake .", "cmake --build .":
        process = run(split(command), cwd=project)
        assert process.returncode == 0
    return


def test_exec(project, context):
    """ Verify execution of the application and its test suite.

    """
    for command in "src/cppapp -h", "tests/unit/test_cppapp":
        process = run(split(command), cwd=project)
        assert process.returncode == 0
    return


# Make the script executable.

if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))












#
#
# def main() -> int:
#     """ Execute the test.
#
#     """
#     template = Path(__file__).resolve().parents[1]
#     defaults = loads(template.joinpath("cookiecutter.json").read_text())
#     with TemporaryDirectory() as tmpdir:
#         cookiecutter(str(template), no_input=True, output_dir=tmpdir)
#         name = defaults["app_name"]
#         cwd = Path(tmpdir) / name
#         for opts in "-DCMAKE_BUILD_TYPE=Debug", "--build":
#             check_call(split(f"cmake {opts:s} ."), cwd=cwd)
#         for command in f"src/{name} -h", f"tests/unit/test_{name}":
#             check_call(split(f"{command:s}"), cwd=cwd)
#     return 0
#
#
# # Make the script executable.
#
# if __name__ == "__main__":
#     raise SystemExit(main())
