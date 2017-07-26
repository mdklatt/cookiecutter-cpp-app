{% set delim = "=" * cookiecutter.app_name|length %}
{{ delim }}
{{ cookiecutter.app_name }}
{{ delim }}

This is the {{ cookiecutter.app_name }} application.


Building
========

Application
-----------
.. code-block:: console

    $ mkdir build && cd build
    $ cmake -DCMAKE_BUILD_TYPE=Debug ../
    $ cmake --build .
    

Documentation (Doxygen)
-----------------------
.. code-block:: console

    $ cd doc/doxygen
    $ doxygen Doxyfile
 
    
Documenation (Sphinx)
---------------------
.. _Breathe: https://breathe.readthedocs.io/en/latest/

.. code-block:: console

    $ cd doc/sphinx && make make html
    
Doxygen documentation can be integreted into Sphinx using the `Breathe`_
extension.


Running
=======

Application
-----------
.. code-block:: console

    $ cd build
    $ ./{{ cookiecutter.app_name }} --help


Test Suite
----------
.. code-block:: console

    $ cd build
    $ test/{{ cookiecutter.app_name }}_test
