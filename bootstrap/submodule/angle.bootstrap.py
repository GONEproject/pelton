#!/usr/bin/python2

# Copyright 2015 Google Inc.  All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Generate .gclient file for Angle.

Because gclient won't accept "--name ." use a different name then edit.
"""

import subprocess
import sys


def main():
    cmd = ('cd $PWD/../../engine/submodules/angle '
            '&& ./../depot_tools/gclient config --name change2dot --unmanaged https://chromium.googlesource.com/angle/angle.git '
            '&& ./../depot_tools/gn gen out/Debug')
    try:
        rc = subprocess.call(cmd, shell=True)
    except OSError:
        print 'could not run "%s" via shell' % cmd
        sys.exit(1)

    if rc:
        print 'failed command: "%s"' % cmd
        sys.exit(1)

    with open('.gclient') as gclient_file:
        content = gclient_file.read()

    with open('.gclient', 'w') as gclient_file:
        gclient_file.write(content.replace('change2dot', '.'))

    print 'bootstrapped angle'

if __name__ == '__main__':
    main()