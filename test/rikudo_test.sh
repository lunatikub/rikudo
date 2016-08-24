#!/bin/bash

SCRIPT_DIR=$(dirname $(readlink -f $0))

RIKUDO=${SCRIPT_DIR}/../rikudo
CFG=${SCRIPT_DIR}/../src/rikudo_cfg.h

_KO=0
_OK=0

KO ()
{
    echo "KO"
    _KO=$((_KO + 1))
}

OK ()
{
    echo "OK"
    _OK=$((_OK + 1))
}

diff()
{
    g1=$1
    g2=$2


}

rikudo_option_set ()
{
    sed -i "s/\/\/\(#define RIKUDO_CFG_$1\)/\1/" ${CFG}
}

rikudo_option_unset ()
{
    sed -i "s/\(#define RIKUDO_CFG_$1\)/\/\/\1/" ${CFG}
}

rikudo_compilation ()
{
    make -C ${SCRIPT_DIR}/../ clean
    make -C ${SCRIPT_DIR}/../
}

rikudo_test_unitary ()
{
    g=$(sed "1q;d" $1)
    nr_t=$(sed "2q;d" $1)
    t=$(sed "3q;d" $1)
    expected=$(sed "4q;d" $1)

    result=$(${RIKUDO} ${g} ${nr_t} ${t})
    printf "%-60s" $1
    [ "${result}" != "${expected}" ] && KO || OK
}


rikudo_test ()
{
    rikudo_option_set DUMP
    rikudo_compilation

    [ "$1" != "" ] && rikudo_test $1 && exit 0

    for grid in $(find ${SCRIPT_DIR}/grid -name "*.grid")
    do
        rikudo_test_unitary ${grid}
    done

    echo ""
    echo "OK: ${_OK}/$((_OK + _KO))"
    echo "KO: ${_KO}/$((_OK + _KO))"

    rikudo_option_unset DUMP
}

rikudo_cycle_unitary ()
{
    g=$(sed "1q;d" $1)
    nr_t=$(sed "2q;d" $1)
    t=$(sed "3q;d" $1)
    expected=$(sed "4q;d" $1)

    ${RIKUDO} ${g} ${nr_t} ${t}
}

rikudo_cycle ()
{
    rikudo_option_set CYCLE
    rikudo_compilation

    for grid in $(find ${SCRIPT_DIR}/grid -name "*.grid")
    do
        rikudo_cycle_unitary ${grid}
    done

    rikudo_option_unset CYCLE
}

rikudo_test
rikudo_cycle

exit 0
