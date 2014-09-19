#!/bin/sh

# add FITECH to the system environment variables
INSTALLED=0
if [ -f /etc/launchd.conf ]; then
  TXT=`grep "FITECH" /etc/launchd.conf`
  if [ $? -eq 0 ]; then
    INSTALLED=1
  fi
fi

if [ $INSTALLED -eq 0 ]; then
  DIR=`pwd`
  echo "setenv FITECH $DIR" | sudo tee -a /etc/launchd.conf > /dev/null
  launchctl < /etc/launchd.conf
fi
