# Project management tasks.

VENV = .venv
PYTHON = source $(VENV)/bin/activate && python
PYTEST = $(PYTHON) -m pytest -v

$(VENV)/.make-update: requirements-dev.txt
	python -m venv $(VENV)
	$(PYTHON) -m pip install -U pip  # needs to be updated first
	$(PYTHON) -m pip install -r $^
	touch $@


.PHONY: dev
dev: $(VENV)/.make-update


.PHONY: test
test: dev
	@$(PYTEST) tests/test_template.py && echo "All tests passed"
