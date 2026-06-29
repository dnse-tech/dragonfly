#!/bin/sh

set -e

PLATFORM=$1

PSHORT=${PLATFORM#"linux/"}
echo "PSHORT ${PSHORT}"


case "${PSHORT}" in
  amd64) SUFFIX='x86_64' ;;
  s390x) SUFFIX='s390x' ;;
  *)     SUFFIX='aarch64' ;;
esac

mv /tmp/dragonfly-${SUFFIX} /build/dragonfly
ls -l /build/
