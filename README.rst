================================
C++ Application Project Template
================================
..  |travis.png| image:: https://travis-ci.org/mdklatt/cookiecutter-cpp-app.png?branch=master
    :alt: Travis CI build status
    :target: `travis`_
..  _travis: https://travis-ci.org/mdklatt/cookiecutter-cpp-app
..  _Cookiecutter: http://cookiecutter.readthedocs.org

|travis.png|

This is a `Cookiecutter`_ template for creating a C++ application project.


Template Project Features
=========================
..  _Cmake: https://cmake.org 
..  _Google Test: https://github.com/google/googletest
..  _Google install: https://github.com/google/googletest/blob/master/googletest/docs/FAQ.md#why-is-it-not-recommended-to-install-a-pre-compiled-copy-of-google-test-for-example-into-usrlocal
..  _Doxygen: http://www.stack.nl/~dimitri/doxygen
..  _Sphinx: http://sphinx-doc.org
..  _MIT License: http://choosealicense.com/licenses/mit

* `CMake`_ builds
* `Google Test`_ test suite
* `Doxygen`_ and `Sphinx`_ documentation
* `MIT License`_


Template Application Features
=============================
* CLI with subcommands
* Logging (coming soon)


Usage
=====
Install Python requirements for using the template:

..  code-block::

    $ pip install --requirement=requirements.txt --user 


..  _GitHub: https://github.com/mdklatt/cookiecutter-cpp-app

Create a new project directly from the template on `GitHub`_:

..  code-block::
   
    $ cookiecutter gh:mdklatt/cookiecutter-cpp-app
