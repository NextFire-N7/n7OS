#!/bin/sh -e
# docker build -t archi-se .
docker run --rm -it -v $(pwd):/projet archi-se $@
