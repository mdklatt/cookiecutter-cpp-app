################################
C++ Application Project Template
################################

|c++17|
|cmake|
|license|
|tests|


This is a `Cookiecutter`_ template for creating a C++ application project that
uses modern CMake practices (*e.g.*  `It's Time To Do CMake Right`_).


**Project features**:

- C++17
- `CMake`_ builds
- `Google Test`_ test suite
- `Doxygen`_ documentation
- `MIT License`_


**Application features**:

- CLI with subcommands
- Logging
- Hierarchical `TOML`_ configuration


=====
Usage
=====

Install Python requirements for using the template:

.. code-block::

    $ python -m pip install -r requirements.txt


Create a new project directly from the template on `GitHub`_:

.. code-block::

    $ cookiecutter gh:mdklatt/cookiecutter-cpp-app


===========
Development
===========

Create a local development environment and run template tests:

.. code-block::

    $ make dev test


.. |c++17| image:: https://img.shields.io/static/v1?label=c%2B%2B&message=17&color=informational
   :alt: C++17
.. |cmake| image:: https://img.shields.io/static/v1?label=cmake&message=3.16&color=informational
   :alt: CMake 3.16
.. |license| image:: https://img.shields.io/github/license/mdklatt/cookiecutter-cpp-app
   :alt: MIT License
   :target: `MIT License`_
.. |tests| image:: https://github.com/mdklatt/cookiecutter-cpp-app/actions/workflows/test.yml/badge.svg
   :alt: CI Test
   :target: `GitHub Actions`_

.. _CMake: https://cmake.org
.. _Cookiecutter: http://cookiecutter.readthedocs.org
.. _Doxygen: http://www.stack.nl/~dimitri/doxygen
.. _Google Test: https://github.com/google/googletest
.. _GitHub: https://github.com/mdklatt/cookiecutter-cpp-app
.. _GitHub Actions: https://github.com/mdklatt/cookiecutter-cpp-app/actions/workflows/test.yml
.. _It's Time To Do CMake Right: https://pabloariasal.github.io/2018/02/19/its-time-to-do-cmake-right/
.. _MIT License: http://choosealicense.com/licenses/mit
.. _TOML: https://toml.io/en/
