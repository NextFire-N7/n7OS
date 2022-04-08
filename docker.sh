#!/bin/sh -e
docker build -t archise .
docker run --rm -it -v $(pwd):/projet archise $@
