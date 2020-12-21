FROM ubuntu:16.04

LABEL "com.github.actions.name"="VCVRackPluginBuilder-Linux"
LABEL "com.github.actions.description"="Builds a VCV Rack plugin for Linux"
LABEL "com.github.actions.icon"="headphones"
LABEL "com.github.actions.color"="purple"

LABEL "repository"="https://github.com/denischevalier/StalysVCVPlugin"
LABEL "homepage"="https://linktr.ee/stalysmusic"
LABEL "maintainer"="Denis Dubo Chevalier"

RUN apt-get update
RUN apt-get install -y build-essential cmake curl gcc g++ git make tar unzip zip libgl1-mesa-dev libglu1-mesa-dev jq

ADD entrypoint.sh /entrypoint.sh
RUN chmod a+x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
