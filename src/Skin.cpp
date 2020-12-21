#include "Skin.hpp"
#include <cstdio>
#include <fstream>
#include <unistd.h>

Skins &Skins::skins() {
  static Skins instance;
  std::lock_guard<std::mutex> lock(instance.lock);
  if (!instance.loaded) {
    instance.loadSkins();
    instance.loaded = true;
  }
  return instance;
}

bool Skins::validKey(const std::string &key) const {
  for (auto s : availableSkins) {
    if (s.key == key) {
      return true;
    }
  }
  return false;
}

void Skins::loadSkins() {
  availableSkins.push_back(Skin("bee", "Bee"));
  availableSkins.push_back(Skin("hornet", "Hornet"));
  availableSkins.push_back(Skin("light", "Light"));
  availableSkins.push_back(Skin("dark", "Dark"));
  defaultKey = "hornet";

  std::string path = rack::asset::user("stalys.json");
  if (access(path.c_str(), R_OK) != 0) {
    return;
  }

  json_error_t error;
  json_t *root = json_load_file(path.c_str(), 0, &error);
  if (!root) {
    WARN("Stalys: JSON error loading skins data from %s: %s\n", path.c_str(),
         error.text);
    return;
  }

  json_t *skins = json_object_get(root, "skins");
  if (!skins) {
    WARN("Stalys: no \"skins\" section found in %s\n", path.c_str());
  } else {
    json_t *d = json_object_get(skins, "default");
    if (!d) {
      WARN("Stalys: \"skins\" section has no key \"default\" in %s\n",
           path.c_str());
    } else {
      std::string dk = json_string_value(d);
      if (!validKey(dk)) {
        WARN("Stalys: \"skins\" \"default\" value \"%s\" is invalid in %s\n",
             dk.c_str(), path.c_str());
        WARN("Stalys: available skins are:\n");
        for (auto s : availableSkins) {
          WARN("Stalys:   %s\n", s.key.c_str());
        }
      } else {
        INFO("Stalys: skin information loaded successfully from %s\n",
             path.c_str());
      }
    }
  }

  json_decref(root);
}

void Skins::setDefaultSkin(std::string skinKey) {
  if (skinKey == "default") {
    skinKey = "hornet";
  }
  std::string path = rack::asset::user("Stalys.json");
  std::string error;
  if (!validKey(skinKey)) {
    error = "invalid key: " + skinKey;
  } else {
    std::ofstream f(path);
    f << "{\n  \"skins\": {\n    \"default\": \"";
    f << skinKey;
    f << "\"\n  }\n}\n";
    if (!f) {
      error = "error writing \"" + path + "\": " + strerror(errno);
    }
  }

  if (error.size() > 0) {
    WARN("Stalys: setting default skin: %s\n", error.c_str());
  } else {
    defaultKey = skinKey;
    INFO("Stalys: skin information written to %s\n", path.c_str());

    std::lock_guard<std::mutex> lock(defaultSkinListenersLock);
    for (auto listener : defaultSkinListeners) {
      listener->defaultSkinChanged(defaultKey);
    }
  }
}

void Skins::registerDefaultSkinChangeListener(
    DefaultSkinChangeListener *listener) {
  std::lock_guard<std::mutex> lock(defaultSkinListenersLock);
  defaultSkinListeners.insert(listener);
}

void Skins::deregisterDefaultSkinChangeListener(
    DefaultSkinChangeListener *listener) {
  std::lock_guard<std::mutex> lock(defaultSkinListenersLock);
  defaultSkinListeners.erase(listener);
}
