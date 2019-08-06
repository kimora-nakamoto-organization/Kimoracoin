 #!/usr/bin/env bash

 # Execute this file to install the kimora cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Kimora-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Kimora-Qt.app/Contents/MacOS/kimorad /usr/local/bin/kimorad
 sudo ln -s ${LOCATION}/Kimora-Qt.app/Contents/MacOS/kimora-cli /usr/local/bin/kimora-cli
