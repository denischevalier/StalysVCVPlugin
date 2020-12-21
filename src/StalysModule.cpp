#include "StalysModule.hpp"
#include "Skin.hpp"

#define SKIN "skin"

json_t *StalysModule::dataToJson() {
  json_t *root = json_object();
  if (theme != "default") {
    json_object_set_new(root, SKIN, json_string(theme.c_str()));
  }
  return toJson(root);
}

void StalysModule::dataFromJson(json_t *root) {
  json_t *s = json_object_get(root, SKIN);
  if (s) {
    setSkin(json_string_value(s));
  }
  else {
    setSkin(theme);
  }

  fromJson(root);
}

void StalysModule::addSkinChangedListener(SkinChangedListener *listener) {
  skinChangedListeners.push_back(listener);
}

void StalysModule::setSkin(const std::string skin) {
  if (skin == "default" || Skins::skins().validKey(skin)) {
    theme = skin;
    for (auto scl : skinChangedListeners) {
      scl->skinChanged(skin);
    }
  }
}
