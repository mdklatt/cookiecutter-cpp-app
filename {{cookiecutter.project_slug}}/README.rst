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

    $ make dev


Build the project:

.. code-block::

    $ make build


Run tests:

.. code-block::

    $ make test


Build documentation:

.. code-block::

    $ make docs


.. _mdklatt/cookiecutter-cpp-app: https://github.com/mdklatt/cookiecutter-cpp-app
