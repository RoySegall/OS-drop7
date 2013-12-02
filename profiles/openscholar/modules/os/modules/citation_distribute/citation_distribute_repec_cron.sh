#!/bin/sh

# On cloud hosting environments it is not always an option to give a repec archive
# its own apache vhost.  Citation Distribute attempts to alleviate that by providing
# the `/repec/` page.  wgetting it (or hitting it with this script as a cron job) will
# copy it, resulting in a repec archive.

if [ $# -ne 2 ] ; then
  echo -e "\nUsage: citation_distribute_repec_cron.sh http://your-site.com/repec /path/to/repec/archive\n"
  exit 1
fi

if [ ! -w "$2" ] ; then
  echo -e "\nError: Directory '$2' is not writeable or not a directory.\n"
  exit 1
fi

TMP=$(mktemp -d)
wget -m "$1" -P "$TMP"

find $TMP -name index.html -delete
mv $TMP/*/repec/* "$2/"
rm -rf $TMP
