""" Test the Cookiecutter template.

A template project is created in a temporary directory, the application and its
test suite are built, and both are executed.

"""
import pytest
from cookiecutter.generate import generate_context
from cookiecutter.main import cookiecutter
from pathlib import Path
from shlex import split
from subprocess import check_call, run


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


@pytest.fixture(scope="session")
def build(project):
    """ Build the application.

    """
    check_call(split("make dev build"), cwd=project)
    return


def test_project(project):
    """ Verify that the project was created correctly.

    """
    # Just a basic sanity test.
    assert len(list(project.iterdir())) == 8
    return


@pytest.mark.usefixtures("build")
def test_unit(project):
    """ Verify that unit tests are working.

    """
    process = run(split(f"make test"), cwd=project)
    assert process.returncode == 0
    return


@pytest.mark.usefixtures("build")
def test_app(project, context):
    """ Verify application execution.

    """
    cwd = project / "build/Debug/src"
    command = f"./{context['app_name']} -h"
    process = run(split(command), cwd=cwd)
    assert process.returncode == 0
    return


@pytest.mark.usefixtures("build")
def test_docs(project):
    """ Verify documentation build.

    """
    process = run(split(f"make docs"), cwd=project)
    assert process.returncode == 0
    path = Path(project / "docs/doxygen/html")
    assert next(path.iterdir())  # directory isn't empty
    return


# Make the script executable.

if __name__ == "__main__":
    raise SystemExit(pytest.main([__file__]))
