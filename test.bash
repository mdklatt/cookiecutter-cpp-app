## Test the cpp-app Cookiecutter template.
##
## A template project is created in a temporary directory, the application is
## build, and the application and its test suite is run.
##
set -e  # exit immediately on failure
if [[ "$(uname)" == "Darwin" ]]
then  # OS X uses BSD mktemp
    MKTEMP="mktemp -d -t tmp"
else  # assume Linux/GNU or similar
    MKTEMP="mktemp -d"
fi
template=$(pwd)
tmpdir=$(${MKTEMP})
trap "rm -rf $tmpdir" EXIT  # remove on exit
pushd $tmpdir
cookiecutter $template --no-input
cd hello
cmake -DCMAKE_BUILD_TYPE=Debug && make
build/Debug/hello
popd
exit 0
