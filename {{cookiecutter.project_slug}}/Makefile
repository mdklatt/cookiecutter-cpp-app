# Project management tasks; see CMakeLists.txt for building the project.

BUILD_TYPE = Debug
BUILD_ROOT = build/$(BUILD_TYPE)


.PHONY: dev
dev:
	cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DBUILD_TESTING=ON -DBUILD_DOCS=ON -S . -B $(BUILD_ROOT)


.PHONY: build
build:
	cmake --build $(BUILD_ROOT)


.PHONY: test
test: build
	cd $(BUILD_ROOT) && ctest


.PHONY: docs
docs:
	cmake --build $(BUILD_ROOT) --target docs
