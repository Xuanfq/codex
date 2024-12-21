#!/bin/bash
set -x

ex-export()
{
    echo "================== Example: export"
    export VAR=environment_value
    make ex-export          # result: Makefile_value
    make ex-export -e       # result: environment_value
####  result:
# + echo '================== Example: export'
# ================== Example: export
# + export VAR=environment_value
# + VAR=environment_value
# + make ex-export
# Makefile: VAR=Makefile_value
# make ex-export -C sub01
# make[1]: Entering directory '/home/dev/ws/codex/lang/make/sub01'
# sub01.Makefile: VAR=sub01.Makefile
# make[1]: Leaving directory '/home/dev/ws/codex/lang/make/sub01'
# export VAR
# make ex-export -C sub01
# make[1]: Entering directory '/home/dev/ws/codex/lang/make/sub01'
# sub01.Makefile: VAR=sub01.Makefile
# make[1]: Leaving directory '/home/dev/ws/codex/lang/make/sub01'
# + make ex-export -e
# Makefile: VAR=environment_value
# make ex-export -C sub01
# make[1]: Entering directory '/home/dev/ws/codex/lang/make/sub01'
# sub01.Makefile: VAR=environment_value
# make[1]: Leaving directory '/home/dev/ws/codex/lang/make/sub01'
# export VAR
# make ex-export -C sub01
# make[1]: Entering directory '/home/dev/ws/codex/lang/make/sub01'
# sub01.Makefile: VAR=environment_value
# make[1]: Leaving directory '/home/dev/ws/codex/lang/make/sub01'
}


ex-export
