#!/bin/sh
[ $(id -u) -eq 0 ] || exec sudo $0 $@

for bin in /var/lib/rancher/k3s/data/**/bin/; do
    [ -d $bin ] && export PATH=$PATH:$bin:$bin/aux
done

set -x

pschildren() {
    ps -e -o ppid= -o pid= | \
    sed -e 's/^\s*//g; s/\s\s*/\t/g;' | \
    grep -w "^$1" | \
    cut -f2
}

pstree() {
    for pid in $@; do
        echo $pid
        for child in $(pschildren $pid); do
            pstree $child
        done
    done
}

killtree() {
    kill -9 $(
        { set +x; } 2>/dev/null;
        pstree $@;
        set -x;
    ) 2>/dev/null
}

getshims() {
    ps -e -o pid= -o args= | sed -e 's/^ *//; s/\s\s*/\t/;' | grep -w 'k3s/data/[^/]*/bin/containerd-shim' | cut -f1
}

killtree $({ set +x; } 2>/dev/null; getshims; set -x)

do_unmount() {
    { set +x; } 2>/dev/null
    MOUNTS=
    while read ignore mount ignore; do
        MOUNTS="$mount\n$MOUNTS"
    done </proc/self/mounts
    MOUNTS=$(printf $MOUNTS | grep "^$1" | sort -r)
    if [ -n "${MOUNTS}" ]; then
        set -x
        umount ${MOUNTS}
    else
        set -x
    fi
}

do_unmount '/run/k3s'
do_unmount '/var/lib/rancher/k3s'
do_unmount '/var/lib/kubelet/pods'
do_unmount '/run/netns/cni-'

# Delete network interface(s) that match 'master cni0'
ip link show 2>/dev/null | grep 'master cni0' | while read ignore iface ignore; do
    iface=${iface%%@*}
    [ -z "$iface" ] || ip link delete $iface
done
ip link delete cni0
ip link delete flannel.1
rm -rf /var/lib/cni/
iptables-save | grep -v KUBE- | grep -v CNI- | iptables-restore
