# !/bin/bash
docker build -t="ethnopred/decision_tree" .
docker rm -f ethnopred
docker run -it -v /$PWD/:/ethnopred/ --name ethnopred ethnopred/decision_tree
