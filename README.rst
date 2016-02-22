C++ Application Project Template
================================

Overview |travis.png|
---------------------

This is a `Cookiecutter`_ template for creating a C++ application project.

..  |travis.png| image:: https://travis-ci.org/mdklatt/cookiecutter-cpp-app.png?branch=master
    :alt: Travis CI build status
    :target: `travis`_

..  _travis: https://travis-ci.org/mdklatt/cookiecutter-cpp-app
..  _Cookiecutter: http://cookiecutter.readthedocs.org


Template Project Features
-------------------------

* `CMake`_ builds
* `Google Test`_ tests
* `Sphinx`_ documentation
* `MIT License`_

..  _Cmake: https://cmake.org 
..  _Google Test: https://github.com/google/googletest
..  _Sphinx: http://sphinx-doc.org
..  _MIT License: http://choosealicense.com/licenses/mit


Usage
-----

Install Python requirements for using the template:

..  code-block::

    $ pip install --requirement=requirements.txt --user 


Create a new project directly from the template on `GitHub`_:

..  code-block::
   
    $ cookiecutter gh:mdklatt/cookiecutter-cpp-app


..  _GitHub: https://github.com/mdklatt/cookiecutter-cpp-app


Build the project using CMake:

..  code-block::

    $ mkdir -p build/Debug && cd build/Debug
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../../
    $ make
    
    
Generate Sphinx documenation.

..  code-block::

    $ pip install --requirement=requirements-doc.txt --user
    $ cd doc
    $ make html
