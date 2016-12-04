..  README for the {{ cookiecutter.app_name }} application.

{% set delim = "=" * cookiecutter.app_name|length %}
{{ delim }}
{{ cookiecutter.app_name }}
{{ delim }}

This is the {{ cookiecutter.app_name }} application.

Building
========

Application
-----------
..  code-block::

    $ mkdir build && cd build
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../
    $ cmake --build .
    

Documentation (Doxygen)
-----------------------
..  code-block::

    $ cd doc/doxygen
    $ doxygen Doxyfile
 
    
Documenation (Sphinx)
---------------------
..  _Breathe: https://breathe.readthedocs.io/en/latest/

..  code-block::

    $ cd doc/sphinx
    $ make html
    
Doxygen documentation can be integreted into Sphinx using the* `Breathe`_
extension.


Running
=======

Application
-----------
..  code-block::

    $ cd build
    $ ./{{ cookiecutter.app_name }} --help


Test Suite
----------
..  code-block::

    $ cd build
    $ test/{{ cookiecutter.app_name }}_test
