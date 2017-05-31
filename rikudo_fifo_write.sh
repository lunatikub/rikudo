#!/bin/bash

#!/bin/bash

fifo_name="/tmp/myfifo"

[ -p "$fifo_name" ] || {
    exit 1
}

./fastafc -I eno1 http content | sed -n "s/.*var GrilleARemplir = \([[][^]]*[]]\).*var NbDir = \([0-9]*\)\;.*var DirList = \([[][^]]*[]]\).*/\1\n\2\n\3/p" > $fifo_name

exit 0
