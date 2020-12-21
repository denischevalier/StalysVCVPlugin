FROM debian:stretch

LABEL "com.github.actions.name"="VCVRackPluginBuilder-Windows"
LABEL "com.github.actions.description"="Builds a VCV Rack plugin for Windows"
LABEL "com.github.actions.icon"="headphones"
LABEL "com.github.actions.color"="purple"

LABEL "repository"="https://github.com/denischevalier/StalysVCVPlugin"
LABEL "homepage"="https://linktr.ee/stalysmusic"
LABEL "maintainer"="Denis Dubo Chevalier"

RUN apt-get update
RUN apt-get install -y build-essential cmake curl gcc g++ git make tar unzip zip libgl1-mesa-dev libglu1-mesa-dev jq g++-mingw-w64-x86-64

ADD entrypoint.sh /entrypoint.sh
RUN chmod a+x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
