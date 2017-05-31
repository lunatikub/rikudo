#!/bin/bash

fifo_name="/tmp/myfifo"

trap "rm -f $fifo_name" EXIT

[ -p "$fifo_name" ] || mkfifo "$fifo_name"

exec 3< $fifo_name

while :; do
    if read -r -u 3 line; then
        if [ "$line" = 'quit' ]; then
            break
        fi
        echo "$line"
    fi
done

exec 3<&-

exit 0
