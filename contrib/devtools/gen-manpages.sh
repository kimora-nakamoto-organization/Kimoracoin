#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

KMRD=${KMRD:-$SRCDIR/kimorad}
KMRCLI=${KMRCLI:-$SRCDIR/kimora-cli}
KMRTX=${KMRTX:-$SRCDIR/kimora-tx}
KMRQT=${KMRQT:-$SRCDIR/qt/kimora-qt}

[ ! -x $KMRD ] && echo "$KMRD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
KMRVER=($($KMRCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for kimorad if --version-string is not set,
# but has different outcomes for kimora-qt and kimora-cli.
echo "[COPYRIGHT]" > footer.h2m
$KMRD --version | sed -n '1!p' >> footer.h2m

for cmd in $KMRD $KMRCLI $KMRTX $KMRQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${KMRVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${KMRVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
