{% set delim = "=" * cookiecutter.app_name|length %}
{{ delim }}
{{ cookiecutter.app_name }}
{{ delim }}

C++ application created from the `mdklatt/cookiecutter-cpp-app`_ template.


===========
Development
===========

Create the development environment:

.. code-block::

    $ cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON -S . -B build/Debug


Build the application:

.. code-block::

    $ cmake --build build/Debug


Run unit tests:

.. code-block::

    $ cd build && ctest


.. _mdklatt/cookiecutter-cpp-app: https://github.com/mdklatt/cookiecutter-cpp-app
