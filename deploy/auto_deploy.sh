#!/bin/bash
ETHNOPRED_TESTING_IP=199.166.235.228
SSH_KEY_FOLDER=$PWD/ssh_pri_keys
TESING_KEY=${SSH_KEY_FOLDER}/ethnopred_admin_git.pem

BASH_FILE_1="ssh-bash-1.sh"
#must change the private key to 600. Otherwise, you will get err: "private key too open err"
chmod 600 ${SSH_KEY_FOLDER}
ssh -i $PWD/gt-remote.pem ubuntu@$IP_CYBERA_1 'bash -s' < $PWD/ssh-bash-1.sh
