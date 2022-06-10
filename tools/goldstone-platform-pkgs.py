#!/usr/bin/python
############################################################
#
# This script expects a yaml file containing the list
# of platforms that are to be included in the
# build.
#
# It produces a YAML list on stdout of all
# packages necessary to support the given list
# of platforms.
#
import onlyaml
import argparse
import onlu
import os

ap = argparse.ArgumentParser(description='Goldstone Platform Package Lister')
ap.add_argument('platforms', metavar='PLATFORM-LIST|YAML-FILE', help='YAML file containing the list of platforms.')
ap.add_argument("--no-builtins", action='store_true', help='Skip builtin ONL packages.')
ap.add_argument("--add-patterns", help="Additional package patterns.", nargs='+', default=[])
ap.add_argument("--without-vs", action='store_true', help='Skip adding VS')

ops = ap.parse_args()

if os.path.exists(ops.platforms):
    platforms = onlyaml.loadf(ops.platforms)
else:
    platforms = ops.platforms.split(',')

if not ops.without_vs:
    platforms.append('vs')

#
# The following ONL packages are needed for each platform:
#
# The platform-config package
# The ONLP package
#
ONL_PATTERNS = [ "goldstone-platform-config-%(platform)s", "goldstone-module-%(platform)s" ]

PATTERNS = list(onlu.sflatten(ops.add_patterns))

if not ops.no_builtins:
    PATTERNS = ONL_PATTERNS + PATTERNS

for p in platforms:
    for pattern in PATTERNS:
        print "-", pattern % dict(platform=p)
